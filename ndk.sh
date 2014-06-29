#/bin/bash

FILE_NAME=librs-jni.jar

ndk-build clean
ndk-build
zip -r libs/$FILE_NAME lib 

