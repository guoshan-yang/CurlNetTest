
LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)  
LOCAL_MODULE := curl  
LOCAL_SRC_FILES := lib/$(TARGET_ARCH_ABI)/libcurl.so
include $(PREBUILT_SHARED_LIBRARY) 

include $(CLEAR_VARS)
LOCAL_C_INCLUDES := $(LOCAL_PATH)/include
LOCAL_MODULE := curlTest
LOCAL_SRC_FILES := src/DownloadModule.cpp \
	src/HttpPostModule.cpp \
	src/Main.cpp \
	src/JNIUtil.cpp
	
LOCAL_SHARED_LIBRARIES := curl
LOCAL_LDLIBS := -llog
include $(BUILD_SHARED_LIBRARY)

