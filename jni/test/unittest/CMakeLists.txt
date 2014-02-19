# 만든이: blog@cnagune.pe.kr
cmake_minimum_required(VERSION 2.6)
project(GrayScaleUnitTest)


# 플래그 설정 - gcov 관련
set(CMAKE_EXE_LINKER_FLAGS "-fprofile-arcs -ftest-coverage")
add_definitions("-std=c++0x")


# GTest 추가
set(GTEST_DIR ${CMAKE_SOURCE_DIR}/externals/gtest)
set(GTEST_SRC ${GTEST_DIR}/src/gtest-all.cc ${GTEST_DIR}/src/gtest_main.cc)
set(GTEST_INCLUDE ${GTEST_DIR} ${GTEST_DIR}/include)
include_directories(${GTEST_INCLUDE})
add_library(gtest ${GTEST_SRC})


# 테스트 할 library, include 등 추가
set(TARGET_DIR ${CMAKE_SOURCE_DIR}/../..)
set(TARGET_INCLUDE ${TARGET_DIR}/include)
file(GLOB TARGET_LIBRARY "${TARGET_DIR}/build/lib*.a")
#set(TARGET_LIBRARY ${CMAKE_SOURCE_DIR}/../../build/libRs-jni.a)
#set(TARGET_LIBRARY ../../build/libRs-jni.a)
include_directories(${TARGET_INCLUDE})


# 테스트 항목 파일 추가
file(GLOB TEST_FILES "*.cpp")
add_executable(runTests ${TEST_FILES})


# 최종 컴파일!
find_package (Threads REQUIRED)
target_link_libraries(runTests gtest ${CMAKE_THREAD_LIBS_INIT} ${TARGET_LIBRARY})


# make test 재정의 (ctest -> gtest)
add_custom_target(test)
add_custom_target(custom_test
    COMMAND runTests #cmake 2.6 required
    DEPENDS runTests
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}")
add_dependencies(test custom_test)



# http://kldp.org/node/122815
# http://stackoverflow.com/questions/7262370/unit-test-output-project-structure-advice-cmake-google-test-framework
