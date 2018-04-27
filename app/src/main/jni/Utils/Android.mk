LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE := medialib

FILE_LIST := $(wildcard $(LOCAL_PATH)/jni/*.cpp)
LOCAL_SRC_FILES := $(FILE_LIST:$(LOCAL_PATH)/%=%)

LOCAL_LDLIBS := -llog -pthread
include $(BUILD_SHARED_LIBRARY)
