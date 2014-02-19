#/bin/bash

FILE_NAME=librs-jni.jar


ndk-build
zip -r libs/$FILE_NAME lib 

