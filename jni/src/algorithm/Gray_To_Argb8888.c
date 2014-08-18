/**
 * @file    Gray_To_Argb8888.c
 * @date    2013-12-08
 * @author  cnagune (blog@cnagune.pe.kr)
 * @brief   일반 명령어를 사용하여 Grayscale 4bytes 변환을 수행한다.
 */

#include "Allocation.h"
#include "algorithm/Gray_To_Argb8888.h"


/**
 * @brief Grayscale 4bytes 변환 함수 - 일반 명령어
 *
 * @param in_pixels 원본 이미지에 대한 1bytes 형식의 배열
 * @param out_pixels 결과 이미지를 저장할 배열 (ARGB8888)
 * @param size 계산하고자 하는 픽셀 길이 (메모리는 4배)
 */
void gray_to_argb8888(const void *in_pixels, void *out_pixels, int size)
{
    const unsigned char *data_in  = (const unsigned char *)in_pixels;
    unsigned char *data_out = (unsigned char *)out_pixels;

    while (size--) {
        *data_out++ = *data_in;
        *data_out++ = *data_in;
        *data_out++ = *data_in++;
        *data_out++ = 0xff;
    }
}

