/**
 * @file    TestData.h
 * @date    2013-12-16
 * @author  cnagune (blog@cnagune.pe.kr)
 * @brief   테스트 데이터 모음 클래스. TestData 객체의 집합을 가짐
 */

#ifndef __TEST_DATA_POOL_H__
#define __TEST_DATA_POOL_H__


#include <list>
#include <memory>
#include "TestData.h"

/**
 * @brief TestData에 대한 집합을 가지는 namespace
 */
namespace TestDataPool {
    std::list<std::shared_ptr<TestData>> GetDataList(); /// 테스트 데이터에 대한 list 얻음
};


#endif /* __TEST_DATA_POOL_H__ */

