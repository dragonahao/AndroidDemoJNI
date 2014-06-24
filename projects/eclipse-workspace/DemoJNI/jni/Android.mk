NB_LOCAL_PATH := $(call my-dir)

#----------------------------------
#- Compilar libreria para Android
#----------------------------------
include $(CLEAR_VARS)
LOCAL_PATH              := $(NB_LOCAL_PATH)
LOCAL_MODULE            := lectorassets    
LOCAL_LDLIBS			:= -llog -landroid

LOCAL_C_INCLUDES		:= $(LOCAL_PATH)/../../../../src/

LOCAL_SRC_FILES         := demo_marcos_ortega_jni_AppNativo.cpp /../../../../src/LectorAssets.cpp
include $(BUILD_SHARED_LIBRARY)
