/**
 * @file    Argb8888_To_Gray_Thread.h
 * @date    2013-12-08
 * @author  cnagune (blog@cnagune.pe.kr)
 * @brief   일반 명령어와 Thread를 사용하여 Grayscale 변환을 수행한다.
 */

#ifndef __ARGB8888_GRAY_THREAD_H__
#define __ARGB8888_GRAY_THREAD_H__

#ifdef __cplusplus 
extern "C" {
#endif


/// Grayscale 변환 함수 - 일반 명령어와 Thread 사용
void argb8888_to_gray_thread(void *in_pixels, void *out_pixels, int size, int thread_num);


#ifdef __cplusplus 
}
#endif

#endif  /* __ARGB8888_GRAY_THREAD_H__ */

