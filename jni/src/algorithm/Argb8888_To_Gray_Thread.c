/**
 * @file    Argb8888_To_Gray_Thread.c
 * @date    2013-12-08
 * @author  cnagune (blog@cnagune.pe.kr)
 * @brief   일반 명령어와 Thread를 사용하여 Grayscale 변환을 수행한다.
 */

#include <pthread.h>
#include "Common.h"
#include "Allocation.h"
#include "algorithm/Argb8888_To_Gray_Thread.h"

static void *thread_calc(void *arg);


/**
 * @brief 각 thread에 넘겨줄 계산 정보가 담긴 구조체
 */
struct _thread_data
{
    unsigned char *data_in;     /// in 메모리의 시작 위치
    unsigned char *data_out;    /// out 메모리의 시작 위치
    int size;                   /// 계산할 pixels의 길이
};


/**
 * @brief Grayscale 변환 함수 - 일반 명령어와 Thread 사용
 *
 * @param in_pixels 원본 이미지에 대한 ARGB8888 형식의 배열
 * @param out_pixels 결과 이미지를 저장할 배열
 * @param size 계산하고자 하는 픽셀 길이 (메모리는 4배)
 * @param thread_cnt 스레드 갯수
 */
void argb8888_to_gray_thread(void *in_pixels, void *out_pixels, int size, int thread_cnt)
{
    int i;

    unsigned char *in_start_ptr = (unsigned char *)in_pixels;
    unsigned char *out_start_ptr = (unsigned char *)out_pixels;
    int chunk_size = size / thread_cnt;
    chunk_size -= chunk_size % (CACHE_LINE_SIZE / 4);

    int *status;
    pthread_t threads[thread_cnt];
    struct _thread_data thread_data[thread_cnt];

    for (i = 0; i < thread_cnt - 1; i++) {
        thread_data[i].data_in  = in_start_ptr;
        thread_data[i].data_out = out_start_ptr;
        thread_data[i].size = chunk_size;

        in_start_ptr  += chunk_size * 4;
        out_start_ptr += chunk_size * 4;
    }
    thread_data[thread_cnt - 1].data_in  = in_start_ptr;
    thread_data[thread_cnt - 1].data_out = out_start_ptr;
    thread_data[thread_cnt - 1].size = size - chunk_size * (thread_cnt - 1);

    for (i = 0; i < thread_cnt; i++) {
        pthread_create(&threads[i], NULL, &thread_calc, (void *)(&thread_data[i]));
    }

    for (i = 0; i < thread_cnt; i++) {
        pthread_join(threads[i], (void **)(&status));
    }
}


/**
 * @brief Grayscale 변환을 수행하는 thread 함수. 일반 명령어를 사용한다.
 *
 * @param arg 계산해야할 정보가 담겨있는 _thread_data 형식의 구조체
 *
 * @return NULL
 */
static void *thread_calc(void *arg)
{
    struct _thread_data data = *((struct _thread_data *)arg);

    while (data.size-- > 0) {
        // 할당 (little-endian)
        int b = *data.data_in++; // 0xBB
        int g = *data.data_in++; // 0xGG
        int r = *data.data_in++; // 0xRR
        int c = *data.data_in++; // 0xAA

        // 게산
        r *= 76; 
        g *= 151;
        b *= 29; 
        int y = (r + g + b) >> 8; // luminance

        // 저장
        *data.data_out++ = y;
        *data.data_out++ = y;
        *data.data_out++ = y;
        *data.data_out++ = c;
    }

    return NULL;
}

