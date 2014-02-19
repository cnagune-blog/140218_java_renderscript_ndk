/**
 * @file    AllocationTest.cpp
 * @date    2013-12-16
 * @author  cnagune (blog@cnagune.pe.kr)
 * @brief   Allocation 관련 테스트 수행
 */

#include <gtest/gtest.h>
#include <cstring>
#include "AllocationTest.h"
#include "Allocation.h"



/**
 * @brief 테스트 수행 전 호출. 메모리 초기화 작업을 수행한다.
 */
void AllocationTest::SetUp()
{
    initialize();
}


/**
 * @brief 테스트 수행 후 호출. 메모리 정리 작업을 한다.
 */
void AllocationTest::TearDown()
{
    finalize();
}


/**
 * @brief Copy_To_In 함수 테스트를 수행
 *        메모리 복사가 제대로 수행되었는지 확인한다.
 */
TEST (AllocationTest, Copy_To_In)
{
    for (auto data : TestDataPool::GetDataList()) {
        // 1. Copy_To_In 으로 대입
        copy_to_in(data->getInputData(), data->getSize());

        // 2. 비교
        ASSERT_TRUE(std::memcmp(get_in_memory(), data->getInputData(), data->getSize() * 4) == 0);
    }
}


/**
 * @brief Copy_From_Out 함수 테스트를 수행
 *        쓰레기 값이라도 비교한다.
 */
TEST (AllocationTest, Copy_From_Out)
{
    for (auto data : TestDataPool::GetDataList()) {
        // 1. Create_Memory_To_Out 으로 메모리 할당
        create_memory_to_out(data->getSize());

        // 2. pixels 빈 배열 할당
        unsigned char *pixels = new unsigned char [data->getSize() * 4];

        // 3. 호출
        copy_from_out(pixels, data->getSize());

        // 4. 비교 (쓰레기 값을 비교하는 방식)
        ASSERT_TRUE(std::memcmp(get_out_memory(), pixels, data->getSize() * 4) == 0);

        // 5. 해제
        delete pixels;
    }
}

