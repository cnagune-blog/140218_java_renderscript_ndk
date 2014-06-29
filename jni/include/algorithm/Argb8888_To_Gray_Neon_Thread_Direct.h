/**
 * @file    Argb8888_To_Gray_Neon_Thread_Direct.h
 * @date    2013-12-08
 * @author  cnagune (blog@cnagune.pe.kr)
 * @brief   NEON 명령어와 Thread를 사용하여 Grayscale 변환을 수행한다.
 *          in, out 메모리가 아닌 Bitmap 메모리로 바로 접근한다
 */

#ifndef __ARGB8888_GRAY_NEON_THREAD_DIRECT_H__
#define __ARGB8888_GRAY_NEON_THREAD_DIRECT_H__

#ifdef __cplusplus 
extern "C" {
#endif


/// Grayscale 변환 함수 - NEON 명령어와 Thread 사용, bitmap 직접 제어
void argb8888_to_gray_neon_thread_direct(const void *in_pixels, void *out_pixels, int size, int thread_cnt);


#ifdef __cplusplus 
}
#endif

#endif  /* __ARGB8888_GRAY_NEON_THREAD_DIRECT_H__ */

