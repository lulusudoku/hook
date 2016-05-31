LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_LDLIBS := -llog

LOCAL_SRC_FILES := \
  hide.c

LOCAL_MODULE := hide
LOCAL_MODULE_TAGS := optional

include $(BUILD_SHARED_LIBRARY)

