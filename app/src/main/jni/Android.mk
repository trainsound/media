LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE := medialib
LOCAL_SRC_FILES := medialibrary.cpp
LOCAL_LDLIBS := -llog
include $(BUILD_SHARED_LIBRARY)
