/**
 * @file    Gray_To_Argb8888.h
 * @date    2013-12-08
 * @author  cnagune (blog@cnagune.pe.kr)
 * @brief   일반 명령어를 사용하여 Grayscale 변환을 수행한다.
 */

#ifndef __GRAY_ARGB8888_H__
#define __GRAY_ARGB8888_H__

#ifdef __cplusplus 
extern "C" {
#endif


/// Grayscale 4bytes 변환 함수 - 일반 명령어
void gray_to_argb8888(const void *in_pixels, void *out_pixels, int size);


#ifdef __cplusplus 
}
#endif

#endif  /* __GRAY_ARGB8888_H__ */

