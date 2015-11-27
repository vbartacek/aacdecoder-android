LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)


LOCAL_WHOLE_STATIC_LIBRARIES := \
	libcpm \
 	libpvpvxparser \
 	libpvid3parcom \
 	libpvamrffparsernode \
 	libpvamrffrecognizer \
 	libpvplsffrecognizer \
 	libpvmp3ff \
 	libpvmp3ffparsernode \
 	libpvmp3ffrecognizer \
 	libpvmp4ff \
 	libmp4recognizer_utility \
 	libpvaacparser \
 	libpvaacffparsernode \
 	libpvaacffrecognizer \
 	libpvwavffparsernode \
 	libpvwavffrecognizer \
 	libpvcommonparsernode \
 	libaudioparser \
 	libamrparser \
 	libwavparser \
 	libpvmfrecognizer \
 	libpvframemetadatautility \
 	libpvplayer_engine

LOCAL_WHOLE_STATIC_LIBRARIES +=  libandroidpv

LOCAL_MODULE := libopencore_player
ifeq ($(PLATFORM_VERSION),1.5)
    LOCAL_SHARED_LIBRARIES :=  libutils libcutils libui libhardware libandroid_runtime libdrm1 libmedia libsgl libvorbisidec libsonivox liblog libicuuc
else ifeq ($(PLATFORM_VERSION),1.6)
    LOCAL_SHARED_LIBRARIES :=  libutils libcutils libui libhardware libandroid_runtime libdrm1 libmedia libsgl libvorbisidec libsonivox liblog libicuuc
else ifeq ($(PLATFORM_VERSION),2.1)
    LOCAL_SHARED_LIBRARIES :=  libutils libcutils libui libhardware libandroid_runtime libdrm1 libmedia libskia libvorbisidec libsonivox liblog libicuuc libbinder
else
    LOCAL_SHARED_LIBRARIES :=  libutils libcutils libui libhardware libandroid_runtime libdrm1 libmedia libskia libvorbisidec libsonivox liblog libicuuc libbinder libsurfaceflinger_client libcamera_client
endif

-include $(PV_TOP)/Android_system_extras.mk

LOCAL_SHARED_LIBRARIES +=   libopencore_common libopencore_net_support

include $(BUILD_SHARED_LIBRARY)
include   $(PV_TOP)/pvmi/content_policy_manager/Android.mk
include   $(PV_TOP)/fileformats/pvx/parser/Android.mk
include   $(PV_TOP)/fileformats/id3parcom/Android.mk
include   $(PV_TOP)/nodes/pvamrffparsernode/Android.mk
include   $(PV_TOP)/pvmi/recognizer/plugins/pvamrffrecognizer/Android.mk
include   $(PV_TOP)/pvmi/recognizer/plugins/pvplsffrecognizer/Android.mk
include   $(PV_TOP)/fileformats/mp3/parser/Android.mk
include   $(PV_TOP)/nodes/pvmp3ffparsernode/Android.mk
include   $(PV_TOP)/pvmi/recognizer/plugins/pvmp3ffrecognizer/Android.mk
include   $(PV_TOP)/fileformats/mp4/parser/Android.mk
include   $(PV_TOP)/fileformats/mp4/parser/utils/mp4recognizer/Android.mk
include   $(PV_TOP)/fileformats/rawaac/parser/Android.mk
include   $(PV_TOP)/nodes/pvaacffparsernode/Android.mk
include   $(PV_TOP)/pvmi/recognizer/plugins/pvaacffrecognizer/Android.mk
include   $(PV_TOP)/nodes/pvwavffparsernode/Android.mk
include   $(PV_TOP)/pvmi/recognizer/plugins/pvwavffrecognizer/Android.mk
include   $(PV_TOP)/nodes/pvcommonparsernode/Android.mk
include   $(PV_TOP)/fileformats/audioparser/common/Android.mk
include   $(PV_TOP)/fileformats/audioparser/amr/Android.mk
include   $(PV_TOP)/fileformats/audioparser/wav/Android.mk
include   $(PV_TOP)/pvmi/recognizer/Android.mk
include   $(PV_TOP)/engines/adapters/player/framemetadatautility/Android.mk
include   $(PV_TOP)/engines/player/Android.mk
include $(PV_TOP)/android/Android.mk

