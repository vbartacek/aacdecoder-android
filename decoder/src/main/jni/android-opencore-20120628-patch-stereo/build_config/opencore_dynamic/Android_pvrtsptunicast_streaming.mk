LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)


LOCAL_WHOLE_STATIC_LIBRARIES := \
	libpvsmrtsptstreamingplugin \
 	libpvrtsptunicaststreamingmanager

LOCAL_MODULE := libpvrtsptunicast_streaming

LOCAL_PRELINK_MODULE := false

-include $(PV_TOP)/Android_system_extras.mk

LOCAL_SHARED_LIBRARIES +=   libopencore_net_support libopencore_player libopencore_common libopencore_rtsp libopencore_streaming

include $(BUILD_SHARED_LIBRARY)
include   $(PV_TOP)/modules/linux_rtsp/smplugins/tunneling/core/Android.mk
include   $(PV_TOP)/nodes/streaming/streamingmanager/plugins/rtsptunicast/Android.mk

