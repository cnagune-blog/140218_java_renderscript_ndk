/**
 * @file    Argb8888_To_Gray_Neon.c
 * @date    2013-12-08
 * @author  cnagune (blog@cnagune.pe.kr)
 * @brief   NEON 명령어를 사용하여 Grayscale 변환을 수행한다.
 */

#ifdef __ARM_NEON__
#include <arm_neon.h>
#include "Allocation.h"
#include "algorithm/Argb8888_To_Gray.h"
#include "algorithm/Argb8888_To_Gray_Neon.h"


/**
 * @brief Grayscale 변환 함수 - NEON 명령어
 *
 * @param in_pixels 원본 이미지에 대한 ARGB8888 형식의 배열
 * @param out_pixels 결과 이미지를 저장할 배열
 * @param size 계산하고자 하는 픽셀 길이 (메모리는 4배)
 */
void argb8888_to_gray_neon(void *in_pixels, void *out_pixels, int size)
{
    uint8x8_t rfac = vdup_n_u8(76);
    uint8x8_t gfac = vdup_n_u8(151);
    uint8x8_t bfac = vdup_n_u8(29);
    int n = size / 8;
    int m = size % 8;

    int iTemp;
    unsigned char szTemp[8];
    unsigned int *data_in  = (unsigned int *)in_pixels;
    unsigned int *data_out = (unsigned int *)out_pixels;

    // 한 루프당 8픽셀씩 변환 (32 bytes)
    while (n--) {
        uint16x8_t  temp;
        uint8x8x4_t rgb  = vld4_u8 ((unsigned char *)data_in);
        uint8x8_t result;

        temp = vmull_u8(rgb.val[0],       bfac);
        temp = vmlal_u8(temp, rgb.val[1], gfac);
        temp = vmlal_u8(temp, rgb.val[2], rfac);

        result = vshrn_n_u16 (temp, 8);
        vst1_u8(szTemp, result);

        iTemp = szTemp[0]; *data_out = iTemp | (iTemp << 8) | (iTemp << 16) | (*data_in & 0xff000000); data_in++; data_out++;
        iTemp = szTemp[1]; *data_out = iTemp | (iTemp << 8) | (iTemp << 16) | (*data_in & 0xff000000); data_in++; data_out++;
        iTemp = szTemp[2]; *data_out = iTemp | (iTemp << 8) | (iTemp << 16) | (*data_in & 0xff000000); data_in++; data_out++;
        iTemp = szTemp[3]; *data_out = iTemp | (iTemp << 8) | (iTemp << 16) | (*data_in & 0xff000000); data_in++; data_out++;
        iTemp = szTemp[4]; *data_out = iTemp | (iTemp << 8) | (iTemp << 16) | (*data_in & 0xff000000); data_in++; data_out++;
        iTemp = szTemp[5]; *data_out = iTemp | (iTemp << 8) | (iTemp << 16) | (*data_in & 0xff000000); data_in++; data_out++;
        iTemp = szTemp[6]; *data_out = iTemp | (iTemp << 8) | (iTemp << 16) | (*data_in & 0xff000000); data_in++; data_out++;
        iTemp = szTemp[7]; *data_out = iTemp | (iTemp << 8) | (iTemp << 16) | (*data_in & 0xff000000); data_in++; data_out++;
    }

    if (m) {
        argb8888_to_gray(data_in, data_out, m);
    }
}

#endif  /* __ARM_NEON__ */

