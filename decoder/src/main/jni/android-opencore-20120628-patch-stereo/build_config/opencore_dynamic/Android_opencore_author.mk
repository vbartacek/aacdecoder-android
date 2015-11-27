LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)


LOCAL_WHOLE_STATIC_LIBRARIES := \
	libpvmp4ffcomposer \
 	libpvmp4ffcomposernode \
 	libpvauthorengine

LOCAL_WHOLE_STATIC_LIBRARIES +=  libandroidpvauthor

LOCAL_MODULE := libopencore_author
ifeq ($(PLATFORM_VERSION),1.5)
    LOCAL_SHARED_LIBRARIES :=  libutils libcutils libui libandroid_runtime libmedia liblog libicuuc
else ifeq ($(PLATFORM_VERSION),1.6)
    LOCAL_SHARED_LIBRARIES :=  libutils libcutils libui libandroid_runtime libmedia liblog libicuuc
else ifeq ($(PLATFORM_VERSION),2.1)
    LOCAL_SHARED_LIBRARIES :=  libutils libcutils libui libandroid_runtime libmedia liblog libicuuc libbinder
else
    LOCAL_SHARED_LIBRARIES :=  libutils libcutils libui libandroid_runtime libmedia liblog libicuuc libbinder libsurfaceflinger_client libcamera_client
endif

-include $(PV_TOP)/Android_system_extras.mk

LOCAL_SHARED_LIBRARIES +=   libopencore_common

include $(BUILD_SHARED_LIBRARY)
include   $(PV_TOP)/fileformats/mp4/composer/Android.mk
include   $(PV_TOP)/nodes/pvmp4ffcomposernode/Android.mk
include   $(PV_TOP)/engines/author/Android.mk
include $(PV_TOP)/android/author/Android.mk

