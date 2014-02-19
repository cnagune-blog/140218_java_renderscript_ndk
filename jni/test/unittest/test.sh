#!/usr/bin/env bash

find -iname '*cmake*' -not -name CMakeLists.txt -not -name "toolchain.arm.cmake" -not -name "*svn*" -exec rm -rf {} \;

#if [[ `uname` = "Darwin" ]];
#then
#    cmake -DCMAKE_CXX_FLAGS="${CMAKE_CXX_FLAGS} -stdlib=libc++" .
#else
#    cmake .
#fi
cmake -DCMAKE_CXX_FLAGS="${CMAKE_CXX_FLAGS} -mfloat-abi=softfp -mfpu=neon" -DCMAKE_TOOLCHAIN_FILE=toolchain.arm.cmake .
make clean
make
#make test

