
include $(MK)/entry_point.mk

FORMAT := android

include $(CFG_DIR)/../common/local.mk

TESTAPPS="pvplayer_engine_test test_pvauthorengine pv2way_engine_test pv2way_console_app test_omx_client test_omxenc_client pvme_test"
TESTAPP_DIR_pvplayer_engine_test="/engines/player/test/build/android"
TESTAPP_DIR_test_pvauthorengine="/engines/author/test/build/android"
TESTAPP_DIR_pv2way_engine_test="/engines/2way/test/build/make"
TESTAPP_DIR_pv2way_console_app="/engines/2way/sample_app/command_line/build/make"
TESTAPP_DIR_test_omx_client="/codecs_v2/omx/omx_testapp/build/android"
TESTAPP_DIR_test_omxenc_client="/codecs_v2/omx/omx_testapp_enc/build/android"
TESTAPP_DIR_pvme_test="/engines/pvme/test/build/make"

opencore_common_PRELINK := true
opencore_player_PRELINK := true
opencore_author_PRELINK := true

include $(MK)/cml2_parser.mk

