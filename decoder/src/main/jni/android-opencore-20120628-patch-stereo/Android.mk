ifneq ($(BUILD_WITHOUT_PV),true)
LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

# Set up the PV variables
include $(LOCAL_PATH)/Config.mk

include $(PV_TOP)/build_config/opencore_dynamic/Android_opencore_common.mk
include $(PV_TOP)/build_config/opencore_dynamic/Android_omx_sharedlibrary.mk
include $(PV_TOP)/build_config/opencore_dynamic/Android_omx_avcdec_sharedlibrary.mk
include $(PV_TOP)/build_config/opencore_dynamic/Android_omx_m4vdec_sharedlibrary.mk
include $(PV_TOP)/build_config/opencore_dynamic/Android_omx_aacdec_sharedlibrary.mk
include $(PV_TOP)/build_config/opencore_dynamic/Android_omx_amrdec_sharedlibrary.mk
include $(PV_TOP)/build_config/opencore_dynamic/Android_omx_mp3dec_sharedlibrary.mk
include $(PV_TOP)/build_config/opencore_dynamic/Android_omx_avcenc_sharedlibrary.mk
include $(PV_TOP)/build_config/opencore_dynamic/Android_omx_m4venc_sharedlibrary.mk
include $(PV_TOP)/build_config/opencore_dynamic/Android_omx_amrenc_sharedlibrary.mk
include $(PV_TOP)/build_config/opencore_dynamic/Android_opencore_net_support.mk
include $(PV_TOP)/build_config/opencore_dynamic/Android_opencore_player.mk
include $(PV_TOP)/build_config/opencore_dynamic/Android_opencore_downloadreg.mk
include $(PV_TOP)/build_config/opencore_dynamic/Android_opencore_download.mk
include $(PV_TOP)/build_config/opencore_dynamic/Android_opencore_streamingreg.mk
include $(PV_TOP)/build_config/opencore_dynamic/Android_opencore_streaming.mk
include $(PV_TOP)/build_config/opencore_dynamic/Android_opencore_mp4localreg.mk
include $(PV_TOP)/build_config/opencore_dynamic/Android_opencore_mp4local.mk
include $(PV_TOP)/build_config/opencore_dynamic/Android_pvoma1passthru.mk
include $(PV_TOP)/build_config/opencore_dynamic/Android_opencore_rtsp.mk
include $(PV_TOP)/build_config/opencore_dynamic/Android_pvrtspunicast_streaming.mk
include $(PV_TOP)/build_config/opencore_dynamic/Android_pvrtspunicast_streamingreg.mk
include $(PV_TOP)/build_config/opencore_dynamic/Android_pvrtsptunicast_streaming.mk
include $(PV_TOP)/build_config/opencore_dynamic/Android_pvrtsptunicast_streamingreg.mk
include $(PV_TOP)/build_config/opencore_dynamic/Android_opencore_author.mk
include $(PV_TOP)/build_config/opencore_dynamic/Android_opencore_pvme.mk
ifeq ($(BUILD_PV_2WAY),1)
include $(PV_TOP)/build_config/opencore_dynamic/Android_opencore_2way.mk
endif
include $(PV_TOP)/oscl/unit_test/Android.mk
 include $(PV_TOP)/oscl/unit_test_utils/Android.mk
 include $(PV_TOP)/fileformats/avi/parser/Android.mk
 include $(PV_TOP)/pvmi/media_io/pvmi_mio_avi_wav_fileinput/Android.mk
ifeq ($(BUILD_PV_TEST_APPS),1)
include $(PV_TOP)/engines/player/test/Android.mk
include $(PV_TOP)/engines/author/test/Android.mk
include $(PV_TOP)/engines/2way/sample_app/command_line/Android.mk
include $(PV_TOP)/codecs_v2/omx/omx_testapp/Android.mk
include $(PV_TOP)/codecs_v2/omx/omx_testapp_enc/Android.mk
include $(PV_TOP)/engines/pvme/test/Android.mk
ifeq ($(BUILD_PV_2WAY),1)
include $(PV_TOP)/engines/2way/test/Android.mk
endif
endif
-include $(PV_TOP)/extern_libs_v2/android/extended_features/Android.mk

endif
