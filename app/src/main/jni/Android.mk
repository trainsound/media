LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE := medialib

FILE_LIST := $(wildcard $(LOCAL_PATH)/jni/*.cpp)
UTILS_DIR := $(wildcard $(LOCAL_PATH)/Utils/*.cpp)
DECODE_DIR := $(wildcard $(LOCAL_PATH)/Decode/*.cpp)
RENDER_DIR := $(wildcard $(LOCAL_PATH)/Render/*.cpp)

LOCAL_SRC_FILES := $(FILE_LIST:$(LOCAL_PATH)/%=%) $(UTILS_DIR:$(LOCAL_PATH)/%=%) $(DECODE_DIR:$(LOCAL_PATH)/%=%) $(RENDER_DIR:$(LOCAL_PATH)/%=%)

LOCAL_LDLIBS := -llog -pthread
include $(BUILD_SHARED_LIBRARY)
