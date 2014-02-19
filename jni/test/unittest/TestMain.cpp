/**
 * @file    TestMain.cpp
 * @date    2013-12-15
 * @author  cnagune (blog@cnagune.pe.kr)
 * @brief   gtest를 이용한 테스트의 시작 부분
 */


#include <gtest/gtest.h>

int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}

