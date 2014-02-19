/**
 * @file    TestData.cpp
 * @date    2013-12-15
 * @author  cnagune (blog@cnagune.pe.kr)
 * @brief   테스트 데이터 단위 클래스. 내부에 data 배열에 대한 복사본을 가짐.
 */

#include <cstring>
#include "TestData.h"


/**
 * @brief 입력받은 데이터에 대한 사본을 저장한다
 *
 * @param dataName 데이터에 대한 이름
 * @param inputData 입력 데이터 (ARGB 대응)
 * @param outputData 출력 데이터 (GrayScale 값을 가짐, 단, ARGB 형태로 4바이트 단위임)
 * @param size 계산하고자 하는 픽셀 길이 (메모리는 4배)
 */
TestData::TestData(const char *dataName, const unsigned char *inputData, const unsigned char *outputData, int size)
{
    // 1. 메모리 할당
    this->dataName = new char [std::strlen(dataName)];
    this->inputData = new unsigned char[size * 4];
    this->outputData = new unsigned char[size * 4];

    // 2. 값 대입
    std::strcpy(this->dataName, dataName);
    std::memcpy(this->inputData, inputData, size * 4);
    std::memcpy(this->outputData, outputData, size * 4);
    this->size = size;
}


TestData::~TestData()
{
    delete dataName;
    delete inputData;
    delete outputData;
}


char *TestData::getDataName()
{
    return dataName;
}


unsigned char *TestData::getInputData()
{
    return inputData;
}


unsigned char *TestData::getOutputData()
{
    return outputData;
}


int TestData::getSize()
{
    return size;
}

