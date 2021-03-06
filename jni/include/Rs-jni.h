/**
 * @file     Rs-jni.h
 * @date     2013-12-08
 * @author   cnagune (blog@cnagune.pe.kr)
 * @brief    jni 인터페이스를 담당
 * @warning  make 명령을 수행하면 이 파일은 컴파일하지 않음
 */

#ifndef __RS_JNI_H__
#define __RS_JNI_H__

#include <jni.h>


#ifdef __cplusplus
extern "C" {
#endif


/*********************************************************
 * 메모리 초기화 관련 함수에 대한 인터페이스
 *********************************************************/



/*********************************************************
 * 메모리 관련 함수에 대한 인터페이스
 *********************************************************/

/// in 메모리 할당 및 pixels 배열 복사 (size * 4)
JNIEXPORT void JNICALL
    Java_kr_pe_cnagune_renderscripttest_RsJNI_CopyToIn
    (JNIEnv *env, jobject thiz, jobject bitmap);

/// out 메모리 할당 (size * 4)
JNIEXPORT void JNICALL
    Java_kr_pe_cnagune_renderscripttest_RsJNI_CreateMemoryToOut
    (JNIEnv *env, jobject thiz, jint size);

/// out 메모리의 내용을 pixels 배열로 복사 (size * 4)
JNIEXPORT void JNICALL
    Java_kr_pe_cnagune_renderscripttest_RsJNI_CopyFromOut
    (JNIEnv *env, jobject thiz, jobject bitmap);


/*********************************************************
 * 계산 관련된 함수에 대한 인터페이스
 *********************************************************/

/// Grayscale 변환 함수 - 일반 명령어 사용
JNIEXPORT void JNICALL
    Java_kr_pe_cnagune_renderscripttest_RsJNI_CalcNdk
    (JNIEnv *env, jobject thiz, jint size);

/// Grayscale 변환 함수 - NEON 명령어 사용
JNIEXPORT void JNICALL
    Java_kr_pe_cnagune_renderscripttest_RsJNI_CalcNdkNeon
    (JNIEnv *env, jobject thiz, jint size);

/// Grayscale 변환 함수 - 일반 명령어와 Thread 사용
JNIEXPORT void JNICALL
    Java_kr_pe_cnagune_renderscripttest_RsJNI_CalcNdkThread
    (JNIEnv *env, jobject thiz, jint size, jint thread_cnt);

/// Grayscale 변환 함수 - NEON 명령어와 Thread 사용
JNIEXPORT void JNICALL
    Java_kr_pe_cnagune_renderscripttest_RsJNI_CalcNdkNeonThread
    (JNIEnv *env, jobject thiz, jint size, jint thread_cnt);

/// Grayscale 변환 함수 - NEON 명령어와 Thread 사용, bitmap 직접 제어
JNIEXPORT void JNICALL
    Java_kr_pe_cnagune_renderscripttest_RsJNI_CalcNdkNeonThreadDirect
    (JNIEnv *env, jobject thiz, jobject in_bitmap, jobject out_bitmap, jint thread_cnt);


#ifdef __cplusplus
}
#endif

#endif  /* __RS_JNI_H__ */

