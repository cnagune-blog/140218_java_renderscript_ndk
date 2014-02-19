/**
 * @file    Argb8888_To_Gray.h
 * @date    2013-12-08
 * @author  cnagune (blog@cnagune.pe.kr)
 * @brief   일반 명령어를 사용하여 Grayscale 변환을 수행한다.
 */

#ifndef __ARGB8888_GRAY_H__
#define __ARGB8888_GRAY_H__

#ifdef __cplusplus 
extern "C" {
#endif


/// Grayscale 변환 함수 - 일반 명령어
void argb8888_to_gray(void *in_pixels, void *out_pixels, int size);


#ifdef __cplusplus 
}
#endif

#endif  /* __ARGB8888_GRAY_H__ */

