/**
 * @file     Rs-jni.c
 * @date     2013-12-08
 * @author   cnagune (blog@cnagune.pe.kr)
 * @brief    jni 인터페이스를 담당
 * @warning  make 명령을 수행하면 이 파일은 컴파일하지 않음
 */

#include <android/log.h>
#include <android/bitmap.h>
#include "Rs-jni.h"
#include "Allocation.h"
#include "algorithm/Argb8888_To_Gray.h"
#include "algorithm/Argb8888_To_Gray_Neon.h"
#include "algorithm/Argb8888_To_Gray_Thread.h"
#include "algorithm/Argb8888_To_Gray_Neon_Thread.h"
#include "algorithm/Argb8888_To_Gray_Neon_Thread_Direct.h"


#define  LOG_TAG    "test"
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)



/*********************************************************
 * 메모리 관련 함수에 대한 인터페이스
 *********************************************************/

/**
 * @brief in 메모리 할당 및 pixels 배열 복사 (size * 4)
 *
 * @param env ...
 * @param thiz ...
 * @param bitmap in 메모리로 복사하고자 하는 bitmap 객체
 */
void Java_kr_pe_cnagune_renderscripttest_RsJNI_CopyToIn
    (JNIEnv *env, jobject thiz, jobject bitmap)
{
    AndroidBitmapInfo info;
    void *pixels;
    int ret;


    if ((ret = AndroidBitmap_getInfo(env, bitmap, &info)) < 0) {
        LOGE("AndroidBitmap_getInfo() failed ! error=%d", ret);
        return;
    }

    if (info.format != ANDROID_BITMAP_FORMAT_RGBA_8888) {
        LOGE("Bitmap format is not RGBA_8888 !");
        return;
    }

    if ((ret = AndroidBitmap_lockPixels(env, bitmap, &pixels)) < 0) {
        LOGE("AndroidBitmap_lockPixels() failed ! error=%d", ret);
    }

    copy_to_in(pixels, info.width * info.height);

    AndroidBitmap_unlockPixels(env, bitmap);
}


/**
 * @brief out 메모리 할당 (size * 4)
 *
 * @param env ...
 * @param thiz ...
 * @param size 할당될 메모리에 대한 픽셀 길이 (4배로 할당)
 */
void Java_kr_pe_cnagune_renderscripttest_RsJNI_CreateMemoryToOut
    (JNIEnv *env, jobject thiz, jint size)
{
    create_memory_to_out(size);
}


/**
 * @brief out 메모리의 내용을 pixels 배열로 복사 (size * 4)
 *
 * @param env ...
 * @param thiz ...
 * @param bitmap out 메모리에서 복사되고자 하는 bitmap 객체
 */
void Java_kr_pe_cnagune_renderscripttest_RsJNI_CopyFromOut
    (JNIEnv *env, jobject thiz, jobject bitmap)
{
    AndroidBitmapInfo info;
    void *pixels;
    int ret;


    if ((ret = AndroidBitmap_getInfo(env, bitmap, &info)) < 0) {
        LOGE("AndroidBitmap_getInfo() failed ! error=%d", ret);
        return;
    }

    if (info.format != ANDROID_BITMAP_FORMAT_RGBA_8888) {
        LOGE("Bitmap format is not RGBA_8888 !");
        return;
    }

    if ((ret = AndroidBitmap_lockPixels(env, bitmap, &pixels)) < 0) {
        LOGE("AndroidBitmap_lockPixels() failed ! error=%d", ret);
    }

    copy_from_out(pixels, info.width * info.height);

    AndroidBitmap_unlockPixels(env, bitmap);
}



/*********************************************************
 * 계산 관련된 함수에 대한 인터페이스
 *********************************************************/

/**
 * @brief Grayscale 변환 함수 - 일반 명령어 사용
 *
 * @param env ...
 * @param thiz ...
 * @param size 계산되고자 하는 pixels 길이
 */
void Java_kr_pe_cnagune_renderscripttest_RsJNI_CalcNdk
    (JNIEnv *env, jobject thiz, jint size)
{
    argb8888_to_gray(get_in_memory(), get_out_memory(), size);
}


/**
 * @brief Grayscale 변환 함수 - NEON 명령어 사용
 *
 * @param env ...
 * @param thiz ...
 * @param size 계산되고자 하는 pixels 길이
 */
void Java_kr_pe_cnagune_renderscripttest_RsJNI_CalcNdkNeon
    (JNIEnv *env, jobject thiz, jint size)
{
    argb8888_to_gray_neon(get_in_memory(), get_out_memory(), size);
}


/**
 * @brief Grayscale 변환 함수 - 일반 명령어와 Thread 사용
 *
 * @param env ...
 * @param thiz ...
 * @param size 계산되고자 하는 pixels 길이
 * @param thread_cnt thread 갯수
 */
void Java_kr_pe_cnagune_renderscripttest_RsJNI_CalcNdkThread
    (JNIEnv *env, jobject thiz, jint size, jint thread_cnt)
{
    argb8888_to_gray_thread(get_in_memory(), get_out_memory(), size, thread_cnt);
}


/**
 * @brief Grayscale 변환 함수 - NEON 명령어와 Thread 사용
 *
 * @param env ...
 * @param thiz ...
 * @param size 계산되고자 하는 pixels 길이
 * @param thread_cnt thread 갯수
 */
void Java_kr_pe_cnagune_renderscripttest_RsJNI_CalcNdkNeonThread
    (JNIEnv *env, jobject thiz, jint size, jint thread_cnt)
{
    argb8888_to_gray_neon_thread(get_in_memory(), get_out_memory(), size, thread_cnt);
}


/**
 * @brief Grayscale 변환 함수 - NEON 명령어와 Thread 사용, bitmap 직접 제어
 *
 * @param env ...
 * @param thiz ...
 * @param in_bitmap 원본 이미지에 대한 bitmap - ARGB8888
 * @param out_bitmap 계산될 이미지에 대한 bitmap - GRAYSCALE
 * @param thread_cnt thread 갯수
 */
void Java_kr_pe_cnagune_renderscripttest_RsJNI_CalcNdkNeonThreadDirect
    (JNIEnv *env, jobject thiz, jobject in_bitmap, jobject out_bitmap, jint thread_cnt)
{
    AndroidBitmapInfo in_info, out_info;
    void *in_pixels, *out_pixels;
    int ret;


    // 1. in_bitmap 유효성 검사
    if ((ret = AndroidBitmap_getInfo(env, in_bitmap, &in_info)) < 0) {
        LOGE("AndroidBitmap_getInfo() failed ! error=%d", ret);
        return;
    }

    if (in_info.format != ANDROID_BITMAP_FORMAT_RGBA_8888) {
        LOGE("Bitmap format is not RGBA_8888 !");
        return;
    }

    // 2. out_bitmap 유효성 검사
    if ((ret = AndroidBitmap_getInfo(env, out_bitmap, &out_info)) < 0) {
        LOGE("AndroidBitmap_getInfo() failed ! error=%d", ret);
        return;
    }

    if (out_info.format != ANDROID_BITMAP_FORMAT_RGBA_8888) {
        LOGE("Bitmap format is not RGBA_8888 !");
        return;
    }

    // 3. in_bitmap과 out_bitmap 크기 비교
    if (in_info.width != out_info.width || in_info.height != out_info.height) {
        LOGE("Bitmap size is not same !");
        return;
    }

    // 4. bitmap 락 걸기
    if ((ret = AndroidBitmap_lockPixels(env, in_bitmap, &in_pixels)) < 0) {
        LOGE("AndroidBitmap_lockPixels() failed ! error=%d", ret);
    }

    if ((ret = AndroidBitmap_lockPixels(env, out_bitmap, &out_pixels)) < 0) {
        AndroidBitmap_unlockPixels(env, in_bitmap);
        LOGE("AndroidBitmap_lockPixels() failed ! error=%d", ret);
    }

    // 5. 변환 작업 수행
    argb8888_to_gray_neon_thread_direct(in_pixels, out_pixels, in_info.width * in_info.height, thread_cnt);

    // 6. bitmap 락 해제
    AndroidBitmap_unlockPixels(env, in_bitmap);
    AndroidBitmap_unlockPixels(env, out_bitmap);
}


