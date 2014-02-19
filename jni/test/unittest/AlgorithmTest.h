/**
 * @file    AlgorithmTest.h
 * @date    2013-12-16
 * @author  cnagune (blog@cnagune.pe.kr)
 * @brief   Algorithm 관련 테스트, 메모리 초기화 때문에 클래스 작성
 */

#ifndef __ALGORITHM_TEST_H__
#define __ALGORITHM_TEST_H__


#include <gtest/gtest.h>
#include "TestDataPool.h"


class AlgorithmTest : public ::testing::Test {
    protected:
        virtual void SetUp();       /// 메모리 초기화
        virtual void TearDown();    /// 메모리 정리
};


#endif  /* __ALGORITHM_TEST_H__ */
