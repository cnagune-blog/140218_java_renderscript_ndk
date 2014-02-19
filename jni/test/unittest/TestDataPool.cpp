/**
 * @file    TestData.cpp
 * @date    2013-12-16
 * @author  cnagune (blog@cnagune.pe.kr)
 * @brief   테스트 데이터 모음 클래스. TestData 객체의 집합을 가짐
 */

#include <memory>
#include <cstring>
#include "TestDataPool.h"


/**
 * @brief 테스트 데이터에 대한 입출력 등의 데이터를 리스트의 형태로 제공한다.
 *
 * @return 테스트 데이터에 대한 list
 */
std::list<std::shared_ptr<TestData>> TestDataPool::GetDataList()
{
    std::list<std::shared_ptr<TestData>> dataPool;

    // 빨강(R) 1pixel
    {
        const unsigned char inputData[] = {0x00, 0x00, 0xff, 0xff};
        const unsigned char outputData[] = {0x4b, 0x4b, 0x4b, 0xff};
        std::shared_ptr<TestData> data(new TestData("1. Red 1pixel", inputData, outputData, 1));
        dataPool.push_back(data);
    }

    // 초록(G) 1pixel
    {
        const unsigned char inputData[] = {0x00, 0xff, 0x00, 0xff};
        const unsigned char outputData[] = {0x96, 0x96, 0x96, 0xff};
        std::shared_ptr<TestData> data(new TestData("2. Green 1pixel", inputData, outputData, 1));
        dataPool.push_back(data);
    }

    // 파랑(B) 1pixel
    {
        const unsigned char inputData[] = {0xff, 0x00, 0x00, 0xff};
        const unsigned char outputData[] = {0x1c, 0x1c, 0x1c, 0xff};
        std::shared_ptr<TestData> data(new TestData("3. Blue 1pixel", inputData, outputData, 1));
        dataPool.push_back(data);
    }

    // 검정 1pixel
    {
        const unsigned char inputData[] = {0x00, 0x00, 0x00, 0xff};
        const unsigned char outputData[] = {0x00, 0x00, 0x00, 0xff};
        std::shared_ptr<TestData> data(new TestData("4. Black 1pixel", inputData, outputData, 1));
        dataPool.push_back(data);
    }

    // 하양 1pixel
    {
        const unsigned char inputData[] = {0xff, 0xff, 0xff, 0xff};
        const unsigned char outputData[] = {0xff, 0xff, 0xff, 0xff};
        std::shared_ptr<TestData> data(new TestData("5. White 1pixel", inputData, outputData, 1));
        dataPool.push_back(data);
    }

    // RGB+BlackWhite 1개씩 5pixels
    {
        const unsigned char inputData[] = {
            0x00, 0x00, 0xff, 0xff,
            0x00, 0xff, 0x00, 0xff,
            0xff, 0x00, 0x00, 0xff,
            0x00, 0x00, 0x00, 0xff,
            0xff, 0xff, 0xff, 0xff
        };
        const unsigned char outputData[] = {
            0x4b, 0x4b, 0x4b, 0xff,
            0x96, 0x96, 0x96, 0xff,
            0x1c, 0x1c, 0x1c, 0xff,
            0x00, 0x00, 0x00, 0xff,
            0xff, 0xff, 0xff, 0xff
        };
        std::shared_ptr<TestData> data(new TestData("6. RGB+BlackWhite 1times == 5pixels", inputData, outputData, 5));
        dataPool.push_back(data);
    }

    // RGB+BlackWhite 1000개씩 5000pixels
    {
        const unsigned char inputData_chunk[] = {
            0x00, 0x00, 0xff, 0xff,
            0x00, 0xff, 0x00, 0xff,
            0xff, 0x00, 0x00, 0xff,
            0x00, 0x00, 0x00, 0xff,
            0xff, 0xff, 0xff, 0xff
        };
        const unsigned char outputData_chunk[] = {
            0x4b, 0x4b, 0x4b, 0xff,
            0x96, 0x96, 0x96, 0xff,
            0x1c, 0x1c, 0x1c, 0xff,
            0x00, 0x00, 0x00, 0xff,
            0xff, 0xff, 0xff, 0xff
        };

        unsigned char *inputData = new unsigned char [5000 * 4];
        unsigned char *outputData = new unsigned char [5000 * 4];

        for (int i = 0; i < 1000; i++) {
            std::memcpy(inputData + (i * 5 * 4), inputData_chunk, 5 * 4);
            std::memcpy(outputData + (i * 5 * 4), outputData_chunk, 5 * 4);
        }

        std::shared_ptr<TestData> data(new TestData("7. RGB+BlackWhite 1000times == 5000pixels", inputData, outputData, 5000));
        dataPool.push_back(data);

        delete [] inputData;
        delete [] outputData;
    }

    return dataPool;
}

