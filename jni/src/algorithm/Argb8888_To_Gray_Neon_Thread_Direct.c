/**
 * @file    Argb8888_To_Gray_Neon_Thread_Direct.c
 * @date    2013-12-08
 * @author  cnagune (blog@cnagune.pe.kr)
 * @brief   NEON 명령어와 Thread를 사용하여 Grayscale 변환을 수행한다.
 *          in, out 메모리가 아닌 Bitmap 메모리로 바로 접근한다
 */

#ifdef __ARM_NEON__
#include <arm_neon.h>
#include <pthread.h>
#include "Common.h"
#include "algorithm/Argb8888_To_Gray.h"
#include "algorithm/Argb8888_To_Gray_Neon_Thread.h"


static void *thread_calc(void *arg);


/**
 * @brief 각 thread에 넘겨줄 계산 정보가 담긴 구조체
 */
struct _thread_data
{
    const unsigned int *data_in;    /// in 메모리의 시작 위치
    unsigned char *data_out;        /// out 메모리의 시작 위치
    int size;                       /// 계산할 pixels의 길이
};


/**
 * @brief Grayscale 변환 함수 - NEON 명령어와 Thread 사용
 *        in, out 메모리를 사용하지 않고 인자로 넘어온 메모리를 사용
 *
 * @param in_pixels 원본 이미지에 대한 ARGB8888 형식의 배열
 * @param out_pixels 결과 이미지를 저장할 배열
 * @param size 계산하고자 하는 픽셀 길이 (메모리는 4배)
 * @param thread_cnt 스레드 갯수
 */
void argb8888_to_gray_neon_thread_direct(const void *in_pixels, void *out_pixels, int size, int thread_cnt)
{
    int i;

    const unsigned int *in_start_ptr = (const unsigned int *)in_pixels;
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

        in_start_ptr  += chunk_size;
        out_start_ptr += chunk_size;
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
 * @brief Grayscale 변환을 수행하는 thread 함수. NEON 명령어를 사용한다.
 *
 * @param arg 계산해야할 정보가 담겨있는 _thread_data 형식의 구조체
 *
 * @return NULL
 */
static void *thread_calc(void *arg)
{
    struct _thread_data *data = (struct _thread_data *)arg;

    uint8x8_t rfac = vdup_n_u8 (76);
    uint8x8_t gfac = vdup_n_u8 (151);
    uint8x8_t bfac = vdup_n_u8 (29);
    int n = data->size / 8;
    int m = data->size % 8;

    const unsigned int *data_in  = data->data_in;
    unsigned char *data_out = data->data_out;

    // 한 루프당 8픽셀씩 변환 (32 bytes)
    while (n--) {
        uint16x8_t  temp;
        uint8x8x4_t rgb  = vld4_u8 ((unsigned char *)data_in);
        uint8x8_t result;

        temp = vmull_u8(rgb.val[0],       bfac);
        temp = vmlal_u8(temp, rgb.val[1], gfac);
        temp = vmlal_u8(temp, rgb.val[2], rfac);

        result = vshrn_n_u16 (temp, 8);
        vst1_u8(data_out, result);

        data_in += 8;
        data_out += 8;
    }

    if (m) {
        argb8888_to_gray(data_in, data_out, m);
    }

    return NULL;
}

#endif  /* __ARM_NEON__ */

