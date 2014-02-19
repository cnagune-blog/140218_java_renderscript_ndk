/**
 * @file     Allocation.h
 * @date     2013-12-07
 * @author   cnagune (blog@cnagune.pe.kr)
 * @brief    메모리 할당, 해제, 복사, 반환 등을 수행한다
 * @warning  Finalize()를 수행하지 않으면 힙 메모리 계속 사용
 */

#ifndef __ALLOCATION_H__
#define __ALLOCATION_H__

#ifdef __cplusplus 
extern "C" {
#endif


/*********************************************************
 * 메모리 얻는 함수들
 *********************************************************/
void *get_in_memory();    /// in 메모리 포인터 반환
void *get_out_memory();   /// out 메모리 포인터 반환


/*********************************************************
 * 메모리 초기화 함수들
 *********************************************************/
void initialize();      /// 메모리 초기화
void finalize();        /// 메모리 정리


/*********************************************************
 * 메모리 할당 및 복사 관련 함수들
 *********************************************************/
void copy_to_in(const void *pixels, int size);    /// in 메모리 할당 및 pixels 배열 복사 (size * 4)
void create_memory_to_out(int size);               /// out 메모리 할당 (size * 4)
void copy_from_out(void *pixels, int size);       /// out 메모리의 내용을 pixels 배열로 복사 (size * 4)


#ifdef __cplusplus 
}
#endif

#endif  /* __ALLOCATION_H__ */

