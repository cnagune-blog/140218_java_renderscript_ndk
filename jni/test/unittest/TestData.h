/**
 * @file    TestData.h
 * @date    2013-12-15
 * @author  cnagune (blog@cnagune.pe.kr)
 * @brief   테스트 데이터 단위 클래스. 내부에 data 배열에 대한 복사본을 가짐.
 */

#ifndef __TESTDATA_H__
#define __TESTDATA_H__


class TestData {
    private:
        char *dataName;             /// 데이터 이름
        unsigned char *inputData;   /// ARGB8888 형태의 배열
        unsigned char *outputData;  /// 출력될 배열
        int size;                   /// 픽셀 길이 (바이트는 4배수로 계산해야 함)

    public:
        TestData(const char *dataName, const unsigned char *inputData, const unsigned char *outputData, int size);
        ~TestData();

        char *getDataName();
        unsigned char *getInputData();
        unsigned char *getOutputData();
        int getSize();
};


#endif  /*__TESTDATA_H__ */

