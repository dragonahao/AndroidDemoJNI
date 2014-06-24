#!/bin/sh

#Set the NDK path
export ANDROID_NDK_ROOT=/Applications/android-ndk-r8b

#Generate JNI interface "JAVA -> CLASS"
#javac  -d ./bin/classes/ ./src/demo/marcos/ortega/jni/AppNativo.java

#Generate JNI interface "CLASS -> C"
#javah -d ./jni -classpath ./bin/classes/ demo.marcos.ortega.jni.AppNativo

#$ANDROID_NDK_ROOT/ndk-build clean
$ANDROID_NDK_ROOT/ndk-build TARGET_PLATFORM=android-9 V=1 NDK_DEBUG=1
