LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)


LOCAL_WHOLE_STATIC_LIBRARIES := \
 	libpvrtspsmpluginreginterface

LOCAL_MODULE := libpvrtspunicast_streamingreg

LOCAL_PRELINK_MODULE := false

-include $(PV_TOP)/Android_system_extras.mk

LOCAL_SHARED_LIBRARIES +=   libopencore_common libopencore_streaming

include $(BUILD_SHARED_LIBRARY)
include   $(PV_TOP)/modules/linux_rtsp/smplugins/unicast/registry/Android.mk

