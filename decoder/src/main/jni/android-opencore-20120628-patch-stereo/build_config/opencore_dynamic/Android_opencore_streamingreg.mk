LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)


LOCAL_WHOLE_STATIC_LIBRARIES := \
 	libpvsmreginterface

LOCAL_MODULE := libopencore_streamingreg

LOCAL_PRELINK_MODULE := false

-include $(PV_TOP)/Android_system_extras.mk

LOCAL_SHARED_LIBRARIES +=   libopencore_common

include $(BUILD_SHARED_LIBRARY)
include   $(PV_TOP)/modules/linux_rtsp/node_registry/Android.mk

