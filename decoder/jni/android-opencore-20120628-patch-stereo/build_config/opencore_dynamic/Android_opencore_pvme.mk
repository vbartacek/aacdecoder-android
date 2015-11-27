LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)


LOCAL_WHOLE_STATIC_LIBRARIES := \
 	libpvmetadata_engine

LOCAL_MODULE := libopencore_pvme

LOCAL_PRELINK_MODULE := false

-include $(PV_TOP)/Android_system_extras.mk

LOCAL_SHARED_LIBRARIES +=   libopencore_player libopencore_common

include $(BUILD_SHARED_LIBRARY)
include   $(PV_TOP)/engines/pvme/Android.mk

