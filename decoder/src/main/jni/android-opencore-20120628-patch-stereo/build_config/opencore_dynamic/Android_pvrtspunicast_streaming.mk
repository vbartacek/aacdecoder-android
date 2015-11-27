LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)


LOCAL_WHOLE_STATIC_LIBRARIES := \
	libpvrtspunicaststreamingmanager \
 	libpvrtspsmplugininterface

LOCAL_MODULE := libpvrtspunicast_streaming

LOCAL_PRELINK_MODULE := false

-include $(PV_TOP)/Android_system_extras.mk

LOCAL_SHARED_LIBRARIES +=   libopencore_net_support libopencore_player libopencore_common libopencore_rtsp libopencore_streaming

include $(BUILD_SHARED_LIBRARY)
include   $(PV_TOP)/nodes/streaming/streamingmanager/plugins/rtspunicast/Android.mk
include   $(PV_TOP)/modules/linux_rtsp/smplugins/unicast/core/Android.mk

