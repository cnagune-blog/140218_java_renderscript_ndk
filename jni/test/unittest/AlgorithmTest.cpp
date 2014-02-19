/**
 * @file    AlgorithmTest.cpp
 * @date    2013-12-16
 * @author  cnagune (blog@cnagune.pe.kr)
 * @brief   Algorithm 관련 테스트 수행
 */

#include <gtest/gtest.h>
#include <cstring>
#include "AlgorithmTest.h"
#include "Allocation.h"
#include "algorithm/Argb8888_To_Gray.h"
#include "algorithm/Argb8888_To_Gray_Neon.h"
#include "algorithm/Argb8888_To_Gray_Thread.h"
#include "algorithm/Argb8888_To_Gray_Neon_Thread.h"
#include "algorithm/Argb8888_To_Gray_Neon_Thread_Direct.h"


/**
 * @brief 테스트 수행 전 호출. 메모리 초기화 작업을 수행한다.
 */
void AlgorithmTest::SetUp()
{
    initialize();
}


/**
 * @brief 테스트 수행 후 호출. 메모리 정리 작업을 한다.
 */
void AlgorithmTest::TearDown()
{
    finalize();
}


/**
 * @brief Argb8888_to_gray 관련 함수 수행
 */
TEST (AlgorithmTest, Argb8888_to_gray)
{
    for (auto data : TestDataPool::GetDataList()) {
        // 1. 데이터 준비
        copy_to_in(data->getInputData(), data->getSize());
        create_memory_to_out(data->getSize());
        
        // 2. 알고리즘 호출
        argb8888_to_gray(get_in_memory(), get_out_memory(), data->getSize());

        // 3. 결과 얻기
        unsigned char *pixels = new unsigned char [data->getSize() * 4];
        copy_from_out(pixels, data->getSize());

        // 4. 비교
        ASSERT_TRUE(std::memcmp(data->getOutputData(), pixels, data->getSize() * 4) == 0);

        // 5. 정리
        delete [] pixels;
    }
}


#ifdef __ARM_NEON__
/**
 * @brief Argb8888_to_gray_neon 관련 함수 수행 (arm neon 전용)
 */
TEST (AlgorithmTest, Argb8888_to_gray_neon)
{
    for (auto data : TestDataPool::GetDataList()) {
        // 1. 데이터 준비
        copy_to_in(data->getInputData(), data->getSize());
        create_memory_to_out(data->getSize());
        
        // 2. 알고리즘 호출
        argb8888_to_gray_neon(get_in_memory(), get_out_memory(), data->getSize());

        // 3. 결과 얻기
        unsigned char *pixels = new unsigned char [data->getSize() * 4];
        copy_from_out(pixels, data->getSize());

        // 4. 비교
        ASSERT_TRUE(std::memcmp(data->getOutputData(), pixels, data->getSize() * 4) == 0);

        // 5. 정리
        delete [] pixels;
    }
}
#endif


/**
 * @brief Argb8888_to_gray_thread 관련 함수 수행
 */
TEST (AlgorithmTest, Argb8888_to_gray_thread)
{
    for (auto data : TestDataPool::GetDataList()) {
        // 1. 데이터 준비
        copy_to_in(data->getInputData(), data->getSize());
        create_memory_to_out(data->getSize());
        
        // 2. 알고리즘 호출
        argb8888_to_gray_thread(get_in_memory(), get_out_memory(), data->getSize(), 4);

        // 3. 결과 얻기
        unsigned char *pixels = new unsigned char [data->getSize() * 4];
        copy_from_out(pixels, data->getSize());

        // 4. 비교
        ASSERT_TRUE(std::memcmp(data->getOutputData(), pixels, data->getSize() * 4) == 0);

        // 5. 정리
        delete [] pixels;
    }
}


#ifdef __ARM_NEON__
/**
 * @brief Argb8888_to_gray_neon_thread 관련 함수 수행 (arm neon 전용)
 */
TEST (AlgorithmTest, Argb8888_to_gray_neon_thread)
{
    for (auto data : TestDataPool::GetDataList()) {
        // 1. 데이터 준비
        copy_to_in(data->getInputData(), data->getSize());
        create_memory_to_out(data->getSize());
        
        // 2. 알고리즘 호출
        argb8888_to_gray_neon_thread(get_in_memory(), get_out_memory(), data->getSize(), 4);

        // 3. 결과 얻기
        unsigned char *pixels = new unsigned char [data->getSize() * 4];
        copy_from_out(pixels, data->getSize());

        // 4. 비교
        ASSERT_TRUE(std::memcmp(data->getOutputData(), pixels, data->getSize() * 4) == 0);

        // 5. 정리
        delete [] pixels;
    }
}


/**
 * @brief Argb8888_to_gray_neon_thread_direct 관련 함수 수행 (arm neon 전용)
 */
TEST (AlgorithmTest, Argb8888_to_gray_neon_thread_direct)
{
    for (auto data : TestDataPool::GetDataList()) {
        // 1. 데이터 준비
        unsigned char *pixels = new unsigned char [data->getSize() * 4];

        // 2. 알고리즘 호출
        argb8888_to_gray_neon_thread_direct(data->getInputData(), pixels, data->getSize(), 4);

        // 3. 비교
        ASSERT_TRUE(std::memcmp(data->getOutputData(), pixels, data->getSize() * 4) == 0);

        // 4. 정리
        delete [] pixels;
    }
}
#endif
