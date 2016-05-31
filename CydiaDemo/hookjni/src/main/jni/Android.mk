LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE    := jInterfaceTrace_4.x
LOCAL_SRC_FILES := libjInterfaceTrace_4.x.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE    := parseMethod
LOCAL_SRC_FILES := libparseMethod.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE    := hookjni
LOCAL_SRC_FILES := FuckIt.c
LOCAL_STATIC_LIBRARIES := jInterfaceTrace_4.x \
				parseMethod
LOCAL_LDLIBS := -llog
include $(BUILD_SHARED_LIBRARY)