/**
 * @file    Argb8888_To_Gray.c
 * @date    2013-12-08
 * @author  cnagune (blog@cnagune.pe.kr)
 * @brief   일반 명령어를 사용하여 Grayscale 변환을 수행한다.
 */

#include "Allocation.h"
#include "algorithm/Argb8888_To_Gray.h"


/**
 * @brief Grayscale 변환 함수 - 일반 명령어
 *
 * @param in_pixels 원본 이미지에 대한 ARGB8888 형식의 배열
 * @param out_pixels 결과 이미지를 저장할 배열
 * @param size 계산하고자 하는 픽셀 길이 (메모리는 4배)
 */
void argb8888_to_gray(void *in_pixels, void *out_pixels, int size)
{
    int i;

    unsigned char *data_in  = (unsigned char *)in_pixels;
    unsigned char *data_out = (unsigned char *)out_pixels;

    for (i = 0; i < size; i++) {
        // 할당
        int b = *data_in++; // 0xAARRGGBB
        int g = *data_in++; // 0xRR
        int r = *data_in++; // 0xGG
        int c = *data_in++; // 0xBB

        // 게산
        r *= 76; 
        g *= 151;
        b *= 29; 
        int y = (r + g + b) >> 8; // luminance

        // 저장
        *data_out++ = y;
        *data_out++ = y;
        *data_out++ = y;
        *data_out++ = c;
    }
}

