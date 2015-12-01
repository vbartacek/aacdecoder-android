LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)


LOCAL_WHOLE_STATIC_LIBRARIES := \
	libpvoma1passthruplugin \
 	libpvoma1passthruplugininterface

LOCAL_MODULE := libpvoma1passthru

LOCAL_PRELINK_MODULE := false

-include $(PV_TOP)/Android_system_extras.mk

LOCAL_SHARED_LIBRARIES +=   libopencore_player libopencore_common

include $(BUILD_SHARED_LIBRARY)
include   $(PV_TOP)/pvmi/content_policy_manager/plugins/oma1/passthru/Android.mk
include   $(PV_TOP)/modules/cpm_oma1_passthru/Android.mk

