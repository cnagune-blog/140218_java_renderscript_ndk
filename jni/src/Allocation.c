/**
 * @file     Allocation.c
 * @date     2013-12-07
 * @author   cnagune (blog@cnagune.pe.kr)
 * @brief    메모리 할당, 해제, 복사, 반환 등을 수행한다
 * @warning  Finalize()를 수행하지 않으면 힙 메모리 계속 사용
 */

#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <stdbool.h>
#include "Allocation.h"


static void *g_in = NULL;   /// in 메모리 영역
static void *g_out = NULL;  /// out 메모리 영역


/*********************************************************
 * 메모리 얻는 함수들
 *********************************************************/

/**
 * @brief in 메모리 포인터 반환
 *
 * @return in 메모리 포인터
 */
void *get_in_memory()
{
    return g_in;
}


/**
 * @brief out 메모리 포인터 반환
 *
 * @return out 메모리 포인터
 */
void *get_out_memory()
{
    return g_out;
}


/*********************************************************
 * 메모리 초기화 함수들
 *********************************************************/

/**
 * @brief 메모리 초기화
 */
void initialize()
{
    if (g_in) {
        free(g_in);
        g_in = NULL;
    }

    if (g_out) {
        free(g_out);
        g_out = NULL;
    }
}


/**
 * @brief 메모리 정리 (초기화와 로직이 같음)
 */
void finalize()
{
    initialize();
}


/*********************************************************
 * 메모리 할당 및 복사 관련 함수들
 *********************************************************/

/**
 * @brief in 메모리 할당 및 pixels 배열 복사 (size * 4)
 *
 * @param pixels in 메모리에 복사할 배열
 * @param size pixels에서 in으로 복사할 픽셀 길이 (4배로 복사)
 */
void copy_to_in(const void *pixels, int size)
{
    const int mem_size = size * 4;

    // 0. 유효성 검사
    if (pixels == NULL || size <= 0) {
        return;
    }

    // 1. 메모리가 이미 할당되어 있으면 해지
    if (g_in != NULL) {
        free(g_in);
    }

    // 2. 메모리 할당
    g_in = (void *)malloc(mem_size);

    // 3. 메모리 공간 복사
    memcpy(g_in, pixels, mem_size);
}


/**
 * @brief out 메모리 할당 (size * 4)
 *
 * @param size 할당될 메모리에 대한 픽셀 길이 (4배로 할당)
 */
void create_memory_to_out(int size)
{
    const int mem_size = size * 4;

    // 0. 유효성 검사
    if (size <= 0) {
        return;
    }

    // 1. 메모리가 이미 할당되어 있으면 해지
    if (g_out != NULL) {
        free(g_out);
    }

    // 2. 메모리 할당
    g_out = (void *)malloc(mem_size);
}


/**
 * @brief out 메모리의 내용을 pixels 배열로 복사 (size * 4)
 *
 * @param pixels out 메모리에서부터 복사될 배열
 * @param size out 메모리로부터 복사할 픽셀 길이 (4배로 복사)
 */
void copy_from_out(void *pixels, int size)
{
    const int mem_size = size * 4;

    // 0. 유효성 검사
    if (g_out == NULL || pixels == NULL) {
        return;
    }

    // 1. 메모리 복사
    memcpy(pixels, g_out, mem_size);
}


