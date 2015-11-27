/* ------------------------------------------------------------------
 * Copyright (C) 1998-2009 PacketVideo
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied.
 * See the License for the specific language governing permissions
 * and limitations under the License.
 * -------------------------------------------------------------------
 */
//
// Automatically generated, don't edit
//

//
// PV Code Base Configuration System
//

//
// Menu for selecting supported features
//
#define module_support 1
#define PV_HAS_SHOUTCAST_SUPPORT_ENABLED 1


//
// Menu for configuring modules
//
#define pv_so 0
#define pvplayerservice_so 0
#define pvsplit_so 1
#define dynamic_loading_support 1
#define download_support 1
#define fasttrack_download_support 0
#define mp4local_support 1
#define mpeg2local_support 0
#define divxlocal_support 0
#define rmff_support 0
#define flvlocal_support 0
#define asflocal_support 0
#define playready_support 0
#define oma1_passthru_support 1
#define wmdrmoemsettings_support 0
#define pvdivxoemsettings_support 0
#define divxdrm_support 0
#define mtp_db_support 0
#define pvdb_config_support 0
#define mtp_config_support 0
#define mtp_drmmanagerplugin_support 0
#define usb_transport_support 0
#define dtcp_support 0


//
// Menu for configuring Baselibs
//
#define csprng_lib 0
#define pvcrypto_lib 0
#define pventropysrc_lib 0
#define pvgendatastruct_lib m
#define pvmediadatastruct_lib m
#define pvmimeutils_lib m
#define threadsafe_callback_ao_lib m
#define pvthreadmessaging_lib m
#define secure_data_format_lib 0


//
// Menu for configuring File Formats
//
#define pvasfff_lib 0
#define pvmp3ff_lib m
#define pvmp4ffcomposer_lib 0
#define pvmp4ffcomposeropencore_lib m
#define pvmp4ff_lib 0
#define pvmp4ffopencore_lib m
#define mp4recognizer_utility_lib m
#define pvaacparser_lib m
#define pvgsmamrparser_lib m
#define pvrmff_lib 0
#define pvrmffparser_lib 0
#define pvfileparserutils_lib m
#define pvid3parcom_lib m
#define pvpvxparser_lib m
#define pvwav_lib m
#define pvasxparser_lib 0
#define pvavifileparser_lib 1
#define pvpvrff_lib 0
#define asfrecognizer_utility_lib 0
#define pv_divxfile_parser_lib 0
#define scsp_lib m
#define divxrecognizer_utility_lib 0
#define pvflvff_lib 0
#define pvrmffrecognizer_utility_lib 0
#define flvrecognizer_utility_lib 0
#define pvmpeg2ff_lib 0
#define mpeg2recognizer_utility_lib 0
#define audioparser_lib m
#define amrparser_lib m
#define wavparser_lib m


//
// Menu for configuring Codecs
//

//
// Menu for configuring OMX Support
//
#define omx_mastercore_lib m
#define MAX_NUMBER_OF_OMX_CORES 10
#define MAX_NUMBER_OF_OMX_COMPONENTS 50
#define USE_DYNAMIC_LOAD_OMX_COMPONENTS 1
#define pv_omx 1
#define omx_avc_component_lib m
#define omx_common_lib m
#define omx_m4v_component_lib m
#define omx_queue_lib m
#define omx_wmv_component_lib 0
#define omx_rv_component_lib 0
#define pvomx_proxy_lib m
#define omx_aac_component_lib m
#define omx_amr_component_lib m
#define omx_mp3_component_lib m
#define omx_wma_component_lib 0
#define omx_ra_component_lib 0
#define omx_amrenc_component_lib m
#define omx_m4venc_component_lib m
#define omx_avcenc_component_lib m
#define omx_aacenc_component_lib 0
#define omx_baseclass_lib m


//
// Menu for configuring audio codecs
//
#define pv_aac_dec_lib m
#define pv_aac_enc_lib 0
#define getactualaacconfig_lib m
#define getaacaudioinfo_lib 0
#define pv_amr_nb_common_lib m
#define pvdecoder_gsmamr_lib m
#define pvencoder_gsmamr_lib m
#define pvamrwbdecoder_lib m
#define gsm_amr_headers_lib m
#define pvmp3_lib m
#define pvra8decoder_lib 0
#define pv_srs_wowhd_lib 0
#define wmadecoder_lib 0
#define useoldwmadecoder 0
#define usepv_one_segment_broadcast 0
#define usemultichannlefriendly 0
#define wma_audio_support m

//
// WMA Audio library build configurations (see build_configuration.doc)
//
#define wma_build_cfg_std 0
#define wma_build_cfg_stdprostereolbrv1 0
#define wma_build_cfg_stdprostereolbr 0
#define wma_build_cfg_stdprolbr 0
#define wma_build_cfg_lsl 0
#define wma_build_cfg_all 1

#define wmavoicedecoder_lib 0
#define wma_voice_support m
#define wma_common_hdrs_lib 0
#define pvg726decoder_lib 0


//
// Menu for configuring video codecs
//
#define pv_avc_common_lib m
#define pvavcdecoder_lib m
#define pv_avc_mp_decoder_lib 0
#define wmvdecoder_lib 0
#define pvmp4decoder_lib m
#define M4VDEC_FLV_SUPPORT 0
#define rvdecoder_lib 0
#define pvm4vencoder_lib m
#define pvavch264enc_lib m


//
// Menu for configuring codecs utilities
//
#define m4v_config_lib m
#define pv_config_parser_lib m
#define colorconvert_lib m

//
// Choose the YUYV format
//
#define UY0VY1 1
#define Y1VY0U 0
#define Y0VY1U 0


//
// choose the RGB format
//
#define CC_RGB 1
#define CC_BGR 0


#define ENABLE_UNALIGNED_MEM_ACCESS_FLAG 0


//
// Menu for configuring Nodes
//

//
// Menu for configuring Streaming Plugins
//
#define mshttp_support 0
#define rtspunicast_support m
#define rtsptunicast_support m
#define rtsptunicastwithreal_support 0
#define broadcastpvr_support 0
#define rtspunicastpvr_support 0
#define fileplaybackpvr_support 0


//
// Menu for configuring Download
//
#define pvdownloadmanagernode_lib m
#define pvdtcp_mbds_lib 0

//
// Menu for configuring downloadmanager features
//
#define PVMF_DOWNLOADMANAGER_SUPPORT_PPB 1
#define PVMF_MEMORYBUFFERDATASTREAM_DTCP_PPB 0
#define PVMF_DOWNLOADMANAGER_MIN_TCP_BUFFERS_FOR_PPB 39
#define PVMF_DOWNLOADMANAGER_CACHE_SIZE_FOR_SC_IN_SECONDS 6
#define PVMF_DOWNLOADMANAGER_MAX_BITRATE_FOR_SC 128



//
// Menu for configuring ProtocolEngine
//
#define penode_enabled m
#define penode_pdl_support 1
#define penode_ps_support 1
#define penode_ftdl_support 0
#define penode_wmhttpstreaming_support 0
#define penode_shoutcast_support 1
#define penode_rtmp_support 0
#define penode_smooth_streaming_support 0
#define penode_apple_http_streaming_support 0

#define pvfileoutputnode_lib m
#define pvmediaoutputnode_lib m
#define pvsocketnode_lib m
#define pvwavffparsernode_lib m
#define pvomxencnode_lib m
#define pvomxaudiodecnode_lib m
#define pvomxbasedecnode_lib m
#define pvomxvideodecnode_lib m
#define pvaacffparsernode_lib m
#define pvamrffparsernode_lib m
#define pvasfffparsernode_lib 0
#define pvmp3ffparsernode_lib m
#define pvmp4ffparsernode_lib 0
#define pvmp4ffparsernodeopencore_lib m
#define pvrmffparsernode_lib 0
#define pvrtppacketsourcenode_lib 0
#define nodes_common_headers_lib m
#define pvmediainputnode_lib m
#define pvmp4ffcomposernode_lib 0
#define pvmp4ffcomposernodeopencore_lib m
#define pvpvr_lib 0
#define pvpvrnode_lib 0
#define pvcommsionode_lib m
#define pvclientserversocketnode_lib m
#define pvloopbacknode_lib m
#define pvdivxffparsernode_lib 0
#define pvstillimagenode_lib 0
#define g726decnode_lib 0
#define pvflvffparsernode_lib 0
#define pvmpeg2ffparsernode_lib 0
#define pvcommonparsernode_lib m


//
// Menu for configuring Oscl
//
#define build_oscl m
#define unit_test_lib 1
#define unit_test_utils_lib 1


//
// Menu for configuring Protocols
//

//
// Menu for configuring Value Adds for 2way
//
#define twoway_value_add_config 1
#define PV_2WAY_VALUE_ADD_NONE 1

#define pv_http_parcom_lib m
#define pv_http_retriever_lib 0
#define pvlatmpayloadparser_lib m
#define rdt_parser_lib 0
#define pv_rtsp_parcom_lib m
#define rtppayloadparser_lib m

//
// Menu for rtppayload parser plugins
//
#define rfc_2429 1
#define rfc_3016 1
#define rfc_3267 1
#define rfc_3640 1
#define rfc_3984 1

#define asf_payload_lib 0
#define realmedia_payload_lib 0
#define rtprtcp_lib m
#define pv324m_lib m
#define pv_rtmp_parcom_lib 0
#define pv_smooth_streaming_lib 0
#define pv324m_common_headers_lib m
#define pvgeneraltools_lib m
#define pv_m3u_parser_lib 0


//
// Menu for configuring Pvmi
//

//
// Menu for configuring Recognizers
//
#define pvmfrecognizer_lib m
#define pvaacffrecognizer_lib m
#define pvamrffrecognizer_lib m
#define pvoma1ffrecognizer_lib 0
#define pvasfffrecognizer_lib 0
#define pvmp3ffrecognizer_lib m
#define pvmp4ffrecognizer_lib m
#define pvmpeg2ffrecognizer_lib 0
#define pvwavffrecognizer_lib m
#define pvrmffrecognizer_lib 0
#define pvdivxffrecognizer_lib 0
#define pvplsffrecognizer_lib m
#define pvflvffrecognizer_lib 0


//
// Menu for configuring Content Policy Manager
//
#define cpm_lib m
#define oma1_passthru_plugin_lib m
#define cpm_headers_lib m
#define pvoma1lockstream_lib 0
#define pvplayreadyplugin_lib 0
#define pvdivxdrmplugin_lib 0
#define pvdtcpplugin_lib 0


//
// Menu for configuring Media IO
//
#define pvmiofileinput_lib m
#define pvmiofileoutput_lib m
#define pvmioaviwavfileinput_lib 1
#define pvmio_comm_loopback_lib m
#define pvaudiotrackmio_lib 0


//
// Menu for configuring PacketSources
//
#define packetsources_default_lib 0

//
// Menu for configuring PacketSource Plugins
//
#define optimized_bcast_ps_support 0
#define standard_bcast_ps_support 0


#define pvmf_lib m
#define realaudio_deinterleaver_lib 0
#define pvdbmanager_lib 0
#define pvdb_recovery_utility_lib 0


//
// Menu for configuring Engines
//

//
// Menu for configuring Player
//
#define pvplayer_engine_lib m

//
// Menu for player engine tunables
//
#define PVPLAYERENGINE_CONFIG_SYNCMARGIN_EARLY_DEF -10
#define PVPLAYERENGINE_CONFIG_SYNCMARGIN_LATE_DEF 50
#define VIDEO_DEC_NODE_LOW_PRIORITY 1
#define PVPLAYERENGINE_SUPPORT_DTCP 1


//
// Menu for configuring player registry
//
#define BUILD_OMX_VIDEO_DEC_NODE 1
#define BUILD_OMX_AUDIO_DEC_NODE 1
#define BUILD_G726_DEC_NODE 0
#define BUILD_MP4_FF_PARSER_NODE 0
#define BUILD_MPEG2_FF_PARSER_NODE 0
#define BUILD_AMR_FF_PARSER_NODE 0
#define BUILD_AAC_FF_PARSER_NODE 1
#define BUILD_MP3_FF_PARSER_NODE 1
#define BUILD_WAV_FF_PARSER_NODE 0
#define BUILD_ASF_FF_PARSER_NODE 0
#define BUILD_RM_FF_PARSER_NODE 0
#define BUILD_STREAMING_MANAGER_NODE 0
#define BUILD_DOWNLOAD_MANAGER_NODE 0
#define BUILD_STILL_IMAGE_NODE 0
#define BUILD_MP4_FF_REC 0
#define BUILD_MPEG2_FF_REC 0
#define BUILD_ASF_FF_REC 0
#define BUILD_OMA1_FF_REC 0
#define BUILD_AAC_FF_REC 1
#define BUILD_RM_FF_REC 0
#define BUILD_MP3_FF_REC 1
#define BUILD_WAV_FF_REC 1
#define BUILD_AMR_FF_REC 1
#define BUILD_DIVX_FF_PARSER_NODE 0
#define BUILD_DIVX_FF_REC 0
#define BUILD_PLS_FF_REC 1
#define BUILD_FLV_FF_PARSER_NODE 0
#define BUILD_FLV_FF_REC 0
#define BUILD_COMMON_PARSER_NODE 1



//
// Menu for configuring Author
//
#define pvauthorengine_lib m


//
// Menu for configuring pv2way
//
#define pv2wayengine_lib m
#define pv2waysample_lib m

#define engines_common_headers_lib m
#define pvframemetadatautility_lib m
#define pvmetadata_engine_lib m
#define pvplayreadyutility_lib 0
#define pvmp4eu_lib 0


//
// Menu for configuring Extern_libs
//
#define pvmtp_engine_lib 0
#define pvmtpip_engine_lib 0
#define pviptransport_lib 0
#define pvsqlite_lib 0

//
// Menu for configuring PlayReady wmdrm
//
#define pvwmdrmmd_lib 0

#define pvtinyxml_lib 0
#define pvdivxdrm_lib 0
#define pvdivxdrm_oem_settings_lib 0


//
// That's all, folks!
//
// Derived symbols
//
#define pvfasttrack_download_link_type "loaded"
#define MODS_pvrtspunicast_streaming "-lopencore_net_support -lopencore_player -lopencore_common -lopencore_rtsp -lopencore_streaming"
#define pvtinyxml_m_lib ""
#define protocolenginenode_shoutcast_lib "-lprotocolenginenode_shoutcast"
#define pvstillimagenode_y_mk ""
#define pvmedialayernode_m_mk ""
#define pvpvr_y_mk ""
#define LIBDIR_engines_shared "/engines/player/build/make /engines/author/build/make /engines/2way/build/make /engines/2way/sample_app/pv2waysample/build/make /engines/common/build/make /engines/adapters/player/framemetadatautility/build/make /engines/pvme/build/make  "
#define LIBDIR_oscl_static " /oscl/unit_test/build/make /oscl/unit_test_utils/build/make"
#define pvsqlite_aggregate_libtype "static"
#define opencore_author_aggregate_libtype "shared"
#define pvrmffparser_m_lib ""
#define pvm4vencoder_m_mk "/codecs_v2/video/m4v_h263/enc/build/make"
#define pvrtsptunicastforrm_streamingreg_aggregate_libtype "static"
#define pvframemetadatautility_m_mk "/engines/adapters/player/framemetadatautility/build/make"
#define pvmf_m_mk "/pvmi/pvmf/build/make"
#define pvrtsp_cli_eng_real_cloaking_node_y_mk ""
#define opencore_downloadreg_so_name "opencore_downloadreg"
#define pvasflocalpb_link_type "loaded"
#define LIBS_codecs_v2_static "                                             "
#define pvmp3ffrecognizer_m_lib "-lpvmp3ffrecognizer"
#define pvmediainputnode_m_lib "-lpvmediainputnode"
#define pvmp4ff_m_mk ""
#define pvmshttpfsp_m_mk ""
#define pvrtsptunicast_streaming_so_name "pvrtsptunicast_streaming"
#define pvavifileparser_y_mk "/fileformats/avi/parser/build/make"
#define pvprotocolenginenode_wmhttpstreaming_plugin_m_lib ""
#define pvasflocalpbreg_so_name ""
#define pvasflocalpb_aggregate_libtype "static"
#define pv_avc_common_lib_y_mk ""
#define pvavcdecoder_m_mk "/codecs_v2/video/avc_h264/dec/build/make"
#define LIBDIR_extern_libs_shared "       "
#define opencore_streamingreg_so_name "opencore_streamingreg"
#define wmadecoder_m_lib ""
#define pv_amr_nb_common_lib_y_lib ""
#define AGGREGATE_LIBDIRS_pvrmff_recognizer "  "
#define pvmpeg2interface_m_lib ""
#define cpm_m_mk "/pvmi/content_policy_manager/build/make"
#define pvpvrcommonimp_y_mk ""
#define pvcommonparsernode_m_mk "/nodes/pvcommonparsernode/build/make"
#define pviptransport_aggregate_libtype "static"
#define pvmtp_engine_m_mk ""
#define realaudio_deinterleaver_y_lib ""
#define MODS_pvfasttrack_downloadreg "-lopencore_common -lopencore_net_support"
#define omx_amr_component_imp_m_lib ""
#define pvframemetadatautility_y_mk ""
#define WMA_BUILD_CFG_ALL_ENABLED 1
#define sdp_common_m_mk "/protocols/sdp/common/build/make"
#define pvavcdecoder_m_lib "-lpvavcdecoder"
#define pvrtspbroadcastwithpvr_streaming_aggregate_libtype "static"
#define pviptransport_y_lib ""
#define pvdtcpplugin_m_mk ""
#define pvsdpparser_y_lib ""
#define pvrtspunicastfsp_m_mk "/nodes/streaming/streamingmanager/plugins/rtspunicast/build/make"
#define pvrfileplaybackpluginregpopulator_m_mk ""
#define pvasfcommon_aggregate_libtype "static"
#define pvmpeg2ffrecognizer_y_lib ""
#define pvrtsp_cli_eng_real_cloaking_node_m_lib ""
#define mpeg2recognizer_utility_y_mk ""
#define pvmp4ffcomposer_y_lib ""
#define MODS_pvdivxoemsettings "-lopencore_common"
#define pvdecoder_gsmamr_m_mk "/codecs_v2/audio/gsm_amr/amr_nb/dec/build/make"
#define pvrtppacketsourcenode_y_lib ""
#define gsm_amr_headers_m_mk "/codecs_v2/audio/gsm_amr/common/dec/build/make"
#define pvrtspunicastfsp_m_lib "-lpvrtspunicaststreamingmanager"
#define pvmetadata_engine_m_lib "-lpvmetadata_engine"
#define pvasfcommon_so_name ""
#define pvmp3ffrecognizer_y_mk ""
#define WMA_BUILD_CFG_STDPROLBR_ENABLED 0
#define pvwmdrmoemsettingsinterface_m_mk ""
#define LIBDIR_pvmi_shared "/pvmi/content_policy_manager/build/make /pvmi/content_policy_manager/plugins/oma1/passthru/build/make /pvmi/content_policy_manager/plugins/common/build/make     /pvmi/media_io/pvmiofileoutput/build/make /pvmi/media_io/pvmi_mio_fileinput/build/make_pvauthor  /pvmi/media_io/pvmio_comm_loopback/build/make /pvmi/recognizer/build/make /pvmi/recognizer/plugins/pvaacffrecognizer/build/make /pvmi/recognizer/plugins/pvamrffrecognizer/build/make   /pvmi/recognizer/plugins/pvmp3ffrecognizer/build/make /pvmi/recognizer/plugins/pvmp4ffrecognizer/build/make  /pvmi/recognizer/plugins/pvwavffrecognizer/build/make   /pvmi/recognizer/plugins/pvplsffrecognizer/build/make   /pvmi/pvmf/build/make   "
#define csprng_y_mk ""
#define pvdivxffparsernode_y_lib ""
#define pv_rtmp_parcom_y_lib ""
#define AGGREGATE_LIBDIRS_pvrtsptunicast_streamingreg "/modules/linux_rtsp/smplugins/tunneling/registry/build/make"
#define pvprotocolenginenode_ftdl_plugin_m_lib ""
#define rdt_parser_y_lib ""
#define MODS_pvrtspbroadcastwithpvr_streaming "-lopencore_net_support -lopencore_player -lopencore_common -lpvpvrcommonimpl_streaming -lopencore_rtsp -lopencore_streaming"
#define pvmp4ff_y_lib ""
#define pvamrffparsernode_y_mk ""
#define pvmshttpfsp_y_mk ""
#define amrparser_y_mk ""
#define LIBS_omxenc_static "   "
#define pvstreamingmanagernode_y_mk ""
#define smmshttpplugininterface_m_lib ""
#define MODS_pvdb "-lopencore_player -lopencore_common -lpvsqlite -lpvasfcommon -lpvasflocalpbreg -lopencore_pvme"
#define DYNAMIC_LOAD_OMX_WMV_COMPONENT 0
#define pvrtsptunicast_streaming_aggregate_libtype "shared"
#define pvmtp_usb_transport_m_lib ""
#define MODS_pvdivxdrm "-lopencore_common"
#define pv_aac_enc_y_mk ""
#define opencore_mp4local_link_type "loaded"
#define pvjitterbufferasf_y_mk ""
#define pvrrtspunicastplugininterface_m_lib ""
#define AGGREGATE_LIBDIRS_pvasflocalpb " "
#define pvomxbasedecnode_y_mk ""
#define nodes_common_headers_y_mk ""
#define omx_wmvdec_sharedlibrary_link_type "loaded"
#define pvbroadcastwithpvrfsp_y_lib ""
#define pvflvparser_node_so_name ""
#define pvaudiotrackmio_m_mk ""
#define MODS_omx_mp3dec_sharedlibrary "-lomx_sharedlibrary -lopencore_common"
#define pvplayer_engine_y_lib ""
#define pvcommonparsernode_m_lib "-lpvcommonparsernode"
#define pvrtsp_cli_eng_node_m_mk "/protocols/rtsp_client_engine/build/make_segments"
#define standard_bcast_ps_mk ""
#define pv2waysample_m_mk "/engines/2way/sample_app/pv2waysample/build/make"
#define pvid3parcom_y_lib ""
#define twoway_config "2way_basic"
#define pv324m_y_mk ""
#define pvmp4ffrecognizer_y_mk ""
#define pvsmreginterface_m_mk "/modules/linux_rtsp/node_registry/build/make"
#define LIBDIR_omxencimp_shared ""
#define pvflvparser_node_aggregate_libtype "static"
#define smrtsptpluginregpopulator_m_lib "-lpvrtsptsmpluginreginterface"
#define pvmshttp_streamingreg_aggregate_libtype "static"
#define pvdownloadinterface_m_mk "/modules/linux_download/core/build/make"
#define pvoma1passthruplugin_y_lib ""
#define pvthreadmessaging_y_mk ""
#define AGGREGATE_LIBDIRS_pvrtspbroadcastwithpvr_streamingreg ""
#define pvmfrecognizer_m_mk "/pvmi/recognizer/build/make"
#define AGGREGATE_LIBDIRS_pvdb ""
#define LIBS_omxdecimp_shared ""
#define pvmtpconfigclass_aggregate_libtype "static"
#define omx_aacenc_component_m_lib ""
#define pvjitterbufferasf_y_lib ""
#define pvrtspunicastwithpvr_streaming_aggregate_libtype "static"
#define pvjitterbuffercommon_y_lib ""
#define AGGREGATE_LIBDIRS_opencore_download "/nodes/pvdownloadmanagernode/build/make /modules/linux_download/core/build/make"
#define pvmedialayernode_m_lib ""
#define pvclientserversocketnode_y_mk ""
#define pvdownloadmanagernode_y_lib ""
#define opencore_common_link_type "linked"
#define pvmshttpfsp_y_lib ""
#define omx_amr_component_imp_m_mk ""
#define pvgeneraltools_y_lib ""
#define pv_avc_common_imp_lib_m_lib ""
#define pvdivxffrecognizer_y_mk ""
#define pvdbmanager_m_mk ""
#define penode_any_selected 1
#define wavparser_y_mk ""
#define USE_LOADABLE_MODULES 1
#define pviptransport_m_lib ""
#define pvrmffparser_m_mk ""
#define protocolenginenode_asfstreaming_mk ""
#define pvdb_aggregate_libtype "static"
#define pvrmff_y_mk ""
#define pvmp4ffcomposernode_y_mk ""
#define pvgendatastruct_m_mk "/baselibs/gen_data_structures/build/make"
#define pv_aac_dec_m_lib "-lpv_aac_dec"
#define pvsocketnode_y_mk ""
#define DYNAMIC_LOAD_OMX_RV_COMPONENT 0
#define MODS_pvasflocalpb "-lopencore_player -lopencore_common -lpvasfcommon"
#define pv_config_parser_m_mk "/codecs_v2/utilities/pv_config_parser/build/make"
#define pv_amr_nb_common_imp_lib_m_lib ""
#define pvwmdrmoemsettings_so_name ""
#define pvpvrcommonimpl_streaming_aggregate_libtype "static"
#define AGGREGATE_LIBDIRS_omx_m4vdec_sharedlibrary "/codecs_v2/omx/omx_m4v/build/make_multithreaded /codecs_v2/video/m4v_h263/dec/build/make"
#define pvmimeutils_m_lib "-lpvmimeutils"
#define pv_rtmp_parcom_m_mk ""
#define AGGREGATE_LIBDIRS_opencore_downloadreg "/modules/linux_download/node_registry/build/make"
#define download_common_enabled 1
#define AGGREGATE_LIBDIRS_opencore_mp4localreg "/modules/linux_mp4/node_registry/build/make /pvmi/recognizer/plugins/pvmp4ffrecognizer/build/make"
#define pvthreadmessaging_m_lib "-lpvthreadmessaging"
#define pvrtspunicastwithpvrfsp_y_mk ""
#define pvmiofileinput_m_lib "-lpvmiofileinput"
#define mpeg2recognizer_utility_y_lib ""
#define omx_avcenc_sharedlibrary_so_name "omx_avcenc_sharedlibrary"
#define pvwmdrmmd_m_mk ""
#define rtppayloadparser_plugins_opencore_rtsp "rfc_2429.mk rfc_3016.mk rfc_3267.mk rfc_3640.mk rfc_3984.mk"
#define omx_common_y_lib ""
#define pvpvrff_m_mk ""
#define pvpvrnode_m_mk ""
#define gsm_amr_headers_y_mk ""
#define AGGREGATE_LIBDIRS_pvmp4eu " "
#define pvmp3_imp_m_lib ""
#define LIBDIR_cpm_shared "/pvmi/content_policy_manager/build/make /pvmi/content_policy_manager/plugins/oma1/passthru/build/make /pvmi/content_policy_manager/plugins/common/build/make    "
#define threadsafe_callback_ao_y_mk ""
#define MODS_opencore_pvme "-lopencore_player -lopencore_common"
#define WMA_BUILD_CFG_STDPROSTEREOLBR_ENABLED 0
#define csprng_y_lib ""
#define LIBS_oscl_shared "-loscllib  -lpvlogger -losclregcli -losclregserv -losclutil -losclproc  -losclio -losclmemory -losclerror -losclbase "
#define pvframemetadatautility_m_lib "-lpvframemetadatautility"
#define omx_mastercore_y_lib ""
#define pvmfrecognizer_y_lib ""
#define rtppayloadparser_m_mk "/protocols/rtp_payload_parser/build/make"
#define flvrecognizer_utility_y_lib ""
#define pvjitterbuffercommon_m_mk "/nodes/streaming/jitterbuffernode/jitterbuffer/common/build/make"
#define pvsdpparser_m_lib ""
#define pvflvreginterface_m_mk ""
#define rtprtcp_m_mk "/protocols/rtp/build/make"
#define pvstillimagenode_m_lib ""
#define BUILD_FASTTRACK_DOWNLOAD_PLUGIN 0
#define pvg726decoder_y_lib ""
#define MODS_omx_amrdec_sharedlibrary "-lomx_sharedlibrary -lopencore_common"
#define csprng_m_mk ""
#define LIBS_video_static "       "
#define opencore_common_aggregate_libtype "shared"
#define omx_avc_component_y_mk ""
#define pvdbmanager_y_lib ""
#define pvasxparser_m_lib ""
#define threadsafe_callback_ao_m_mk "/baselibs/threadsafe_callback_ao/build/make"
#define BUILD_STATIC_RTSPT 0
#define pv_srs_wowhd_m_mk ""
#define pvdivxdrm_m_lib ""
#define pvamrffparsernode_m_lib "-lpvamrffparsernode"
#define pvflvinterface_m_lib ""
#define pvprotocolengine_asfstreamingreg_aggregate_libtype "static"
#define pvmp4ffcomposer_y_mk ""
#define LIBS_nodes_shared "-lpvfileoutputnode -lpvmediaoutputnode -lpvsocketnode -lprotocolenginenode_base -lprotocolenginenode_common -lprotocolenginenode_download_common -lprotocolenginenode_pdl -lprotocolenginenode_ps -lprotocolenginenode_shoutcast -lpvwavffparsernode -lpvomxencnode -lpvomxbasedecnode -lpvomxaudiodecnode -lpvomxvideodecnode -lpvaacffparsernode -lpvamrffparsernode  -lpvmp3ffparsernode  -lpvmp4ffparsernode   -lpvmediainputnode  -lpvmp4ffcomposernode   -lpvdownloadmanagernode  -lpvrtspunicaststreamingmanager -lpvrtsptunicaststreamingmanager     -lpvsmfspcommon  -lpvstreamingmanagernode   -lpvrtspsmplugininterface -lpvrtspsmpluginreginterface -lpvrtsptsmplugininterface -lpvrtsptsmpluginreginterface          -lpvjitterbuffer -lpvjitterbufferrtp  -lpvjitterbuffernode -lpvcommsionode -lpvclientserversocketnode -lpvloopbacknode      -lpvcommonparsernode"
#define pvloopbacknode_m_mk "/nodes/pvloopbacknode/build/make"
#define pvjitterbuffernode_m_mk "/nodes/streaming/jitterbuffernode/build/make"
#define pvmio_comm_loopback_y_lib ""
#define AGGREGATE_LIBDIRS_omx_amrenc_sharedlibrary "/codecs_v2/omx/omx_amrenc/build/make_multithreaded /codecs_v2/audio/gsm_amr/amr_nb/enc/build/make"
#define omx_aac_component_y_mk ""
#define omx_ra_component_y_mk ""
#define pvavcdecoder_y_lib ""
#define pvdb_recovery_utility_y_mk ""
#define pv_rtsp_parcom_m_lib "-lpv_rtsp_parcom"
#define pvrtsptunicastfsp_m_mk "/nodes/streaming/streamingmanager/plugins/rtsptunicast/build/make"
#define pventropysrc_m_mk ""
#define pvra8decoder_imp_m_lib ""
#define smrtspunicastpluginregpopulator_m_mk "/modules/linux_rtsp/smplugins/unicast/registry/build/make"
#define AGGREGATE_LIBDIRS_pvasflocalpbreg " "
#define pvdecoder_gsmamr_y_lib ""
#define omx_amrdec_sharedlibrary_so_name "omx_amrdec_sharedlibrary"
#define pvoma1lockstream_m_mk ""
#define pvmpeg2interface_m_mk ""
#define pv_amr_nb_common_lib_y_mk ""
#define cpm_headers_m_mk "/pvmi/content_policy_manager/plugins/common/build/make"
#define pvmp4ffrecognizer_m_mk "/pvmi/recognizer/plugins/pvmp4ffrecognizer/build/make"
#define pvrtsp_cli_eng_node_y_mk ""
#define pvmioaviwavfileinput_y_mk "/pvmi/media_io/pvmi_mio_avi_wav_fileinput/build/make"
#define pvmp3_y_mk ""
#define pvasflocalpb_so_name ""
#define pvmp4decoder_y_lib ""
#define pv324m_m_mk "/protocols/systems/3g-324m_pvterminal/build/make/"
#define omx_mp3_component_y_lib ""
#define oscl_y_mk ""
#define pv_http_parcom_y_mk ""
#define LIBS_shared "-loscllib  -lpvlogger -losclregcli -losclregserv -losclutil -losclproc  -losclio -losclmemory -losclerror -losclbase     -lpvgendatastruct -lpvmediadatastruct -lpvmimeutils -lthreadsafe_callback_ao -lpvthreadmessaging  -lomx_avc_component_lib -lomx_m4v_component_lib   -lomx_aac_component_lib -lomx_amr_component_lib -lomx_mp3_component_lib   -lomx_amrenc_component_lib -lomx_m4venc_component_lib -lomx_avcenc_component_lib  -lomx_common_lib -lomx_queue_lib -lpvomx_proxy_lib -lomx_baseclass_lib -lomx_mastercore_lib -lpv_omx_interface     -lpv_aac_dec  -lpv_amr_nb_common_lib -lpvamrwbdecoder -lpvdecoder_gsmamr -lpvmp3   -lpvencoder_gsmamr  -lpv_avc_common_lib -lpvavcdecoder   -lpvmp4decoder  -lpvm4vencoder -lpvavch264enc -lm4v_config -lpv_config_parser -lcolorconvert -lpvfileparserutils -lpvid3parcom -lpvpvxparser -lpvwav    -lpvmp3ff -lpvaacparser -lpvgsmamrparser   -lmp4recognizer_utility -lpvmp4ff  -lpvmp4ffcomposer    -lscsp       -laudioparser -lamrparser -lwavparser -lpv_http_parcom  -lpvlatmpayloadparser  -lpvsdpparser  -lpv_rtsp_parcom -lpvrtsp_cli_eng_node     -lrtppayloadparser -lrtprtcp -lpv324m   -lpvgeneraltools  -lcpm -lpvoma1passthruplugin     -lpvmiofileoutput -lpvmiofileinput  -lpvmio_comm_loopback -lpvmfrecognizer -lpvaacffrecognizer -lpvamrffrecognizer   -lpvmp3ffrecognizer -lpvmp4ffrecognizer  -lpvwavffrecognizer   -lpvplsffrecognizer   -lpvmf            -lpvfileoutputnode -lpvmediaoutputnode -lpvsocketnode -lprotocolenginenode_base -lprotocolenginenode_common -lprotocolenginenode_download_common -lprotocolenginenode_pdl -lprotocolenginenode_ps -lprotocolenginenode_shoutcast -lpvwavffparsernode -lpvomxencnode -lpvomxbasedecnode -lpvomxaudiodecnode -lpvomxvideodecnode -lpvaacffparsernode -lpvamrffparsernode  -lpvmp3ffparsernode  -lpvmp4ffparsernode   -lpvmediainputnode  -lpvmp4ffcomposernode   -lpvdownloadmanagernode  -lpvrtspunicaststreamingmanager -lpvrtsptunicaststreamingmanager     -lpvsmfspcommon  -lpvstreamingmanagernode   -lpvrtspsmplugininterface -lpvrtspsmpluginreginterface -lpvrtsptsmplugininterface -lpvrtsptsmpluginreginterface          -lpvjitterbuffer -lpvjitterbufferrtp  -lpvjitterbuffernode -lpvcommsionode -lpvclientserversocketnode -lpvloopbacknode      -lpvcommonparsernode -lpvplayer_engine -lpvauthorengine -lpv2wayengine -lpv2waysample -lpvframemetadatautility -lpvmetadata_engine   -lpvsminterface -lpvsmreginterface   -lpvrtspsmplugininterface -lpvrtspsmpluginreginterface -lpvrtsptsmplugininterface -lpvrtsptsmpluginreginterface         -lpvdownloadinterface -lpvdownloadreginterface -lpvmp4interface -lpvmp4reginterface         -lpvoma1passthruplugininterface           "
#define pvmp4eu_aggregate_libtype "static"
#define rtppayloadparser_plugins "rfc_2429.mk rfc_3016.mk rfc_3267.mk rfc_3640.mk rfc_3984.mk"
#define omx_aacenc_component_y_mk ""
#define pvsdpparser_y_mk ""
#define pvfileoutputnode_y_lib ""
#define AGGREGATE_LIBDIRS_pvfileplaybackwithpvr_streamingreg ""
#define pvamrwbdecoder_imp_m_mk ""
#define pvmf_y_mk ""
#define pvwavffrecognizer_y_mk ""
#define pvtinyxml_m_mk ""
#define LIBS_protocols_shared "-lpv_http_parcom  -lpvlatmpayloadparser  -lpvsdpparser  -lpv_rtsp_parcom -lpvrtsp_cli_eng_node     -lrtppayloadparser -lrtprtcp -lpv324m   -lpvgeneraltools "
#define DYNAMIC_LOAD_OMX_WMA_COMPONENT 0
#define realaudio_deinterleaver_y_mk ""
#define pvjitterbufferrtp_y_mk ""
#define pvomxencnode_m_mk "/nodes/pvomxencnode/build/make"
#define pv_rtmp_parcom_m_lib ""
#define pvfileparserutils_m_mk "/fileformats/common/parser/build/make"
#define pvoma1passthru_aggregate_libtype "shared"
#define pvrtspunicast_streamingreg_aggregate_libtype "shared"
#define secure_data_format_m_lib ""
#define pvcommsionode_y_mk ""
#define pvmp4ffcomposeropencore_m_lib "-lpvmp4ffcomposer"
#define nodes_common_headers_m_mk "/nodes/common/build/make"
#define omx_avc_component_imp_m_lib ""
#define wmavoicedecoder_imp_m_mk ""
#define pvoma1lockstream_y_lib ""
#define LIBDIR_protocols_shared "/protocols/http_parcom/build/make  /protocols/rtp_payload_parser/util/build/latmparser/make /protocols/sdp/parser/build/make /protocols/sdp/common/build/make  /protocols/rtsp_parcom/build/make /protocols/rtsp_client_engine/build/make_segments     /protocols/rtp_payload_parser/build/make /protocols/rtp/build/make /protocols/systems/3g-324m_pvterminal/build/make/   /protocols/systems/common/build/make/ /protocols/systems/tools/general/build/make "
#define pvdivxdrmplugin_y_mk ""
#define pvmfrecognizer_m_lib "-lpvmfrecognizer"
#define pvencoder_gsmamr_y_mk ""
#define pvoma1ffrecognizer_y_lib ""
#define wmadecoder_m_mk ""
#define AGGREGATE_LIBDIRS_pvmpeg2localreg "  "
#define omx_rv_component_m_lib ""
#define wmvdecoder_y_lib ""
#define pvpvr_m_mk ""
#define pvrtsptwithrealfsp_y_lib ""
#define pvomx_proxy_m_lib "-lpvomx_proxy_lib"
#define omx_wma_component_m_mk ""
#define pvrtsptwithrealfsp_m_mk ""
#define wmavoicedecoder_m_lib ""
#define pvdivxdrm_oem_settings_m_mk ""
#define pv_avc_mp_decoder_imp_m_mk ""
#define pvmp3_imp_m_mk ""
#define secure_data_format_m_mk ""
#define rfc_3984_mk "rfc_3984.mk"
#define pvpvr_y_lib ""
#define pv2wayengine_y_lib ""
#define omx_aacenc_component_imp_m_lib ""
#define pv_aac_enc_m_lib ""
#define pvdivxdrm_y_mk ""
#define REGISTER_OMX_AAC_COMPONENT 1
#define pvwavffparsernode_m_lib "-lpvwavffparsernode"
#define AGGREGATE_LIBDIRS_pvdivxoemsettings ""
#define rtppayloadparser_m_lib "-lrtppayloadparser"
#define DYNAMIC_LOAD_OMX_M4V_COMPONENT 1
#define MODS_omx_avcenc_sharedlibrary "-lomx_sharedlibrary -lopencore_common "
#define pvaacparser_m_mk "/fileformats/rawaac/parser/build/make"
#define pvgsmamrparser_y_mk ""
#define opencore_download_link_type "loaded"
#define pvfileplaybackwithpvrfsp_y_lib ""
#define pvdivxdrm_oem_settings_m_lib ""
#define pvavcdecoder_imp_m_lib ""
#define pvmediadatastruct_y_lib ""
#define pvmshttp_streaming_link_type "loaded"
#define pvmpeg2ff_m_lib ""
#define LIBDIR_codecs_v2_static "                                           "
#define pvstillimagenode_m_mk ""
#define MODS_omx_m4vdec_sharedlibrary "-lomx_sharedlibrary -lopencore_common "
#define AGGREGATE_LIBDIRS_omx_m4venc_sharedlibrary "/codecs_v2/omx/omx_m4venc/build/make_multithreaded /codecs_v2/video/m4v_h263/enc/build/make"
#define pvmp4ff_m_lib ""
#define rvdecoder_y_lib ""
#define pvbroadcastwithpvrfsp_y_mk ""
#define getaacaudioinfo_y_mk ""
#define pvauthorengine_y_mk ""
#define pvasflocalpbreg_link_type "loaded"
#define omx_avc_component_y_lib ""
#define omx_m4vdec_sharedlibrary_link_type "loaded"
#define pvplayreadyplugin_y_mk ""
#define pvmiofileoutput_m_lib "-lpvmiofileoutput"
#define pvmediadatastruct_m_lib "-lpvmediadatastruct"
#define MODS_pvwmdrmoemsettings "-lopencore_common"
#define opencore_downloadreg_link_type "loaded"
#define flvrecognizer_utility_m_mk ""
#define AGGREGATE_LIBDIRS_pvrtspbroadcastwithpvr_streaming " "
#define MODS_pvmpeg2localreg "-lopencore_player -lopencore_common"
#define pvprotocolenginewmhttpstreaminginterface_m_lib ""
#define unit_test_utils_m_mk ""
#define omx_rvdec_sharedlibrary_aggregate_libtype "static"
#define pvrtppacketsourcenode_y_mk ""
#define wmavoicedecoder_y_lib ""
#define pvbroadcastwithpvrfsp_m_lib ""
#define opencore_download_so_name "opencore_download"
#define omx_avc_component_m_lib "-lomx_avc_component_lib"
#define pvaacffparsernode_y_mk ""
#define pvmp3ffparsernode_m_lib "-lpvmp3ffparsernode"
#define USING_OMX 1
#define wmvdecoder_m_lib ""
#define pvdtcp_mbds_so_m_mk ""
#define BUILD_APPLE_HTTP_STREAMING_PLUGIN 0
#define mp4recognizer_utility_y_mk ""
#define REGISTER_OMX_H263_COMPONENT 1
#define pvmp4reginterface_m_lib "-lpvmp4reginterface"
#define pv324m_m_lib "-lpv324m"
#define pvpvrnode_y_lib ""
#define pvpvrff_y_lib ""
#define pvrtsptunicast_streamingreg_link_type "loaded"
#define pvmp4eu_y_lib ""
#define getactualaacconfig_imp_m_mk "/codecs_v2/audio/aac/dec/util/getactualaacconfig/build/make"
#define pv2wayengine_m_mk "/engines/2way/build/make"
#define rvdecoder_imp_m_lib ""
#define getactualaacconfig_for_static_m_mk ""
#define sdp_parser_mksegment_default ""
#define omx_wmv_component_y_mk ""
#define LIBS_video_shared "-lpv_avc_common_lib -lpvavcdecoder   -lpvmp4decoder  -lpvm4vencoder -lpvavch264enc"
#define pvmiofileinput_y_mk ""
#define pvplayreadyplugin_m_lib ""
#define omx_queue_y_mk ""
#define pvpvrcommonimp_m_mk ""
#define pvfileplaybackwithpvrfsp_m_mk ""
#define DYNAMIC_LOAD_OMX_AMRENC_COMPONENT 1
#define omx_wma_component_imp_m_mk ""
#define pvflvff_y_mk ""
#define opencore_mp4local_so_name "opencore_mp4local"
#define pvwmdrmmd_aggregate_libtype "static"
#define omx_amrdec_sharedlibrary_link_type "loaded"
#define AGGREGATE_LIBDIRS_pvrtspunicast_streaming "/nodes/streaming/streamingmanager/plugins/rtspunicast/build/make /modules/linux_rtsp/smplugins/unicast/core/build/make"
#define MODS_pvsqlite "-lopencore_common"
#define omx_wma_component_m_lib ""
#define pv_avc_mp_decoder_y_mk ""
#define MODS_pvmtp "-lopencore_common -lpvdb"
#define pvgendatastruct_m_lib "-lpvgendatastruct"
#define pvjitterbuffercommon_y_mk ""
#define BUILD_STATIC_RTSPT_REALMEDIA 0
#define audioparser_y_lib ""
#define LIBS_omxenc_shared "-lomx_amrenc_component_lib -lomx_m4venc_component_lib -lomx_avcenc_component_lib "
#define pvjitterbuffernode_y_mk ""
#define MODS_pvdivx_recognizer "-lopencore_common"
#define pvencoder_gsmamr_y_lib ""
#define smrtsptrmpluginregpopulator_m_mk ""
#define omx_amrenc_component_m_mk "/codecs_v2/omx/omx_amrenc/build/make_multithreaded"
#define pvprotocolenginewmhttpstreamingpluginreginterface_m_lib ""
#define sdp_parser_mksegment_opencore "sdp_opencore.mk"
#define scsp_m_lib "-lscsp"
#define BUILD_STATIC_RTSP_UNICAST_PVR 0
#define smmshttpplugininterface_m_mk ""
#define getaacaudioinfo_y_lib ""
#define pvauthorengine_y_lib ""
#define AGGREGATE_LIBDIRS_omx_rvdec_sharedlibrary " "
#define omx_amrenc_component_m_lib "-lomx_amrenc_component_lib"
#define pvfileparserutils_y_mk ""
#define AGGREGATE_LIBDIRS_opencore_streaming "/nodes/streaming/streamingmanager/build/make /nodes/streaming/streamingmanager/plugins/common/build/make /modules/linux_rtsp/core/build/make"
#define pv_aac_dec_y_mk ""
#define pvmimeutils_y_lib ""
#define pvrtsp_cli_eng_playlist_node_y_mk ""
#define AGGREGATE_LIBDIRS_pvdtcp_mbds " "
#define g726decnode_m_mk ""
#define pvdtcp_mbds_m_mk ""
#define mp4recognizer_utility_m_lib "-lmp4recognizer_utility"
#define MODS_opencore_download "-lopencore_net_support -lopencore_player -lopencore_common"
#define pvoma1passthru_link_type "loaded"
#define pvrtspunicast_streamingreg_so_name "pvrtspunicast_streamingreg"
#define pv_divxfile_parser_y_lib ""
#define omx_avcenc_component_m_lib "-lomx_avcenc_component_lib"
#define omx_m4v_component_y_lib ""
#define MODS_opencore_mp4localreg "-lopencore_player -lopencore_common"
#define AGGREGATE_LIBDIRS_pvrtsptunicastforrm_streaming "     "
#define pvomxbasedecnode_m_lib "-lpvomxbasedecnode"
#define pvmpeg2reginterface_m_lib ""
#define AGGREGATE_LIBDIRS_pvmtpip ""
#define m4v_config_m_mk "/codecs_v2/utilities/m4v_config_parser/build/make"
#define pvdivxreginterface_m_lib ""
#define pvrtspunicastwithpvrfsp_m_mk ""
#define asfrecognizer_utility_y_mk ""
#define LIBDIR_codecs_v2_shared "/codecs_v2/omx/omx_h264/build/make_multithreaded /codecs_v2/omx/omx_m4v/build/make_multithreaded   /codecs_v2/omx/omx_aac/build/make_multithreaded /codecs_v2/omx/omx_amr/build/make_multithreaded /codecs_v2/omx/omx_mp3/build/make_multithreaded   /codecs_v2/omx/omx_amrenc/build/make_multithreaded /codecs_v2/omx/omx_m4venc/build/make_multithreaded /codecs_v2/omx/omx_h264enc/build/make_multithreaded  /codecs_v2/omx/omx_common/build/make_multithreaded /codecs_v2/omx/omx_queue/build/make /codecs_v2/omx/omx_proxy/build/make /codecs_v2/omx/omx_baseclass/build/make /codecs_v2/omx/omx_mastercore/build/make_multithreaded /codecs_v2/omx/omx_sharedlibrary/interface/build/make      /codecs_v2/audio/aac/dec/build/make  /codecs_v2/audio/gsm_amr/amr_nb/common/build/make /codecs_v2/audio/gsm_amr/amr_wb/dec/build/make /codecs_v2/audio/gsm_amr/amr_nb/dec/build/make /codecs_v2/audio/mp3/dec/build/make   /codecs_v2/audio/gsm_amr/common/dec/build/make /codecs_v2/audio/gsm_amr/amr_nb/enc/build/make  /codecs_v2/video/avc_h264/common/build/make /codecs_v2/video/avc_h264/dec/build/make   /codecs_v2/video/m4v_h263/dec/build/make  /codecs_v2/video/m4v_h263/enc/build/make /codecs_v2/video/avc_h264/enc/build/make /codecs_v2/utilities/m4v_config_parser/build/make /codecs_v2/utilities/pv_config_parser/build/make /codecs_v2/utilities/colorconvert/build/make"
#define MODS_opencore_player "-lopencore_common -lopencore_net_support"
#define omx_amrenc_component_imp_m_mk ""
#define pvdecoder_gsmamr_m_lib "-lpvdecoder_gsmamr"
#define pvfileoutputnode_y_mk ""
#define wavparser_m_lib "-lwavparser"
#define pvmp4ffcomposeropencore_m_mk "/fileformats/mp4/composer/build_opencore/make"
#define pvrtsp_cli_eng_playlist_node_y_lib ""
#define MODS_pvprotocolengine_asfstreamingreg "-lopencore_common -lopencore_net_support"
#define pvtinyxml_y_lib ""
#define pvamrffrecognizer_y_mk ""
#define pventropysrc_m_lib ""
#define smrtspunicastplugininterface_m_lib "-lpvrtspsmplugininterface"
#define LIBDIR_baselibs_shared "   /baselibs/gen_data_structures/build/make /baselibs/media_data_structures/build/make /baselibs/pv_mime_utils/build/make /baselibs/threadsafe_callback_ao/build/make /baselibs/thread_messaging/build/make "
#define AGGREGATE_LIBDIRS_pvdbconfigclass ""
#define pvaacffrecognizer_y_lib ""
#define LIBS_omxencimp_shared ""
#define MODS_pvwmdrmmd "-lopencore_common"
#define pvdivxffrecognizer_m_lib ""
#define omx_avc_component_lib_plugins "omx_avc_dec_plugin.mk"
#define pvmp4ffopencore_m_lib "-lpvmp4ff"
#define pvprotocolenginefasttrackdownloadpluginreginterface_m_lib ""
#define sdp_common_y_mk ""
#define AGGREGATE_LIBDIRS_opencore_2way "/engines/2way/sample_app/pv2waysample/build/make /engines/2way/build/make /protocols/systems/3g-324m_pvterminal/build/make/ /nodes/pvclientserversocketnode/build/make /nodes/pvcommsionode/build/make /pvmi/media_io/pvmio_comm_loopback/build/make /protocols/systems/common/build/make/ /protocols/systems/tools/general/build/make "
#define omx_amrenc_sharedlibrary_link_type "loaded"
#define pvmtpip_so_name ""
#define pvavifileparser_m_mk ""
#define pvrtsp_cli_eng_real_cloaking_node_y_lib ""
#define pvaacparser_y_mk ""
#define LIBS_extern_libs_shared "       "
#define MODS_pvfileplaybackwithpvr_streaming "-lopencore_net_support -lopencore_player -lopencore_common -lpvpvrcommonimpl_streaming -lopencore_rtsp -lopencore_streaming"
#define getactualaacconfig_m_mk "/codecs_v2/audio/aac/dec/util/getactualaacconfig/build/make"
#define pvmp3ff_y_mk ""
#define pv_aac_dec_imp_m_lib ""
#define rfc_3016_mk "rfc_3016.mk"
#define pvasxparser_y_lib ""
#define pvmimeutils_y_mk ""
#define pvwavffrecognizer_m_lib "-lpvwavffrecognizer"
#define pvrtsp_cli_eng_node_y_lib ""
#define pvencoder_gsmamr_imp_m_lib ""
#define smrtsptplugininterface_m_lib "-lpvrtsptsmplugininterface"
#define pvdtcp_mbds_so_m_lib ""
#define pvmpeg2ffparsernode_y_lib ""
#define smrtsptrmpluginregpopulator_m_lib ""
#define omx_amr_component_y_lib ""
#define pvomxvideodecnode_m_lib "-lpvomxvideodecnode"
#define protocolenginenode_shoutcast_mk "/nodes/pvprotocolenginenode/download_protocols/shoutcast/build/make"
#define REGISTER_OMX_RV_COMPONENT 0
#define pvgeneraltools_y_mk ""
#define pvrealsupportcommon_so_name ""
#define omx_radec_sharedlibrary_aggregate_libtype "static"
#define omx_aacdec_sharedlibrary_aggregate_libtype "shared"
#define pvjitterbufferasf_m_lib ""
#define pvasxparser_m_mk ""
#define omx_m4venc_component_imp_m_mk ""
#define scsp_m_mk "/fileformats/scsp/build/make"
#define pvavcdecoder_imp_m_mk ""
#define pvdownloadinterface_m_lib "-lpvdownloadinterface"
#define pvwmdrmmd_m_lib ""
#define omx_queue_m_lib "-lomx_queue_lib"
#define MODS_opencore_streaming "-lopencore_net_support -lopencore_player -lopencore_common"
#define pvoma1passthru_so_name "pvoma1passthru"
#define amrparser_m_lib "-lamrparser"
#define omx_aac_component_y_lib ""
#define pvoma1lockstream_y_mk ""
#define pvplayreadyutility_y_lib ""
#define getaacaudioinfo_m_lib ""
#define pvauthorengine_m_lib "-lpvauthorengine"
#define pvdtcpplugin_y_lib ""
#define pvmediaoutputnode_y_lib ""
#define pvpvrcommonimpl_streaming_so_name ""
#define pvwavffparsernode_y_lib ""
#define DYNAMIC_LOAD_OMX_M4VENC_COMPONENT 1
#define AGGREGATE_LIBDIRS_opencore_pvme "/engines/pvme/build/make"
#define AGGREGATE_LIBDIRS_omx_radec_sharedlibrary " "
#define LIBDIR_omxdec_static "        "
#define MODS_omx_wmvdec_sharedlibrary "-lomx_sharedlibrary -lopencore_common"
#define pvrtsptunicast_streamingregreg_so_name "pvrtsptunicast_streamingreg"
#define pvdtcp_mbds_m_lib ""
#define pvrrtspunicastpluginregpopulator_m_mk ""
#define pvwavffrecognizer_m_mk "/pvmi/recognizer/plugins/pvwavffrecognizer/build/make"
#define pvasfff_y_lib ""
#define pvjitterbuffernode_m_lib "-lpvjitterbuffernode"
#define pvwavffrecognizer_y_lib ""
#define MODS_pvdb_recovery_utility "-lopencore_common -lpvdb"
#define USE_OLD_WMA_DECODER 0
#define AGGREGATE_LIBDIRS_pvplayerservice "/engines/player/build/make  /nodes/pvmediaoutputnode/build/make /nodes/pvfileoutputnode/build/make /nodes/pvwavffparsernode/build/make /pvmi/recognizer/plugins/pvwavffrecognizer/build/make /fileformats/wav/parser/build/make /nodes/pvmp3ffparsernode/build/make /pvmi/recognizer/plugins/pvmp3ffrecognizer/build/make /fileformats/mp3/parser/build/make  /nodes/pvmp4ffparsernode/build_opencore/make /pvmi/recognizer/plugins/pvmp4ffrecognizer/build/make  /fileformats/mp4/parser/build_opencore/make /fileformats/mp4/parser/utils/mp4recognizer/build/make         /nodes/pvaacffparsernode/build/make /pvmi/recognizer/plugins/pvaacffrecognizer/build/make /fileformats/rawaac/parser/build/make /nodes/pvamrffparsernode/build/make /pvmi/recognizer/plugins/pvamrffrecognizer/build/make /fileformats/rawgsmamr/parser/build/make     /pvmi/recognizer/build/make /nodes/pvcommonparsernode/build/make /fileformats/audioparser/common/build/make /fileformats/audioparser/amr/build/make /fileformats/audioparser/wav/build/make /pvmi/content_policy_manager/build/make /fileformats/scsp/build/make /fileformats/common/parser/build/make /fileformats/id3parcom/build/make /nodes/pvomxaudiodecnode/build/make /nodes/pvomxbasedecnode/build/make /codecs_v2/omx/omx_mastercore/build/make_multithreaded /protocols/rtp_payload_parser/util/build/latmparser/make /fileformats/scsp/build/make /codecs_v2/omx/omx_common/build/make_multithreaded /codecs_v2/omx/omx_proxy/build/make /codecs_v2/omx/omx_aac/build/make_multithreaded /codecs_v2/omx/omx_amr/build/make_multithreaded /codecs_v2/omx/omx_mp3/build/make_multithreaded   /codecs_v2/omx/omx_queue/build/make /codecs_v2/omx/omx_baseclass/build/make /codecs_v2/omx/omx_mastercore/build/make_multithreaded /codecs_v2/omx/omx_sharedlibrary/interface/build/make /codecs_v2/audio/aac/dec/util/getactualaacconfig/build/make  /codecs_v2/utilities/colorconvert/build/make /codecs_v2/utilities/m4v_config_parser/build/make /codecs_v2/utilities/pv_config_parser/build/make  /codecs_v2/audio/aac/dec/build/make /codecs_v2/audio/mp3/dec/build/make   /codecs_v2/audio/gsm_amr/amr_nb/dec/build/make /codecs_v2/audio/gsm_amr/amr_nb/common/build/make /codecs_v2/audio/gsm_amr/amr_wb/dec/build/make /baselibs/threadsafe_callback_ao/build/make /baselibs/media_data_structures/build/make /baselibs/gen_data_structures/build/make /pvmi/pvmf/build/make /baselibs/pv_mime_utils/build/make /codecs_v2/audio/gsm_amr/common/dec/build/make /nodes/common/build/make /engines/common/build/make /pvmi/content_policy_manager/plugins/common/build/make /oscl  "
#define pvomx_proxy_m_mk "/codecs_v2/omx/omx_proxy/build/make"
#define pvra8decoder_imp_m_mk ""
#define pvrtsptunicastfsp_y_mk ""
#define unit_test_utils_m_lib ""
#define pvdecoder_gsmamr_imp_m_mk ""
#define pvomxencnode_m_lib "-lpvomxencnode"
#define pv_smooth_streaming_m_mk ""
#define pvsdpparser_m_mk "/protocols/sdp/parser/build/make"
#define pvsqlite_y_mk ""
#define pvmp4interface_m_lib "-lpvmp4interface"
#define pv_aac_enc_y_lib ""
#define pvrtspunicast_streaming_aggregate_libtype "shared"
#define MODS_pv ""
#define pvmpeg2ffrecognizer_m_mk ""
#define LIBS_audio_static "             "
#define pvsmfspcommonimp_m_mk "/nodes/streaming/streamingmanager/plugins/common/build/make"
#define pvrtsp_cli_eng_node_m_lib "-lpvrtsp_cli_eng_node"
#define pvavch264enc_m_mk "/codecs_v2/video/avc_h264/enc/build/make"
#define pvplayreadyplugin_y_lib ""
#define pvm4vencoder_y_lib ""
#define LIBDIR_omxenc_static "   "
#define asf_payload_parser_y_lib ""
#define pvrtsptwithrealfsp_y_mk ""
#define rtppayloadparser_y_mk ""
#define pvid3parcom_m_mk "/fileformats/id3parcom/build/make"
#define opencore_author_so_name "opencore_author"
#define pvdownloadreginterface_m_mk "/modules/linux_download/node_registry/build/make"
#define AGGREGATE_LIBDIRS_pvwmdrmoemsettings ""
#define omx_amr_component_m_mk "/codecs_v2/omx/omx_amr/build/make_multithreaded"
#define MODS_pvrmff_recognizer "-lopencore_common"
#define pvcrypto_m_mk ""
#define pvplayreadyplugininterface_m_lib ""
#define AGGREGATE_LIBDIRS_opencore_player "         /pvmi/content_policy_manager/build/make /fileformats/pvx/parser/build/make /fileformats/id3parcom/build/make /nodes/pvamrffparsernode/build/make /pvmi/recognizer/plugins/pvamrffrecognizer/build/make /pvmi/recognizer/plugins/pvplsffrecognizer/build/make /fileformats/mp3/parser/build/make /nodes/pvmp3ffparsernode/build/make /pvmi/recognizer/plugins/pvmp3ffrecognizer/build/make  /fileformats/mp4/parser/build_opencore/make /fileformats/mp4/parser/utils/mp4recognizer/build/make /fileformats/rawaac/parser/build/make /nodes/pvaacffparsernode/build/make /pvmi/recognizer/plugins/pvaacffrecognizer/build/make /nodes/pvwavffparsernode/build/make /pvmi/recognizer/plugins/pvwavffrecognizer/build/make /nodes/pvcommonparsernode/build/make /fileformats/audioparser/common/build/make /fileformats/audioparser/amr/build/make /fileformats/audioparser/wav/build/make    /pvmi/recognizer/build/make   /engines/adapters/player/framemetadatautility/build/make /engines/player/build/make"
#define pvfasttrack_downloadreg_so_name ""
#define pvfileplaybackwithpvr_streaming_aggregate_libtype "static"
#define pvrtspunicastwithpvr_streamingreg_aggregate_libtype "static"
#define MODS_pvmtpdrmmanagerplugin "-lopencore_common -lpvwmdrmmd"
#define pvflvffparsernode_m_mk ""
#define pvmpeg2ff_y_mk ""
#define pvaacffparsernode_m_lib "-lpvaacffparsernode"
#define pvprotocolenginenode_wmhttpstreaming_plugin_m_mk ""
#define MODS_pvplayready "-lopencore_common -lpvwmdrmmd"
#define pvjitterbufferrtp_y_lib ""
#define pvomxencnode_y_mk ""
#define AGGREGATE_LIBDIRS_opencore_common "/oscl   /codecs_v2/omx/omx_mastercore/build/make_multithreaded                 /codecs_v2/audio/gsm_amr/common/dec/build/make /fileformats/rawgsmamr/parser/build/make /codecs_v2/audio/aac/dec/util/getactualaacconfig/build/make /codecs_v2/utilities/m4v_config_parser/build/make /codecs_v2/utilities/pv_config_parser/build/make /codecs_v2/utilities/colorconvert/build/make /baselibs/threadsafe_callback_ao/build/make /baselibs/media_data_structures/build/make /baselibs/pv_mime_utils/build/make /baselibs/gen_data_structures/build/make /pvmi/pvmf/build/make /nodes/pvfileoutputnode/build/make /nodes/pvmediainputnode/build/make_pvauthor /nodes/pvomxencnode/build/make /pvmi/media_io/pvmi_mio_fileinput/build/make_pvauthor /baselibs/thread_messaging/build/make /pvmi/media_io/pvmiofileoutput/build/make /nodes/pvmediaoutputnode/build/make /nodes/pvomxvideodecnode/build/make /nodes/pvomxaudiodecnode/build/make /nodes/pvomxbasedecnode/build/make /protocols/rtp_payload_parser/util/build/latmparser/make /fileformats/wav/parser/build/make /fileformats/common/parser/build/make /fileformats/scsp/build/make /nodes/common/build/make /engines/common/build/make /pvmi/content_policy_manager/plugins/common/build/make"
#define pvflvffrecognizer_y_mk ""
#define omx_wmv_component_imp_m_mk ""
#define pvmtp_so_name ""
#define MODS_pvdbconfigclass "-lopencore_common"
#define pvmpeg2reginterface_m_mk ""
#define pvrtspunicastfsp_y_mk ""
#define pvrtppacketsourcenode_m_mk ""
#define omx_common_y_mk ""
#define MODS_omx_avcdec_sharedlibrary "-lomx_sharedlibrary -lopencore_common"
#define BUILD_PROGRESSIVE_DOWNLOAD_PLUGIN 1
#define pvasfffrecognizer_m_mk ""
#define pvfileplaybackwithpvr_streamingreg_aggregate_libtype "static"
#define pvlatmpayloadparser_y_lib ""
#define pvg726decoder_y_mk ""
#define pvmp4ffparsernode_m_mk ""
#define wmavoicedecoder_y_mk ""
#define pvmp4eu_m_lib ""
#define pvpvxparser_y_mk ""
#define pv_m3u_parser_y_lib ""
#define rfc_3640_mk "rfc_3640.mk"
#define pv_rtmp_parcom_y_mk ""
#define omx_m4venc_component_m_lib "-lomx_m4venc_component_lib"
#define pvmp4ffcomposernodeopencore_m_lib "-lpvmp4ffcomposernode"
#define rfc_3267_mk "rfc_3267.mk"
#define LIBS_media_io_shared "-lpvmiofileoutput -lpvmiofileinput  -lpvmio_comm_loopback"
#define LIBS_audio_shared "    -lpv_aac_dec  -lpv_amr_nb_common_lib -lpvamrwbdecoder -lpvdecoder_gsmamr -lpvmp3   -lpvencoder_gsmamr "
#define MODS_pvfasttrack_download "-lopencore_net_support -lopencore_common"
#define pvrmffrecognizer_y_lib ""
#define pvrrtspunicastplugininterface_m_mk ""
#define omx_amrdec_sharedlibrary_aggregate_libtype "shared"
#define pvplsffrecognizer_m_lib "-lpvplsffrecognizer"
#define audioparser_y_mk ""
#define pvmioaviwavfileinput_y_lib "-lpvmioaviwavfileinput"
#define pvfasttrack_downloadreg_link_type "loaded"
#define pvrtsp_cli_eng_real_cloaking_node_m_mk ""
#define WMA_BUILD_CFG_STD_ENABLED 0
#define pvdb_recovery_utility_m_lib ""
#define pvsminterface_m_mk "/modules/linux_rtsp/core/build/make"
#define omx_avcenc_component_m_mk "/codecs_v2/omx/omx_h264enc/build/make_multithreaded"
#define omx_avcenc_component_imp_m_lib ""
#define pvmp4ffcomposernodeopencore_y_mk ""
#define wmavoicedecoder_imp_m_lib ""
#define pvsocketnode_m_lib "-lpvsocketnode"
#define pvgsmamrparser_m_mk "/fileformats/rawgsmamr/parser/build/make"
#define pvprotocolengine_asfstreamingreg_link_type "loaded"
#define rvdecoder_m_mk ""
#define pvmp4ffparsernodeopencore_m_mk "/nodes/pvmp4ffparsernode/build_opencore/make"
#define pvmtpdrmmanagerplugin_aggregate_libtype "static"
#define MODS_pvmshttp_streamingreg "-lopencore_common -lopencore_streaming"
#define pv324m_common_headers_m_mk "/protocols/systems/common/build/make/"
#define pvrtspunicastwithpvrfsp_y_lib ""
#define MODS_pvoma1passthru "-lopencore_player -lopencore_common"
#define REGISTER_OMX_MP3_COMPONENT 1
#define asf_payload_parser_m_lib ""
#define LIBS_omxdec_shared "-lomx_avc_component_lib -lomx_m4v_component_lib   -lomx_aac_component_lib -lomx_amr_component_lib -lomx_mp3_component_lib  "
#define pvmp4interface_m_mk "/modules/linux_mp4/core/build/make"
#define REGISTER_OMX_AVC_COMPONENT 1
#define pv_m3u_parser_y_mk ""
#define pvaacffparsernode_y_lib ""
#define protocolenginenode_ftdl_mk ""
#define omx_mp3_component_imp_m_mk ""
#define pvasfffparsernode_m_mk ""
#define m4v_config_y_lib ""
#define pvmp4ffparsernodeopencore_m_lib "-lpvmp4ffparsernode"
#define realmedia_payload_parser_y_lib ""
#define AGGREGATE_LIBDIRS_opencore_net_support "/nodes/pvsocketnode/build/make /protocols/http_parcom/build/make /nodes/pvprotocolenginenode/base/build/make /nodes/pvprotocolenginenode/protocol_common/build/make /nodes/pvprotocolenginenode/download_protocols/common/build/make /nodes/pvprotocolenginenode/download_protocols/progressive_download/build/make /nodes/pvprotocolenginenode/download_protocols/progressive_streaming/build/make /nodes/pvprotocolenginenode/download_protocols/shoutcast/build/make /nodes/streaming/jitterbuffernode/jitterbuffer/common/build/make /nodes/streaming/jitterbuffernode/build/make /protocols/sdp/parser/build/make /protocols/sdp/common/build/make /protocols/rtp/build/make"
#define pvavch264enc_m_lib "-lpvavch264enc"
#define AGGREGATE_LIBDIRS_opencore_mp4local "/modules/linux_mp4/core/build/make  /nodes/pvmp4ffparsernode/build_opencore/make"
#define pvwmdrmoemsettingsinterface_m_lib ""
#define pvwavffparsernode_y_mk ""
#define pvdivxoemsettings_so_name ""
#define BUILD_STATIC_RTSP_BROADCAST_PVR 0
#define pvplsffrecognizer_y_mk ""
#define pvrtspunicastwithpvr_streamingreg_so_name ""
#define omx_wmv_component_m_lib ""
#define pvwmdrmmd_y_lib ""
#define unit_test_utils_y_mk "/oscl/unit_test_utils/build/make"
#define AGGREGATE_LIBDIRS_pvoma1passthru "/pvmi/content_policy_manager/plugins/oma1/passthru/build/make /modules/cpm_oma1_passthru/build/make"
#define pvaacffrecognizer_m_mk "/pvmi/recognizer/plugins/pvaacffrecognizer/build/make"
#define pvrtsptunicastfsp_m_lib "-lpvrtsptunicaststreamingmanager"
#define pvrtspunicast_streaming_link_type "loaded"
#define omx_amr_component_m_lib "-lomx_amr_component_lib"
#define LIBDIR_omxdecimp_static ""
#define pvcommsionode_m_lib "-lpvcommsionode"
#define pvmiofileoutput_m_mk "/pvmi/media_io/pvmiofileoutput/build/make"
#define BUILD_RTMPSTREAMING_PLUGIN 0
#define pvmediainputnode_y_lib ""
#define omx_aac_component_m_mk "/codecs_v2/omx/omx_aac/build/make_multithreaded"
#define omx_ra_component_m_mk ""
#define BUILD_STATIC_MSHTTP_ASF 0
#define AGGREGATE_LIBDIRS_pvwmdrmmd "    "
#define pv_aac_dec_y_lib ""
#define pvgsmamrparser_y_lib ""
#define pvoma1ffrecognizer_m_lib ""
#define pvdb_recovery_utility_so_name ""
#define protocolenginenode_pdl_mk "/nodes/pvprotocolenginenode/download_protocols/progressive_download/build/make"
#define rtprtcp_y_lib ""
#define pvasfffparsernode_m_lib ""
#define secure_data_format_y_mk ""
#define LIBDIR_shared "/oscl      /baselibs/gen_data_structures/build/make /baselibs/media_data_structures/build/make /baselibs/pv_mime_utils/build/make /baselibs/threadsafe_callback_ao/build/make /baselibs/thread_messaging/build/make  /codecs_v2/omx/omx_h264/build/make_multithreaded /codecs_v2/omx/omx_m4v/build/make_multithreaded   /codecs_v2/omx/omx_aac/build/make_multithreaded /codecs_v2/omx/omx_amr/build/make_multithreaded /codecs_v2/omx/omx_mp3/build/make_multithreaded   /codecs_v2/omx/omx_amrenc/build/make_multithreaded /codecs_v2/omx/omx_m4venc/build/make_multithreaded /codecs_v2/omx/omx_h264enc/build/make_multithreaded  /codecs_v2/omx/omx_common/build/make_multithreaded /codecs_v2/omx/omx_queue/build/make /codecs_v2/omx/omx_proxy/build/make /codecs_v2/omx/omx_baseclass/build/make /codecs_v2/omx/omx_mastercore/build/make_multithreaded /codecs_v2/omx/omx_sharedlibrary/interface/build/make      /codecs_v2/audio/aac/dec/build/make  /codecs_v2/audio/gsm_amr/amr_nb/common/build/make /codecs_v2/audio/gsm_amr/amr_wb/dec/build/make /codecs_v2/audio/gsm_amr/amr_nb/dec/build/make /codecs_v2/audio/mp3/dec/build/make   /codecs_v2/audio/gsm_amr/common/dec/build/make /codecs_v2/audio/gsm_amr/amr_nb/enc/build/make  /codecs_v2/video/avc_h264/common/build/make /codecs_v2/video/avc_h264/dec/build/make   /codecs_v2/video/m4v_h263/dec/build/make  /codecs_v2/video/m4v_h263/enc/build/make /codecs_v2/video/avc_h264/enc/build/make /codecs_v2/utilities/m4v_config_parser/build/make /codecs_v2/utilities/pv_config_parser/build/make /codecs_v2/utilities/colorconvert/build/make /fileformats/common/parser/build/make /fileformats/id3parcom/build/make /fileformats/pvx/parser/build/make /fileformats/wav/parser/build/make    /fileformats/mp3/parser/build/make /fileformats/rawaac/parser/build/make /fileformats/rawgsmamr/parser/build/make    /fileformats/mp4/parser/utils/mp4recognizer/build/make /fileformats/mp4/parser/build_opencore/make  /fileformats/mp4/composer/build_opencore/make    /fileformats/scsp/build/make       /fileformats/audioparser/common/build/make /fileformats/audioparser/amr/build/make /fileformats/audioparser/wav/build/make /protocols/http_parcom/build/make  /protocols/rtp_payload_parser/util/build/latmparser/make /protocols/sdp/parser/build/make /protocols/sdp/common/build/make  /protocols/rtsp_parcom/build/make /protocols/rtsp_client_engine/build/make_segments     /protocols/rtp_payload_parser/build/make /protocols/rtp/build/make /protocols/systems/3g-324m_pvterminal/build/make/   /protocols/systems/common/build/make/ /protocols/systems/tools/general/build/make  /pvmi/content_policy_manager/build/make /pvmi/content_policy_manager/plugins/oma1/passthru/build/make /pvmi/content_policy_manager/plugins/common/build/make     /pvmi/media_io/pvmiofileoutput/build/make /pvmi/media_io/pvmi_mio_fileinput/build/make_pvauthor  /pvmi/media_io/pvmio_comm_loopback/build/make /pvmi/recognizer/build/make /pvmi/recognizer/plugins/pvaacffrecognizer/build/make /pvmi/recognizer/plugins/pvamrffrecognizer/build/make   /pvmi/recognizer/plugins/pvmp3ffrecognizer/build/make /pvmi/recognizer/plugins/pvmp4ffrecognizer/build/make  /pvmi/recognizer/plugins/pvwavffrecognizer/build/make   /pvmi/recognizer/plugins/pvplsffrecognizer/build/make   /pvmi/pvmf/build/make            /nodes/pvfileoutputnode/build/make /nodes/pvmediaoutputnode/build/make /nodes/pvsocketnode/build/make /nodes/pvprotocolenginenode/base/build/make /nodes/pvprotocolenginenode/protocol_common/build/make /nodes/pvprotocolenginenode/download_protocols/common/build/make /nodes/pvprotocolenginenode/download_protocols/progressive_download/build/make /nodes/pvprotocolenginenode/download_protocols/progressive_streaming/build/make /nodes/pvprotocolenginenode/download_protocols/shoutcast/build/make /nodes/pvwavffparsernode/build/make /nodes/pvomxencnode/build/make /nodes/pvomxbasedecnode/build/make /nodes/pvomxaudiodecnode/build/make /nodes/pvomxvideodecnode/build/make /nodes/pvaacffparsernode/build/make /nodes/pvamrffparsernode/build/make  /nodes/pvmp3ffparsernode/build/make  /nodes/pvmp4ffparsernode/build_opencore/make   /nodes/common/build/make /nodes/pvmediainputnode/build/make_pvauthor  /nodes/pvmp4ffcomposernode/build_opencore/make   /nodes/pvdownloadmanagernode/build/make  /nodes/streaming/streamingmanager/plugins/rtspunicast/build/make /nodes/streaming/streamingmanager/plugins/rtsptunicast/build/make     /nodes/streaming/streamingmanager/plugins/common/build/make  /nodes/streaming/streamingmanager/build/make   /modules/linux_rtsp/smplugins/unicast/core/build/make /modules/linux_rtsp/smplugins/unicast/registry/build/make /modules/linux_rtsp/smplugins/tunneling/core/build/make /modules/linux_rtsp/smplugins/tunneling/registry/build/make          /nodes/streaming/jitterbuffernode/jitterbuffer/common/build/make /nodes/streaming/jitterbuffernode/jitterbuffer/rtp/build/make  /nodes/streaming/jitterbuffernode/build/make /nodes/pvcommsionode/build/make /nodes/pvclientserversocketnode/build/make /nodes/pvloopbacknode/build/make      /nodes/pvcommonparsernode/build/make /engines/player/build/make /engines/author/build/make /engines/2way/build/make /engines/2way/sample_app/pv2waysample/build/make /engines/common/build/make /engines/adapters/player/framemetadatautility/build/make /engines/pvme/build/make   /modules/linux_rtsp/core/build/make /modules/linux_rtsp/node_registry/build/make   /modules/linux_rtsp/smplugins/unicast/core/build/make /modules/linux_rtsp/smplugins/unicast/registry/build/make /modules/linux_rtsp/smplugins/tunneling/core/build/make /modules/linux_rtsp/smplugins/tunneling/registry/build/make         /modules/linux_download/core/build/make /modules/linux_download/node_registry/build/make /modules/linux_mp4/core/build/make /modules/linux_mp4/node_registry/build/make         /modules/cpm_oma1_passthru/build/make           "
#define omx_aac_component_imp_m_lib ""
#define omx_ra_component_imp_m_lib ""
#define divxrecognizer_utility_y_lib ""
#define protocolenginenode_ps_lib "-lprotocolenginenode_ps"
#define pvsmfspcommonimp_y_mk ""
#define pvmp3ffparsernode_y_lib ""
#define pvdivxinterface_m_mk ""
#define MODS_pvdivxparser_node "-lpvdivx_recognizer -lopencore_player -lopencore_common"
#define omx_wmadec_sharedlibrary_so_name ""
#define omx_ra_component_m_lib ""
#define omx_aac_component_m_lib "-lomx_aac_component_lib"
#define wmadecoderlibpath "/codecs_v2/audio/wma/dec/build/make"
#define pvmtpip_engine_y_lib ""
#define pvmp4decoder_m_lib "-lpvmp4decoder"
#define pvrmffparser_y_mk ""
#define opencore_player_aggregate_libtype "shared"
#define scsp_y_lib ""
#define pvrfileplaybackplugininterface_m_lib ""
#define omx_avcenc_component_y_mk ""
#define optimized_bcast_ps_mk ""
#define wmadecoder_y_lib ""
#define oscllib_lib "-loscllib"
#define pvclientserversocketnode_y_lib ""
#define pvrmff_m_lib ""
#define DYNAMIC_LOAD_OMX_AMR_COMPONENT 1
#define pvavch264enc_imp_m_lib ""
#define pvasfff_m_lib ""
#define LIBS_omxdec_static "            "
#define DYNAMIC_LOAD_OMX_AVCENC_COMPONENT 1
#define AVC_MP_DECODER_ENABLED 0
#define REGISTER_OMX_WMA_COMPONENT 0
#define pv_http_parcom_m_lib "-lpv_http_parcom"
#define pvrbroadcastpluginregpopulator_m_mk ""
#define pv_rtsp_parcom_m_mk "/protocols/rtsp_parcom/build/make"
#define pvoma1passthruplugin_m_mk "/pvmi/content_policy_manager/plugins/oma1/passthru/build/make"
#define omx_wma_component_y_lib ""
#define pvrmffrecognizer_utility_m_mk ""
#define csprng_m_lib ""
#define smrtsptplugininterface_m_mk "/modules/linux_rtsp/smplugins/tunneling/core/build/make"
#define LIBS_fileformats_shared "-lpvfileparserutils -lpvid3parcom -lpvpvxparser -lpvwav    -lpvmp3ff -lpvaacparser -lpvgsmamrparser   -lmp4recognizer_utility -lpvmp4ff  -lpvmp4ffcomposer    -lscsp       -laudioparser -lamrparser -lwavparser"
#define pvwmdrmoemsettings_aggregate_libtype "static"
#define LIBS_engines_static "       "
#define pv_smooth_streaming_y_mk ""
#define pvmp3_m_lib "-lpvmp3"
#define opencore_download_aggregate_libtype "shared"
#define pvsdpparser_plugins " sdp_opencore.mk"
#define pvmimeutils_m_mk "/baselibs/pv_mime_utils/build/make"
#define AGGREGATE_LIBDIRS_pvprotocolengine_asfstreamingreg ""
#define protocolenginenode_segments_mk "/nodes/pvprotocolenginenode/base/build/make /nodes/pvprotocolenginenode/protocol_common/build/make /nodes/pvprotocolenginenode/download_protocols/common/build/make /nodes/pvprotocolenginenode/download_protocols/progressive_download/build/make /nodes/pvprotocolenginenode/download_protocols/progressive_streaming/build/make /nodes/pvprotocolenginenode/download_protocols/shoutcast/build/make"
#define omx_mp3dec_sharedlibrary_link_type "loaded"
#define pvsqlite_so_name ""
#define asf_payload_parser_m_mk ""
#define pv_http_retriever_y_lib ""
#define pvamrwbdecoder_imp_m_lib ""
#define oscl_m_lib "-lpvlogger -losclregcli -losclregserv -losclutil -losclproc  -losclio -losclmemory -losclerror -losclbase"
#define pvasfffrecognizer_y_lib ""
#define pvmediainputnode_y_mk ""
#define pvdivxreginterface_m_mk ""
#define omx_common_m_lib "-lomx_common_lib"
#define pvprotocolenginefasttrackdownloadinterface_m_mk ""
#define pvwav_m_mk "/fileformats/wav/parser/build/make"
#define omx_m4venc_sharedlibrary_link_type "loaded"
#define pvrmffinterface_m_mk ""
#define pvflvffrecognizer_m_mk ""
#define AGGREGATE_LIBDIRS_pvrtspunicastwithpvr_streamingreg ""
#define pvmp4ffcomposeropencore_y_lib ""
#define pvmp4ffparsernodeopencore_y_lib ""
#define LIBS_baselibs_shared "   -lpvgendatastruct -lpvmediadatastruct -lpvmimeutils -lthreadsafe_callback_ao -lpvthreadmessaging "
#define pvfileparserutils_m_lib "-lpvfileparserutils"
#define pvmshttp_streamingreg_so_name ""
#define pvlatmpayloadparser_m_mk "/protocols/rtp_payload_parser/util/build/latmparser/make"
#define pvid3parcom_m_lib "-lpvid3parcom"
#define pvdivxdrmplugininterface_m_lib ""
#define LIBDIR_fileformats_static "     /fileformats/avi/parser/build/make                        "
#define LIBS_cpm_shared "-lcpm -lpvoma1passthruplugin    "
#define secure_data_format_y_lib ""
#define omx_m4venc_sharedlibrary_aggregate_libtype "shared"
#define LIBS_pvmi_static "        -lpvmioaviwavfileinput                   "
#define pv_amr_nb_common_lib_m_mk "/codecs_v2/audio/gsm_amr/amr_nb/common/build/make"
#define pvcrypto_y_lib ""
#define AGGREGATE_LIBDIRS_pvasfcommon " "
#define LIBDIR_cpm_static "      "
#define opencore_pvme_so_name "opencore_pvme"
#define LIBDIR_omxjointimp_static ""
#define pvjitterbuffernode_y_lib ""
#define pvdownloadmanagernode_m_mk "/nodes/pvdownloadmanagernode/build/make"
#define pviptransport_m_mk ""
#define pvmediaoutputnode_y_mk ""
#define MODS_omx_aacdec_sharedlibrary "-lomx_sharedlibrary -lopencore_common"
#define AGGREGATE_LIBDIRS_pvpvrcommonimpl_streaming ""
#define LIBS_packetsources_static ""
#define pvstreamingmanagernode_m_lib "-lpvstreamingmanagernode"
#define opencore_net_support_aggregate_libtype "shared"
#define pvfasttrack_downloadreg_aggregate_libtype "static"
#define pv_http_retriever_m_lib ""
#define opencore_mp4localreg_link_type "loaded"
#define AGGREGATE_LIBDIRS_pvmpeg2local "  "
#define LIBDIR_omxdecimp_shared ""
#define pvmio_comm_loopback_m_mk "/pvmi/media_io/pvmio_comm_loopback/build/make"
#define opencore_streamingreg_aggregate_libtype "shared"
#define pvlatmpayloadparser_m_lib "-lpvlatmpayloadparser"
#define pv2wayengine_m_lib "-lpv2wayengine"
#define pvamrffrecognizer_m_lib "-lpvamrffrecognizer"
#define omx_wmv_component_m_mk ""
#define pvflvffrecognizer_y_lib ""
#define smrtsptpluginregpopulator_m_mk "/modules/linux_rtsp/smplugins/tunneling/registry/build/make"
#define AGGREGATE_LIBDIRS_omx_aacenc_sharedlibrary " "
#define LIBS_codecs_v2_shared "-lomx_avc_component_lib -lomx_m4v_component_lib   -lomx_aac_component_lib -lomx_amr_component_lib -lomx_mp3_component_lib   -lomx_amrenc_component_lib -lomx_m4venc_component_lib -lomx_avcenc_component_lib  -lomx_common_lib -lomx_queue_lib -lpvomx_proxy_lib -lomx_baseclass_lib -lomx_mastercore_lib -lpv_omx_interface     -lpv_aac_dec  -lpv_amr_nb_common_lib -lpvamrwbdecoder -lpvdecoder_gsmamr -lpvmp3   -lpvencoder_gsmamr  -lpv_avc_common_lib -lpvavcdecoder   -lpvmp4decoder  -lpvm4vencoder -lpvavch264enc -lm4v_config -lpv_config_parser -lcolorconvert"
#define opencore_pvme_aggregate_libtype "shared"
#define opencore_downloadreg_aggregate_libtype "shared"
#define pvdecoder_gsmamr_imp_m_lib ""
#define pvasflocalpbreg_aggregate_libtype "static"
#define pvdivxdrm_oem_settings_y_lib ""
#define omx_mastercore_m_mk "/codecs_v2/omx/omx_mastercore/build/make_multithreaded"
#define pvdivxparser_node_so_name ""
#define pvplayerservice_aggregate_libtype "static"
#define pvprotocolenginenode_ftdl_plugin_m_mk ""
#define omx_avc_component_m_mk "/codecs_v2/omx/omx_h264/build/make_multithreaded"
#define omx_aacenc_sharedlibrary_aggregate_libtype "static"
#define getactualaacconfig_imp_m_lib "-lgetactualaacconfig"
#define pvencoder_gsmamr_imp_m_mk ""
#define LIBDIR_recognizer_static "            "
#define MODS_pvmpeg2local "-lopencore_common -lopencore_player -lpvmpeg2localreg"
#define cpm_m_lib "-lcpm"
#define pvrmff_recognizer_aggregate_libtype "static"
#define MODS_opencore_author "-lopencore_common"
#define wmvdecoder_imp_m_mk ""
#define pvdivxdrm_aggregate_libtype "static"
#define pvamrffparsernode_y_lib ""
#define pvmioaviwavfileinput_m_lib ""
#define pv324m_plugins "default_support.mk"
#define MODS_omx_wmadec_sharedlibrary "-lomx_sharedlibrary -lopencore_common"
#define divxrecognizer_utility_m_lib ""
#define LIBDIR_recognizer_shared "/pvmi/recognizer/build/make /pvmi/recognizer/plugins/pvaacffrecognizer/build/make /pvmi/recognizer/plugins/pvamrffrecognizer/build/make   /pvmi/recognizer/plugins/pvmp3ffrecognizer/build/make /pvmi/recognizer/plugins/pvmp4ffrecognizer/build/make  /pvmi/recognizer/plugins/pvwavffrecognizer/build/make   /pvmi/recognizer/plugins/pvplsffrecognizer/build/make "
#define REGISTER_OMX_WMV_COMPONENT 0
#define omx_m4v_component_m_lib "-lomx_m4v_component_lib"
#define pvmpeg2ffparsernode_m_lib ""
#define pvomxbasedecnode_y_lib ""
#define MODS_pvrtsptunicast_streaming "-lopencore_net_support -lopencore_player -lopencore_common -lopencore_rtsp -lopencore_streaming"
#define pvsocketnode_m_mk "/nodes/pvsocketnode/build/make"
#define omx_avcdec_sharedlibrary_so_name "omx_avcdec_sharedlibrary"
#define pvdivx_recognizer_aggregate_libtype "static"
#define pvdownloadmanagernode_m_lib "-lpvdownloadmanagernode"
#define amrparser_y_lib ""
#define packetsources_default_m_mk ""
#define pvrtspbroadcastwithpvr_streamingreg_so_name ""
#define pvmp4ffrecognizer_m_lib "-lpvmp4ffrecognizer"
#define pvprotocolenginefasttrackdownloadpluginreginterface_m_mk ""
#define pv2waysample_y_lib ""
#define smrtsptrmplugininterface_m_lib ""
#define pvmp4ffcomposer_m_lib ""
#define pvflv_recognizer_aggregate_libtype "static"
#define pvrtspbroadcastwithpvr_streaming_so_name ""
#define rdt_parser_m_mk ""
#define WMA_BUILD_CFG_STDPROSTEREOLBRV1_ENABLED 0
#define pvencoder_gsmamr_m_mk "/codecs_v2/audio/gsm_amr/amr_nb/enc/build/make"
#define pv_rtsp_parcom_y_mk ""
#define opencore_streamingreg_link_type "loaded"
#define pvmio_comm_loopback_m_lib "-lpvmio_comm_loopback"
#define omx_wmv_component_y_lib ""
#define smrtspunicastpluginregpopulator_m_lib "-lpvrtspsmpluginreginterface"
#define pvcommonparsernode_y_lib ""
#define omx_m4vdec_sharedlibrary_so_name "omx_m4vdec_sharedlibrary"
#define LIBDIR_media_io_static "  /pvmi/media_io/pvmi_mio_avi_wav_fileinput/build/make "
#define pvplayreadyutility_y_mk ""
#define pvrtspunicastwithpvr_streaming_so_name ""
#define AGGREGATE_LIBDIRS_omx_mp3dec_sharedlibrary "/codecs_v2/omx/omx_mp3/build/make_multithreaded /codecs_v2/audio/mp3/dec/build/make"
#define AGGREGATE_LIBDIRS_pvrealsupportcommon ""
#define g726decnode_y_lib ""
#define pvasflocalpbinterface_m_mk ""
#define MODS_omx_rvdec_sharedlibrary "-lomx_sharedlibrary -lopencore_common"
#define pvmp4decoder_m_mk "/codecs_v2/video/m4v_h263/dec/build/make"
#define pvmp4ffparsernode_y_mk ""
#define omx_aacenc_sharedlibrary_link_type "loaded"
#define pvdtcp_mbds_so_name ""
#define pvmpeg2localreg_so_name ""
#define BUILD_SMOOTHSTREAMING_PLUGIN 0
#define omx_aacenc_component_m_mk ""
#define pv_http_retriever_m_mk ""
#define LIBDIR_protocols_static "                   "
#define pvtinyxml_y_mk ""
#define LIBDIR_codecs_utilities_shared "/codecs_v2/utilities/m4v_config_parser/build/make /codecs_v2/utilities/pv_config_parser/build/make /codecs_v2/utilities/colorconvert/build/make"
#define AGGREGATE_LIBDIRS_pvprotocolengine_asfstreaming " "
#define pvflvffparsernode_y_mk ""
#define pvdbconfigclass_link_type "loaded"
#define rtspbasedpluginselected_y_config 0
#define pv_avc_common_lib_m_lib "-lpv_avc_common_lib"
#define pvrmffreginterface_m_lib ""
#define AGGREGATE_LIBDIRS_pvflv_recognizer "  "
#define pvrmffparsernode_y_mk ""
#define LIBS_extern_libs_static "       "
#define pvmp3ff_m_lib "-lpvmp3ff"
#define AGGREGATE_LIBDIRS_pviptransport ""
#define pvdivxparser_node_aggregate_libtype "static"
#define LIBDIR_extern_libs_static "       "
#define pvmp3_y_lib ""
#define pvdivxdrmplugin_m_mk ""
#define protocolenginenode_base_lib "-lprotocolenginenode_base"
#define pvaacparser_y_lib ""
#define pvmpeg2ffparsernode_m_mk ""
#define omx_rv_component_imp_m_mk ""
#define MODS_opencore_rtsp "-lopencore_net_support -lopencore_player -lopencore_common"
#define pvdb_recovery_utility_aggregate_libtype "static"
#define REGISTER_OMX_AMR_COMPONENT 1
#define pvmtp_aggregate_libtype "static"
#define BUILD_WMHTTPSTREAMING_PLUGIN 0
#define MODS_pvrtspunicast_streamingreg "-lopencore_common -lopencore_streaming"
#define omx_aacdec_sharedlibrary_link_type "loaded"
#define omx_radec_sharedlibrary_link_type "loaded"
#define pv_avc_common_imp_lib_m_mk ""
#define engines_common_headers_m_mk "/engines/common/build/make"
#define pvoma1passthruplugin_y_mk ""
#define pvdivxdrm_so_name ""
#define pvdivxdrm_m_mk ""
#define pvflvff_y_lib ""
#define LIBDIR_omxencimp_static ""
#define pvrmffreginterface_m_mk ""
#define LIBDIR_packetsources_static ""
#define omx_amrenc_sharedlibrary_aggregate_libtype "shared"
#define MODS_omx_m4venc_sharedlibrary "-lomx_sharedlibrary -lopencore_common "
#define pvjitterbufferrtp_m_lib "-lpvjitterbufferrtp"
#define pvmp4ff_y_mk ""
#define pvmp4ffcomposernode_m_mk ""
#define LIBDIR_oscl_shared "/oscl  "
#define realmedia_payload_parser_m_lib ""
#define AGGREGATE_LIBDIRS_pvfileplaybackwithpvr_streaming " "
#define cpm_headers_y_mk ""
#define audioparser_m_lib "-laudioparser"
#define pv_aac_dec_imp_m_mk ""
#define omx_wmv_component_imp_m_lib ""
#define DYNAMIC_LOAD_OMX_H263ENC_COMPONENT 1
#define omx_m4v_component_imp_m_mk ""
#define protocolenginenode_common_mk "/nodes/pvprotocolenginenode/protocol_common/build/make"
#define LIBDIR_media_io_shared "/pvmi/media_io/pvmiofileoutput/build/make /pvmi/media_io/pvmi_mio_fileinput/build/make_pvauthor  /pvmi/media_io/pvmio_comm_loopback/build/make"
#define pvflvinterface_m_mk ""
#define pvamrffparsernode_m_mk "/nodes/pvamrffparsernode/build/make"
#define pvmpeg2localreg_link_type "loaded"
#define pvasfffparsernode_y_mk ""
#define pv_avc_common_lib_m_mk "/codecs_v2/video/avc_h264/common/build/make"
#define pv_aac_dec_plugins "aacdec_util.mk"
#define pv_srs_wowhd_m_lib ""
#define pvfileplaybackwithpvr_streaming_so_name ""
#define realmedia_payload_parser_y_mk ""
#define colorconvert_m_mk "/codecs_v2/utilities/colorconvert/build/make"
#define threadsafe_callback_ao_m_lib "-lthreadsafe_callback_ao"
#define omx_wmadec_sharedlibrary_link_type "loaded"
#define opencore_rtsp_so_name "opencore_rtsp"
#define mpeg2recognizer_utility_m_lib ""
#define pvmpeg2ffrecognizer_m_lib ""
#define LIBDIR_codecs_utilities_static "  "
#define pvpvrcommonimp_y_lib ""
#define pvmetadata_engine_m_mk "/engines/pvme/build/make"
#define pvauthorengine_m_mk "/engines/author/build/make"
#define getaacaudioinfo_m_mk ""
#define pvmshttpfsp_m_lib ""
#define pvomxvideodecnode_y_mk ""
#define opencore_streaming_link_type "loaded"
#define pvmediadatastruct_y_mk ""
#define pvasfffrecognizer_m_lib ""
#define pvplayreadyplugin_m_mk ""
#define protocolenginenode_download_common_mk "/nodes/pvprotocolenginenode/download_protocols/common/build/make"
#define pvrmffrecognizer_y_mk ""
#define pvavifileparser_m_lib ""
#define omx_avcenc_component_y_lib ""
#define rtprtcp_y_mk ""
#define pvmp4reginterface_m_mk "/modules/linux_mp4/node_registry/build/make"
#define omx_m4venc_component_y_mk ""
#define LIBDIR_module "/modules"
#define pvpvxparser_m_mk "/fileformats/pvx/parser/build/make"
#define protocolenginenode_common_lib "-lprotocolenginenode_common"
#define pv_omx_interface_m_lib "-lpv_omx_interface"
#define MODS_pvmshttp_streaming "-lopencore_net_support -lopencore_player -lopencore_common -lopencore_streaming -lpvasfcommon"
#define smmshttppluginregpopulator_m_mk ""
#define pvrmffrecognizer_m_lib ""
#define rtspbasedpluginselected_m_config 1
#define pvrtsp_cli_eng_playlist_node_m_lib ""
#define pv_avc_mp_decoder_y_lib ""
#define mp4recognizer_utility_m_mk "/fileformats/mp4/parser/utils/mp4recognizer/build/make"
#define pvamrffrecognizer_m_mk "/pvmi/recognizer/plugins/pvamrffrecognizer/build/make"
#define pvasflocalpbreginterface_m_lib ""
#define colorconvert_m_lib "-lcolorconvert"
#define pvprotocolengine_asfstreaming_so_name ""
#define omx_baseclass_y_lib ""
#define pvrmffinterface_m_lib ""
#define wmvdecoder_imp_m_lib ""
#define pvmtp_engine_y_mk ""
#define LIBDIR_video_shared "/codecs_v2/video/avc_h264/common/build/make /codecs_v2/video/avc_h264/dec/build/make   /codecs_v2/video/m4v_h263/dec/build/make  /codecs_v2/video/m4v_h263/enc/build/make /codecs_v2/video/avc_h264/enc/build/make"
#define mtpconfiginterface_m_lib ""
#define pvasfff_m_mk ""
#define pvaudiotrackmio_m_lib ""
#define DYNAMIC_LOAD_OMX_AAC_COMPONENT 1
#define rvdecoder_imp_m_mk ""
#define pvdivxdrmplugin_y_lib ""
#define pvflvffparsernode_y_lib ""
#define pvgendatastruct_y_mk ""
#define pvmiofileoutput_y_lib ""
#define AGGREGATE_LIBDIRS_pvrtspunicastwithpvr_streaming " "
#define pvwmdrmmd_so_name ""
#define pvdownloadreginterface_m_lib "-lpvdownloadreginterface"
#define LIBS_static " -lunit_test -lunit_test_utils                                                             -lpvavifileparser                                                   -lpvmioaviwavfileinput                                                                                   "
#define REGISTER_OMX_M4V_COMPONENT 1
#define MODS_opencore_net_support "-lopencore_common"
#define pvcrypto_y_mk ""
#define AGGREGATE_LIBDIRS_pvrtsptunicast_streaming "/modules/linux_rtsp/smplugins/tunneling/core/build/make /nodes/streaming/streamingmanager/plugins/rtsptunicast/build/make"
#define omx_aacenc_component_imp_m_mk ""
#define asfrecognizer_utility_y_lib ""
#define pv_aac_enc_m_mk ""
#define pvmp3ff_m_mk "/fileformats/mp3/parser/build/make"
#define pvplsffrecognizer_m_mk "/pvmi/recognizer/plugins/pvplsffrecognizer/build/make"
#define pvomx_proxy_y_lib ""
#define pvmiofileinput_m_mk "/pvmi/media_io/pvmi_mio_fileinput/build/make_pvauthor"
#define pvfasttrack_download_aggregate_libtype "static"
#define oscl_y_lib ""
#define mtpconfiginterface_m_mk ""
#define MODS_omx_radec_sharedlibrary "-lomx_sharedlibrary -lopencore_common -lopencore_player -lpvrealsupportcommon"
#define pvrmffrecognizer_utility_y_mk ""
#define omx_rv_component_y_mk ""
#define wavparser_m_mk "/fileformats/audioparser/wav/build/make"
#define LIBS_protocols_static "                  "
#define MODS_pvmp4eu "-lopencore_common -lopencore_player -lopencore_author"
#define LIBDIR_audio_shared "     /codecs_v2/audio/aac/dec/build/make  /codecs_v2/audio/gsm_amr/amr_nb/common/build/make /codecs_v2/audio/gsm_amr/amr_wb/dec/build/make /codecs_v2/audio/gsm_amr/amr_nb/dec/build/make /codecs_v2/audio/mp3/dec/build/make   /codecs_v2/audio/gsm_amr/common/dec/build/make /codecs_v2/audio/gsm_amr/amr_nb/enc/build/make "
#define pvmtpdrmmanagerplugin_so_name ""
#define pvdivxdrm_link_type "loaded"
#define pvsdpparser_opencore_m_lib "-lpvsdpparser"
#define protocolenginenode_m_lib "-lprotocolenginenode_base -lprotocolenginenode_common -lprotocolenginenode_download_common -lprotocolenginenode_pdl -lprotocolenginenode_ps -lprotocolenginenode_shoutcast"
#define pvrmffparser_node_aggregate_libtype "static"
#define BUILD_SHOUTCAST_PLUGIN 1
#define pvdb_recovery_utility_m_mk ""
#define pvomxaudiodecnode_m_lib "-lpvomxaudiodecnode"
#define pv324m_y_lib ""
#define pvflv_recognizer_so_name ""
#define BUILD_WOW_HD_AUDIO 0
#define pvsocketnode_y_lib ""
#define unit_test_y_mk "/oscl/unit_test/build/make"
#define AGGREGATE_LIBDIRS_pv "/oscl    /codecs_v2/audio/aac/dec/build/make /codecs_v2/audio/mp3/dec/build/make   /codecs_v2/audio/gsm_amr/amr_nb/dec/build/make /codecs_v2/audio/gsm_amr/amr_nb/enc/build/make /codecs_v2/audio/gsm_amr/amr_nb/common/build/make /codecs_v2/audio/gsm_amr/amr_wb/dec/build/make /codecs_v2/video/avc_h264/dec/build/make  /codecs_v2/video/avc_h264/common/build/make /codecs_v2/video/avc_h264/enc/build/make  /codecs_v2/video/m4v_h263/dec/build/make /codecs_v2/video/m4v_h263/enc/build/make   /codecs_v2/audio/aac/dec/util/getactualaacconfig/build/make  /codecs_v2/utilities/colorconvert/build/make /codecs_v2/utilities/m4v_config_parser/build/make /codecs_v2/utilities/pv_config_parser/build/make /codecs_v2/omx/omx_h264/build/make_multithreaded /codecs_v2/omx/omx_m4v/build/make_multithreaded   /codecs_v2/omx/omx_aac/build/make_multithreaded /codecs_v2/omx/omx_amr/build/make_multithreaded /codecs_v2/omx/omx_mp3/build/make_multithreaded   /codecs_v2/omx/omx_common/build/make_multithreaded /codecs_v2/omx/omx_queue/build/make /codecs_v2/omx/omx_proxy/build/make /codecs_v2/omx/omx_baseclass/build/make /codecs_v2/omx/omx_mastercore/build/make_multithreaded /codecs_v2/omx/omx_sharedlibrary/interface/build/make /baselibs/threadsafe_callback_ao/build/make /baselibs/media_data_structures/build/make /baselibs/pv_mime_utils/build/make /baselibs/gen_data_structures/build/make /pvmi/pvmf/build/make /pvmi/content_policy_manager/build/make /pvmi/media_io/pvmiofileoutput/build/make /fileformats/common/parser/build/make /fileformats/id3parcom/build/make  /fileformats/mp4/parser/build_opencore/make /fileformats/mp4/parser/utils/mp4recognizer/build/make    /fileformats/mp4/composer/build_opencore/make  /nodes/pvmp4ffcomposernode/build_opencore/make  /fileformats/pvx/parser/build/make /nodes/pvmediainputnode/build/make_pvauthor /nodes/pvmediaoutputnode/build/make /nodes/pvfileoutputnode/build/make /fileformats/rawgsmamr/parser/build/make /nodes/pvamrffparsernode/build/make /pvmi/recognizer/plugins/pvamrffrecognizer/build/make /fileformats/rawaac/parser/build/make /nodes/pvaacffparsernode/build/make /pvmi/recognizer/plugins/pvaacffrecognizer/build/make /fileformats/mp3/parser/build/make /nodes/pvmp3ffparsernode/build/make /pvmi/recognizer/plugins/pvmp3ffrecognizer/build/make   /nodes/pvcommonparsernode/build/make /fileformats/audioparser/common/build/make /fileformats/audioparser/amr/build/make /fileformats/audioparser/wav/build/make /nodes/pvomxvideodecnode/build/make /nodes/pvomxaudiodecnode/build/make /nodes/pvomxbasedecnode/build/make  /nodes/pvwavffparsernode/build/make /pvmi/recognizer/plugins/pvwavffrecognizer/build/make     /pvmi/recognizer/build/make /pvmi/media_io/pvmi_mio_fileinput/build/make_pvauthor  /engines/adapters/player/framemetadatautility/build/make /engines/player/build/make /engines/author/build/make /engines/2way/sample_app/pv2waysample/build/make /protocols/systems/3g-324m_pvterminal/build/make/ /engines/2way/build/make /nodes/pvclientserversocketnode/build/make  /baselibs/thread_messaging/build/make /protocols/rtp_payload_parser/util/build/latmparser/make  /fileformats/scsp/build/make"
#define PV_ONE_SEGMENT_BROADCAST 0
#define getactualaacconfig_y_mk ""
#define AGGREGATE_LIBDIRS_pvmtp ""
#define protocolenginenode_base_mk "/nodes/pvprotocolenginenode/base/build/make"
#define pvmf_y_lib ""
#define pv_config_parser_y_lib ""
#define opencore_2way_aggregate_libtype "shared"
#define pvpvrcommonimp_m_lib ""
#define m4v_config_m_lib "-lm4v_config"
#define pvaacffrecognizer_m_lib "-lpvaacffrecognizer"
#define cpm_y_mk ""
#define MODS_pvrtsptunicast_streamingreg "-lopencore_common -lopencore_streaming"
#define pvrbroadcastplugininterface_m_lib ""
#define pvmtpdrmmanagerplugin_link_type "loaded"
#define wmvdecoder_y_mk ""
#define AGGREGATE_LIBDIRS_omx_aacdec_sharedlibrary "/codecs_v2/omx/omx_aac/build/make_multithreaded /codecs_v2/audio/aac/dec/build/make"
#define pvsmfspcommonimp_y_lib ""
#define opencore_mp4localreg_so_name "opencore_mp4localreg"
#define pvcommonparsernode_y_mk ""
#define pvmtpdrmmanagerplugin_m_lib ""
#define flvrecognizer_utility_y_mk ""
#define omx_radec_sharedlibrary_so_name ""
#define pv_avc_mp_decoder_m_lib ""
#define pvomxvideodecnode_m_mk "/nodes/pvomxvideodecnode/build/make"
#define pvmp4ffcomposernodeopencore_m_mk "/nodes/pvmp4ffcomposernode/build_opencore/make"
#define pvrtsp_cli_eng_playlist_node_m_mk ""
#define pvomxaudiodecnode_y_mk ""
#define pvra8decoder_y_mk ""
#define AGGREGATE_LIBDIRS_pvflvparser_node "  "
#define AGGREGATE_LIBDIRS_opencore_rtsp "/protocols/rtsp_parcom/build/make /protocols/rtsp_client_engine/build/make_segments /protocols/rtp_payload_parser/build/make /nodes/streaming/jitterbuffernode/jitterbuffer/rtp/build/make"
#define pvflvff_m_mk ""
#define m4v_config_y_mk ""
#define pvthreadmessaging_y_lib ""
#define pvthreadmessaging_m_mk "/baselibs/thread_messaging/build/make"
#define pvjitterbuffercommon_m_lib "-lpvjitterbuffer"
#define LIBS_tools_v2_shared "-lpvsminterface -lpvsmreginterface   -lpvrtspsmplugininterface -lpvrtspsmpluginreginterface -lpvrtsptsmplugininterface -lpvrtsptsmpluginreginterface         -lpvdownloadinterface -lpvdownloadreginterface -lpvmp4interface -lpvmp4reginterface         -lpvoma1passthruplugininterface           "
#define LIBS_pvmi_shared "-lcpm -lpvoma1passthruplugin     -lpvmiofileoutput -lpvmiofileinput  -lpvmio_comm_loopback -lpvmfrecognizer -lpvaacffrecognizer -lpvamrffrecognizer   -lpvmp3ffrecognizer -lpvmp4ffrecognizer  -lpvwavffrecognizer   -lpvplsffrecognizer   -lpvmf   "
#define pvcommsionode_m_mk "/nodes/pvcommsionode/build/make"
#define pvm4vencoder_imp_m_mk ""
#define g726decnode_m_lib ""
#define omx_mp3_component_imp_m_lib ""
#define pvstreamingmanagernode_m_mk "/nodes/streaming/streamingmanager/build/make"
#define pvplayreadyplugininterface_m_mk ""
#define mpeg2recognizer_utility_m_mk ""
#define DYNAMIC_LOAD_OMX_H263_COMPONENT 1
#define pvomxencnode_y_lib ""
#define smrtsptrmplugininterface_m_mk ""
#define pvmetadata_engine_y_mk ""
#define omx_wma_component_imp_m_lib ""
#define wavparser_y_lib ""
#define pvpvxparser_y_lib ""
#define pvra8decoder_y_lib ""
#define pvdbconfiginterface_m_lib ""
#define MODS_pvasflocalpbreg "-lopencore_common -lpvasfcommon"
#define pvrmffparsernode_m_lib ""
#define MODS_pvplayerservice ""
#define pv_divxfile_parser_m_mk ""
#define LIBS_media_io_static "  -lpvmioaviwavfileinput "
#define pv_amr_nb_common_imp_lib_m_mk ""
#define MODS_pvrmffparser_node "-lpvrmff_recognizer -lopencore_player -lopencore_common -lpvrealsupportcommon"
#define pvmp4eu_m_mk ""
#define pvrmff_y_lib ""
#define pvdtcp_mbds_y_lib ""
#define pvwmdrmoemsettings_link_type "loaded"
#define pvstillimagenode_y_lib ""
#define USE_OMX_ENC_NODE 1
#define pvrtsptwithrealfsp_m_lib ""
#define mp4recognizer_utility_y_lib ""
#define asf_payload_parser_y_mk ""
#define pvm4vencoder_m_lib "-lpvm4vencoder"
#define LIBS_codecs_utilities_shared "-lm4v_config -lpv_config_parser -lcolorconvert"
#define opencore_2way_so_name "opencore_2way"
#define AGGREGATE_LIBDIRS_pvsqlite ""
#define pv2waysample_y_mk ""
#define omx_avcdec_sharedlibrary_aggregate_libtype "shared"
#define AGGREGATE_LIBDIRS_omx_wmadec_sharedlibrary "  "
#define omx_wmvdec_sharedlibrary_so_name ""
#define pvdtcpplugin_y_mk ""
#define pvmshttp_streaming_so_name ""
#define AGGREGATE_LIBDIRS_omx_amrdec_sharedlibrary "/codecs_v2/omx/omx_amr/build/make_multithreaded /codecs_v2/audio/gsm_amr/amr_nb/dec/build/make /codecs_v2/audio/gsm_amr/amr_wb/dec/build/make"
#define getactualaacconfig_m_lib "-lgetactualaacconfig"
#define MODS_pvprotocolengine_asfstreaming "-lopencore_net_support -lopencore_common -lpvasfcommon"
#define pvprotocolengine_asfstreaming_link_type "loaded"
#define omx_amrenc_component_y_lib ""
#define MODS_pvrealsupportcommon "-lopencore_common"
#define AGGREGATE_LIBDIRS_pvrtsptunicastforrm_streamingreg ""
#define pvaacffparsernode_m_mk "/nodes/pvaacffparsernode/build/make"
#define pvm4vencoder_imp_m_lib ""
#define rtppayloadparser_y_lib ""
#define pvrmffparser_y_lib ""
#define wmvdecoder_m_mk ""
#define packetsources_default_m_lib ""
#define omx_amrenc_component_imp_m_lib ""
#define pvaacffrecognizer_y_mk ""
#define DYNAMIC_LOAD_OMX_AVC_COMPONENT 1
#define REGISTER_OMX_RA_COMPONENT 0
#define LIBS_omxdecimp_static ""
#define pvmtpip_aggregate_libtype "static"
#define pv_smooth_streaming_m_lib ""
#define WMA_BUILD_CFG_LSL_ENABLED 0
#define pv_aac_enc_imp_m_lib ""
#define LIBDIR_nodes_static "                                                "
#define smrtspunicastplugininterface_m_mk "/modules/linux_rtsp/smplugins/unicast/core/build/make"
#define pvmshttp_streaming_aggregate_libtype "static"
#define PV_MULTICHANNEL_FRIENDLY 0
#define asfrecognizer_utility_m_mk ""
#define pvrmffparsernode_m_mk ""
#define realaudio_deinterleaver_m_mk ""
#define LIBDIR_baselibs_static "        "
#define pvwav_m_lib "-lpvwav"
#define pvmp4decoder_imp_m_lib ""
#define pv_rtsp_parcom_y_lib ""
#define LIBDIR_static " /oscl/unit_test/build/make /oscl/unit_test_utils/build/make                                                           /fileformats/avi/parser/build/make                                                      /pvmi/media_io/pvmi_mio_avi_wav_fileinput/build/make                                                                                     "
#define pvmp4decoder_y_mk ""
#define omx_mastercore_m_lib "-lomx_mastercore_lib"
#define omx_m4vdec_sharedlibrary_aggregate_libtype "shared"
#define pv_config_parser_y_mk ""
#define MODS_pvmtpconfigclass "-lopencore_common"
#define LIBS_oscl_static " -lunit_test -lunit_test_utils"
#define pvfileoutputnode_m_mk "/nodes/pvfileoutputnode/build/make"
#define wmadecoder_imp_m_lib ""
#define g726decnode_y_mk ""
#define oscl_m_mk "/oscl"
#define pvpvxparser_m_lib "-lpvpvxparser"
#define rtspbasedpluginselected 1
#define pv_http_retriever_y_mk ""
#define MODS_pvrtsptunicastforrm_streaming "-lopencore_net_support -lopencore_player -lopencore_common -lpvrtsptunicast_streaming -lopencore_rtsp -lopencore_streaming -lpvwmdrmmd -lpvrealsupportcommon"
#define pvfileplaybackwithpvrfsp_m_lib ""
#define pvdivxdrm_y_lib ""
#define pvmtpconfigclass_link_type "loaded"
#define omx_m4venc_component_imp_m_lib ""
#define pvrmff_recognizer_so_name ""
#define pvdb_recovery_utility_y_lib ""
#define pvmetadata_engine_y_lib ""
#define pvamrffrecognizer_y_lib ""
#define LIBS_omxjointimp_shared "-lomx_mastercore_lib"
#define pvmediaoutputnode_m_mk "/nodes/pvmediaoutputnode/build/make"
#define pvm4vencoder_y_mk ""
#define pvbroadcastwithpvrfsp_m_mk ""
#define LIBDIR_omxjoint_shared "/codecs_v2/omx/omx_common/build/make_multithreaded /codecs_v2/omx/omx_queue/build/make /codecs_v2/omx/omx_proxy/build/make /codecs_v2/omx/omx_baseclass/build/make /codecs_v2/omx/omx_mastercore/build/make_multithreaded /codecs_v2/omx/omx_sharedlibrary/interface/build/make"
#define pvrmff_recognizer_link_type "loaded"
#define REGISTER_OMX_M4VENC_COMPONENT 1
#define AGGREGATE_LIBDIRS_pvplayready "  "
#define pvpvrff_y_mk ""
#define pvpvrnode_y_mk ""
#define omx_baseclass_y_mk ""
#define AGGREGATE_LIBDIRS_pvfasttrack_downloadreg ""
#define pvrtspunicastwithpvrfsp_m_lib ""
#define pvamrwbdecoder_m_mk "/codecs_v2/audio/gsm_amr/amr_wb/dec/build/make"
#define pvplayready_so_name ""
#define pvplayer_engine_y_mk ""
#define pvamrwbdecoder_y_lib ""
#define pvsqlite_m_lib ""
#define LIBDIR_tools_v2_shared "/modules/linux_rtsp/core/build/make /modules/linux_rtsp/node_registry/build/make   /modules/linux_rtsp/smplugins/unicast/core/build/make /modules/linux_rtsp/smplugins/unicast/registry/build/make /modules/linux_rtsp/smplugins/tunneling/core/build/make /modules/linux_rtsp/smplugins/tunneling/registry/build/make         /modules/linux_download/core/build/make /modules/linux_download/node_registry/build/make /modules/linux_mp4/core/build/make /modules/linux_mp4/node_registry/build/make         /modules/cpm_oma1_passthru/build/make           "
#define wmadecoder_y_mk ""
#define WMA_AUDIO_SUPPORT_ENABLED 1
#define pvmtpip_engine_m_lib ""
#define pvrtsptunicastfsp_y_lib ""
#define protocolenginenode_m_mk "/nodes/pvprotocolenginenode/base/build/make /nodes/pvprotocolenginenode/protocol_common/build/make /nodes/pvprotocolenginenode/download_protocols/common/build/make /nodes/pvprotocolenginenode/download_protocols/progressive_download/build/make /nodes/pvprotocolenginenode/download_protocols/progressive_streaming/build/make /nodes/pvprotocolenginenode/download_protocols/shoutcast/build/make"
#define pvmedialayernode_y_lib ""
#define pvg726decoder_m_mk ""
#define pvdivxffrecognizer_m_mk ""
#define pvflvffparsernode_m_lib ""
#define pvmp4ffcomposernodeopencore_y_lib ""
#define scsp_y_mk ""
#define pvjitterbufferrtp_m_mk "/nodes/streaming/jitterbuffernode/jitterbuffer/rtp/build/make"
#define pvplayreadyutility_m_mk ""
#define pventropysrc_y_lib ""
#define pvdecoder_gsmamr_y_mk ""
#define pvplayerservice_so_name ""
#define pvmp4ffcomposernode_m_lib ""
#define pvplayready_aggregate_libtype "static"
#define pvloopbacknode_y_mk ""
#define pvfileplaybackwithpvr_streamingreg_so_name ""
#define AGGREGATE_LIBDIRS_pvdivxparser_node "  "
#define pvdivxoemsettings_link_type "loaded"
#define pvrmffparser_node_link_type "loaded"
#define pvgsmamrparser_m_lib "-lpvgsmamrparser"
#define omx_mp3_component_m_mk "/codecs_v2/omx/omx_mp3/build/make_multithreaded"
#define MODS_pvflv_recognizer "-lopencore_common"
#define pv_divxfile_parser_m_lib ""
#define omx_mp3_component_m_lib "-lomx_mp3_component_lib"
#define pvaacparser_m_lib "-lpvaacparser"
#define pvwavffparsernode_m_mk "/nodes/pvwavffparsernode/build/make"
#define BUILD_STATIC_FILEPLAYBACK_PVR 0
#define pvdivxoemsettings_m_lib ""
#define LIBS_omxencimp_static ""
#define MODS_opencore_2way "-lopencore_common"
#define pv_aggregate_libtype "static"
#define rvdecoder_m_lib ""
#define LIBDIR_fileformats_shared "/fileformats/common/parser/build/make /fileformats/id3parcom/build/make /fileformats/pvx/parser/build/make /fileformats/wav/parser/build/make    /fileformats/mp3/parser/build/make /fileformats/rawaac/parser/build/make /fileformats/rawgsmamr/parser/build/make    /fileformats/mp4/parser/utils/mp4recognizer/build/make /fileformats/mp4/parser/build_opencore/make  /fileformats/mp4/composer/build_opencore/make    /fileformats/scsp/build/make       /fileformats/audioparser/common/build/make /fileformats/audioparser/amr/build/make /fileformats/audioparser/wav/build/make"
#define omx_queue_m_mk "/codecs_v2/omx/omx_queue/build/make"
#define omx_wmadec_sharedlibrary_aggregate_libtype "static"
#define protocolenginenode_ps_mk "/nodes/pvprotocolenginenode/download_protocols/progressive_streaming/build/make"
#define pvplayreadyutility_m_lib ""
#define pv_http_parcom_m_mk "/protocols/http_parcom/build/make"
#define pvmshttp_streamingreg_link_type "loaded"
#define LIBDIR_packetsources_shared ""
#define pvrmffparser_node_so_name ""
#define LIBDIR_omxjoint_static "   "
#define pv_amr_nb_common_lib_m_lib "-lpv_amr_nb_common_lib"
#define pvmiofileoutput_y_mk ""
#define MODS_opencore_mp4local "-lopencore_common -lopencore_player"
#define AGGREGATE_LIBDIRS_pvmshttp_streamingreg ""
#define pvrtspunicast_streamingreg_link_type "loaded"
#define pvmp3ff_y_lib ""
#define pvrrtspunicastpluginregpopulator_m_lib ""
#define pvmiofileinput_y_lib ""
#define LIBS_fileformats_static "     -lpvavifileparser                       "
#define divxrecognizer_utility_y_mk ""
#define pvmp3ffparsernode_y_mk ""
#define pvavch264enc_y_mk ""
#define pvg726decoder_m_lib ""
#define AGGREGATE_LIBDIRS_pvrmffparser_node "  "
#define LIBS_recognizer_shared "-lpvmfrecognizer -lpvaacffrecognizer -lpvamrffrecognizer   -lpvmp3ffrecognizer -lpvmp4ffrecognizer  -lpvwavffrecognizer   -lpvplsffrecognizer "
#define pvstreamingmanagernode_y_lib ""
#define pvdivxdrm_oem_settings_y_mk ""
#define pvrtsptunicastforrm_streaming_so_name ""
#define unit_test_utils_y_lib "-lunit_test_utils"
#define pvsqlite_y_lib ""
#define AGGREGATE_LIBDIRS_pvdivxdrm "  "
#define pvmtpdrmmanagerplugin_m_mk ""
#define opencore_player_so_name "opencore_player"
#define omx_aacenc_sharedlibrary_so_name ""
#define rvdecoder_y_mk ""
#define colorconvert_y_mk ""
#define pvflvreginterface_m_lib ""
#define pv_m3u_parser_m_lib ""
#define pv_m3u_parser_m_mk ""
#define pvoma1ffrecognizer_m_mk ""
#define packetsources_default_y_lib ""
#define DYNAMIC_LOAD_OMX_AACENC_COMPONENT 0
#define pvplayer_engine_m_lib "-lpvplayer_engine"
#define opencore_rtsp_aggregate_libtype "shared"
#define pvrmffrecognizer_utility_m_lib ""
#define pvdivxffparsernode_m_mk ""
#define pv_avc_mp_decoder_imp_m_lib ""
#define packetsources_default_y_mk ""
#define omx_amrenc_sharedlibrary_so_name "omx_amrenc_sharedlibrary"
#define pv2wayengine_y_mk ""
#define pvmpeg2ff_m_mk ""
#define pvrtspunicast_streaming_so_name "pvrtspunicast_streaming"
#define AGGREGATE_LIBDIRS_omx_avcdec_sharedlibrary "/codecs_v2/omx/omx_h264/build/make_multithreaded /codecs_v2/video/avc_h264/dec/build/make "
#define pvmp4ffopencore_y_lib ""
#define omx_m4venc_component_y_lib ""
#define pvrtsptunicast_streaming_link_type "loaded"
#define pvpvrnode_m_lib ""
#define pvpvrff_m_lib ""
#define pvframemetadatautility_y_lib ""
#define omx_avcenc_component_imp_m_mk ""
#define omx_amr_component_y_mk ""
#define divxrecognizer_utility_m_mk ""
#define pvavch264enc_y_lib ""
#define pvclientserversocketnode_m_mk "/nodes/pvclientserversocketnode/build/make"
#define omx_rv_component_imp_m_lib ""
#define LIBDIR_nodes_shared "/nodes/pvfileoutputnode/build/make /nodes/pvmediaoutputnode/build/make /nodes/pvsocketnode/build/make /nodes/pvprotocolenginenode/base/build/make /nodes/pvprotocolenginenode/protocol_common/build/make /nodes/pvprotocolenginenode/download_protocols/common/build/make /nodes/pvprotocolenginenode/download_protocols/progressive_download/build/make /nodes/pvprotocolenginenode/download_protocols/progressive_streaming/build/make /nodes/pvprotocolenginenode/download_protocols/shoutcast/build/make /nodes/pvwavffparsernode/build/make /nodes/pvomxencnode/build/make /nodes/pvomxbasedecnode/build/make /nodes/pvomxaudiodecnode/build/make /nodes/pvomxvideodecnode/build/make /nodes/pvaacffparsernode/build/make /nodes/pvamrffparsernode/build/make  /nodes/pvmp3ffparsernode/build/make  /nodes/pvmp4ffparsernode/build_opencore/make   /nodes/common/build/make /nodes/pvmediainputnode/build/make_pvauthor  /nodes/pvmp4ffcomposernode/build_opencore/make   /nodes/pvdownloadmanagernode/build/make  /nodes/streaming/streamingmanager/plugins/rtspunicast/build/make /nodes/streaming/streamingmanager/plugins/rtsptunicast/build/make     /nodes/streaming/streamingmanager/plugins/common/build/make  /nodes/streaming/streamingmanager/build/make   /modules/linux_rtsp/smplugins/unicast/core/build/make /modules/linux_rtsp/smplugins/unicast/registry/build/make /modules/linux_rtsp/smplugins/tunneling/core/build/make /modules/linux_rtsp/smplugins/tunneling/registry/build/make          /nodes/streaming/jitterbuffernode/jitterbuffer/common/build/make /nodes/streaming/jitterbuffernode/jitterbuffer/rtp/build/make  /nodes/streaming/jitterbuffernode/build/make /nodes/pvcommsionode/build/make /nodes/pvclientserversocketnode/build/make /nodes/pvloopbacknode/build/make      /nodes/pvcommonparsernode/build/make"
#define pvasfff_y_mk ""
#define getactualaacconfig_for_static_m_lib ""
#define pvmp3ffrecognizer_y_lib ""
#define AGGREGATE_LIBDIRS_pvfasttrack_download " "
#define AGGREGATE_LIBDIRS_pvdivx_recognizer "  "
#define pvprotocolenginewmhttpstreamingpluginreginterface_m_mk ""
#define pvclientserversocketnode_m_lib "-lpvclientserversocketnode"
#define pvsqlite_m_mk ""
#define DYNAMIC_LOAD_OMX_MP3_COMPONENT 1
#define pvavcdecoder_y_mk ""
#define pvrtsptunicastforrm_streamingreg_so_name ""
#define getactualaacconfig_y_lib ""
#define pvoma1passthruplugininterface_m_lib "-lpvoma1passthruplugininterface"
#define wma_common_hdrs_y_mk ""
#define omx_amrenc_component_y_mk ""
#define LIBS_omxjoint_static "   "
#define pvmtpconfigclass_so_name ""
#define pvmio_comm_loopback_y_mk ""
#define pvmediaoutputnode_m_lib "-lpvmediaoutputnode"
#define BUILD_STATIC_RTSPUNICAST 0
#define LIBDIR_audio_static "               "
#define pvra8decoder_m_lib ""
#define pvdbconfigclass_so_name ""
#define omx_rv_component_y_lib ""
#define pvmtpip_engine_m_mk ""
#define pvlatmpayloadparser_y_mk ""
#define omx_m4v_component_m_mk "/codecs_v2/omx/omx_m4v/build/make_multithreaded"
#define packetsources_default_plugins " "
#define omx_queue_y_lib ""
#define protocolenginenode_pdl_lib "-lprotocolenginenode_pdl"
#define pvrfileplaybackpluginregpopulator_m_lib ""
#define pvpvr_m_lib ""
#define AGGREGATE_LIBDIRS_pvmtpdrmmanagerplugin ""
#define pvmp4ffcomposernode_y_lib ""
#define pvasxparser_y_mk ""
#define MODS_pvdtcp_mbds "-lopencore_download -lopencore_common"
#define pvmp3ffparsernode_m_mk "/nodes/pvmp3ffparsernode/build/make"
#define pvdivxffrecognizer_y_lib ""
#define pvmp4eu_y_mk ""
#define pvdownloadmanagernode_y_mk ""
#define omx_wmvdec_sharedlibrary_aggregate_libtype "static"
#define omx_sharedlibrary_so_name "omx_sharedlibrary"
#define omx_avc_component_imp_m_mk ""
#define unit_test_m_lib ""
#define MODS_pvasfcommon "-lopencore_common"
#define pvid3parcom_y_mk ""
#define pventropysrc_y_mk ""
#define pvrtsptunicastforrm_streaming_aggregate_libtype "static"
#define opencore_streaming_aggregate_libtype "shared"
#define pvomx_proxy_y_mk ""
#define pvdivxparser_node_link_type "loaded"
#define pvsmreginterface_m_lib "-lpvsmreginterface"
#define DYNAMIC_LOAD_OMX_RA_COMPONENT 0
#define pvmediainputnode_m_mk "/nodes/pvmediainputnode/build/make_pvauthor"
#define pvoma1lockstream_m_lib ""
#define pvcommsionode_y_lib ""
#define pv_avc_common_lib_y_lib ""
#define pvomxaudiodecnode_y_lib ""
#define pvflvffrecognizer_m_lib ""
#define omx_wma_component_y_mk ""
#define pv_srs_wowhd_y_mk ""
#define omx_baseclass_m_lib "-lomx_baseclass_lib"
#define ss_or_als 0
#define pvoma1ffrecognizer_y_mk ""
#define pvoma1passthruplugin_m_lib "-lpvoma1passthruplugin"
#define protocolenginenode_download_common_lib "-lprotocolenginenode_download_common"
#define pvwav_y_mk ""
#define pvwav_y_lib ""
#define pv_aac_enc_imp_m_mk ""
#define opencore_mp4localreg_aggregate_libtype "shared"
#define wmavoicedecoder_m_mk ""
#define pvmfrecognizer_y_mk ""
#define pvdbconfiginterface_m_mk ""
#define pvsdpparser_opencore_y_lib ""
#define protocolenginenode_y_lib ""
#define omx_m4venc_sharedlibrary_so_name "omx_m4venc_sharedlibrary"
#define pvmtp_usb_transport_m_mk ""
#define pvfileplaybackwithpvrfsp_y_mk ""
#define pv2waysample_m_lib "-lpv2waysample"
#define pvgeneraltools_m_mk "/protocols/systems/tools/general/build/make"
#define pv_aac_dec_m_mk "/codecs_v2/audio/aac/dec/build/make"
#define omx_aac_component_imp_m_mk ""
#define AGGREGATE_LIBDIRS_pvmshttp_streaming "    "
#define pvamrwbdecoder_m_lib "-lpvamrwbdecoder"
#define pv_http_parcom_y_lib ""
#define LIBS_engines_shared "-lpvplayer_engine -lpvauthorengine -lpv2wayengine -lpv2waysample -lpvframemetadatautility -lpvmetadata_engine  "
#define omx_mp3dec_sharedlibrary_so_name "omx_mp3dec_sharedlibrary"
#define pvsmfspcommonimp_m_lib "-lpvsmfspcommon"
#define LIBDIR_video_static "       "
#define LIBDIR_omxenc_shared "/codecs_v2/omx/omx_amrenc/build/make_multithreaded /codecs_v2/omx/omx_m4venc/build/make_multithreaded /codecs_v2/omx/omx_h264enc/build/make_multithreaded "
#define opencore_net_support_so_name "opencore_net_support"
#define pvjitterbufferasf_m_mk ""
#define pvdivxdrmplugininterface_m_mk ""
#define LIBS_nodes_static "                                               "
#define pvfileoutputnode_m_lib "-lpvfileoutputnode"
#define MODS_pvfileplaybackwithpvr_streamingreg "-lopencore_common -lopencore_streaming"
#define pvomxvideodecnode_y_lib ""
#define AGGREGATE_LIBDIRS_pvdb_recovery_utility ""
#define AGGREGATE_LIBDIRS_opencore_author " /fileformats/mp4/composer/build_opencore/make  /nodes/pvmp4ffcomposernode/build_opencore/make /engines/author/build/make"
#define AGGREGATE_LIBDIRS_opencore_streamingreg "/modules/linux_rtsp/node_registry/build/make"
#define pvmtpip_engine_y_mk ""
#define MODS_omx_sharedlibrary "-lopencore_common"
#define pv_omx_interface_m_mk "/codecs_v2/omx/omx_sharedlibrary/interface/build/make"
#define pvavifileparser_y_lib "-lpvavifileparser"
#define pvrfileplaybackplugininterface_m_mk ""
#define pvoma1passthruplugininterface_m_mk "/modules/cpm_oma1_passthru/build/make"
#define audioparser_m_mk "/fileformats/audioparser/common/build/make"
#define protocolenginenode_ftdl_lib ""
#define LIBDIR_omxdec_shared "/codecs_v2/omx/omx_h264/build/make_multithreaded /codecs_v2/omx/omx_m4v/build/make_multithreaded   /codecs_v2/omx/omx_aac/build/make_multithreaded /codecs_v2/omx/omx_amr/build/make_multithreaded /codecs_v2/omx/omx_mp3/build/make_multithreaded  "
#define omx_aacenc_component_y_lib ""
#define BUILD_PROGRESSIVE_STREAMING_PLUGIN 1
#define pvfasttrack_download_so_name ""
#define MODS_pvpvrcommonimpl_streaming "-lopencore_net_support -lopencore_common -lopencore_rtsp -lopencore_streaming"
#define pvmp4decoder_imp_m_mk ""
#define omx_m4v_component_y_mk ""
#define rdt_parser_m_lib ""
#define pvprotocolenginewmhttpstreaminginterface_m_mk ""
#define pvprotocolengine_asfstreaming_aggregate_libtype "static"
#define pvdtcp_mbds_y_mk ""
#define pvloopbacknode_y_lib ""
#define realaudio_deinterleaver_m_lib ""
#define REGISTER_OMX_AMRENC_COMPONENT 1
#define LIBS_cpm_static "     "
#define pvrtsptunicastforrm_streamingreg_link_type "loaded"
#define rtprtcp_m_lib "-lrtprtcp"
#define pvdbmanager_m_lib ""
#define WMA_VOICE_SUPPORT_ENABLED 1
#define pvmpeg2ff_y_lib ""
#define pv_smooth_streaming_y_lib ""
#define omx_mastercore_y_mk ""
#define omx_mp3dec_sharedlibrary_aggregate_libtype "shared"
#define pvmp4ffcomposer_m_mk ""
#define pvasflocalpbreginterface_m_mk ""
#define pvasflocalpbinterface_m_lib ""
#define omx_avcenc_sharedlibrary_aggregate_libtype "shared"
#define pvdivx_recognizer_link_type "loaded"
#define AGGREGATE_LIBDIRS_pvrtspunicast_streamingreg "/modules/linux_rtsp/smplugins/unicast/registry/build/make"
#define pvasfffrecognizer_y_mk ""
#define opencore_mp4local_aggregate_libtype "shared"
#define pvplayer_engine_m_mk "/engines/player/build/make"
#define LIBDIR_engines_static "        "
#define LIBDIR_pvmi_static "         /pvmi/media_io/pvmi_mio_avi_wav_fileinput/build/make                   "
#define pv324m_common_headers_y_mk ""
#define AGGREGATE_LIBDIRS_omx_sharedlibrary "/codecs_v2/omx/omx_common/build/make_multithreaded /codecs_v2/omx/omx_queue/build/make /codecs_v2/omx/omx_proxy/build/make /codecs_v2/omx/omx_baseclass/build/make /codecs_v2/omx/omx_sharedlibrary/interface/build/make /codecs_v2/video/avc_h264/common/build/make /codecs_v2/audio/gsm_amr/amr_nb/common/build/make"
#define pvwmdrmmd_y_mk ""
#define omx_ra_component_y_lib ""
#define pvrmffrecognizer_utility_y_lib ""
#define AGGREGATE_LIBDIRS_pvmtpconfigclass ""
#define pvrtppacketsourcenode_m_lib ""
#define pvrtspunicastfsp_y_lib ""
#define pvprotocolengine_asfstreamingreg_so_name ""
#define oscllib_mk "/oscl/oscl/oscllib/build/make"
#define asfrecognizer_utility_m_lib ""
#define threadsafe_callback_ao_y_lib ""
#define MODS_pvrtspbroadcastwithpvr_streamingreg "-lopencore_common -lopencore_streaming"
#define protocolenginenode_y_mk ""
#define REGISTER_OMX_H263ENC_COMPONENT 1
#define omx_baseclass_m_mk "/codecs_v2/omx/omx_baseclass/build/make"
#define pvdtcp_mbds_aggregate_libtype "static"
#define MODS_pviptransport "-lopencore_common"
#define AGGREGATE_LIBDIRS_omx_avcenc_sharedlibrary "/codecs_v2/omx/omx_h264enc/build/make_multithreaded /codecs_v2/video/avc_h264/enc/build/make"
#define pv_avc_mp_decoder_m_mk ""
#define pvrtsptunicastforrm_streaming_link_type "loaded"
#define LIBS_baselibs_static "        "
#define pvgendatastruct_y_lib ""
#define pv_config_parser_m_lib "-lpv_config_parser"
#define pvmpeg2local_so_name ""
#define pvmedialayernode_y_mk ""
#define pvdbmanager_y_mk ""
#define pvmtp_engine_y_lib ""
#define omx_avcenc_sharedlibrary_link_type "loaded"
#define opencore_common_so_name "opencore_common"
#define pv_divxfile_parser_y_mk ""
#define smmshttppluginregpopulator_m_lib ""
#define omx_mp3_component_y_mk ""
#define TARGET_aggregate "  opencore_common omx_sharedlibrary omx_avcdec_sharedlibrary omx_m4vdec_sharedlibrary   omx_aacdec_sharedlibrary omx_amrdec_sharedlibrary omx_mp3dec_sharedlibrary  omx_avcenc_sharedlibrary omx_m4venc_sharedlibrary omx_amrenc_sharedlibrary  opencore_net_support opencore_player opencore_downloadreg opencore_download opencore_streamingreg opencore_streaming          opencore_mp4localreg opencore_mp4local                pvoma1passthru        opencore_rtsp pvrtspunicast_streaming pvrtspunicast_streamingreg pvrtsptunicast_streaming pvrtsptunicast_streamingreg             opencore_author  opencore_2way opencore_pvme"
#define rdt_parser_y_mk ""
#define pvmpeg2localreg_aggregate_libtype "static"
#define REGISTER_OMX_AVCENC_COMPONENT 1
#define pvamrwbdecoder_y_mk ""
#define pvrmffparsernode_y_lib ""
#define pvmp4ffparsernodeopencore_y_mk ""
#define pvmp4ffopencore_y_mk ""
#define realmedia_payload_parser_m_mk ""
#define colorconvert_y_lib ""
#define pvmp4ffopencore_m_mk "/fileformats/mp4/parser/build_opencore/make"
#define pvencoder_gsmamr_m_lib "-lpvencoder_gsmamr"
#define pvra8decoder_m_mk ""
#define rfc_2429_mk "rfc_2429.mk"
#define pvdbconfigclass_aggregate_libtype "static"
#define omx_sharedlibrary_link_type "loaded"
#define MODS_pvrtspunicastwithpvr_streaming "-lopencore_net_support -lopencore_player -lopencore_common -lpvpvrcommonimpl_streaming -lopencore_rtsp -lopencore_streaming"
#define omx_aacdec_sharedlibrary_so_name "omx_aacdec_sharedlibrary"
#define pv_so_name ""
#define pvrmffrecognizer_m_mk ""
#define pvavch264enc_imp_m_mk ""
#define pvgeneraltools_m_lib "-lpvgeneraltools"
#define LIBS_omxjoint_shared "-lomx_common_lib -lomx_queue_lib -lpvomx_proxy_lib -lomx_baseclass_lib -lomx_mastercore_lib -lpv_omx_interface"
#define pviptransport_so_name ""
#define pvdivxoemsettings_m_mk ""
#define cpm_y_lib ""
#define pvplsffrecognizer_y_lib ""
#define MODS_pvrtsptunicastforrm_streamingreg "-lopencore_common -lopencore_streaming"
#define pvdivxdrmplugin_m_lib ""
#define omx_rvdec_sharedlibrary_link_type "loaded"
#define wmadecoder_imp_m_mk ""
#define MODS_opencore_downloadreg "-lopencore_common"
#define pvmp3ffrecognizer_m_mk "/pvmi/recognizer/plugins/pvmp3ffrecognizer/build/make"
#define omx_sharedlibrary_aggregate_libtype "shared"
#define protocolenginenode_asfstreaming_lib ""
#define pvmtp_engine_m_lib ""
#define pvdivxinterface_m_lib ""
#define MODS_omx_aacenc_sharedlibrary "-lomx_sharedlibrary -lopencore_common "
#define LIBS_omxjointimp_static ""
#define amrparser_m_mk "/fileformats/audioparser/amr/build/make"
#define pvdivx_recognizer_so_name ""
#define omx_m4v_component_imp_m_lib ""
#define pvmp4ffcomposeropencore_y_mk ""
#define pvrtspbroadcastwithpvr_streamingreg_aggregate_libtype "static"
#define pvdivxffparsernode_m_lib ""
#define AGGREGATE_LIBDIRS_omx_wmvdec_sharedlibrary " "
#define pv_srs_wowhd_y_lib ""
#define engines_common_headers_y_mk ""
#define pvmp4ffparsernode_y_lib ""
#define pvmioaviwavfileinput_m_mk ""
#define pvdb_so_name ""
#define pvmpeg2ffparsernode_y_mk ""
#define pvloopbacknode_m_lib "-lpvloopbacknode"
#define pvrbroadcastplugininterface_m_mk ""
#define pvmpeg2local_link_type "loaded"
#define protocolenginenode_segments_lib "-lprotocolenginenode_base -lprotocolenginenode_common -lprotocolenginenode_download_common -lprotocolenginenode_pdl -lprotocolenginenode_ps -lprotocolenginenode_shoutcast"
#define pvmf_m_lib "-lpvmf"
#define pvrealsupportcommon_aggregate_libtype "static"
#define pvdtcpplugin_m_lib ""
#define MODS_pvflvparser_node "-lpvflv_recognizer -lopencore_player -lopencore_common"
#define pvmp4eu_so_name ""
#define pvasfffparsernode_y_lib ""
#define LIBS_recognizer_static "            "
#define omx_rvdec_sharedlibrary_so_name ""
#define opencore_streaming_so_name "opencore_streaming"
#define pvmp4ffrecognizer_y_lib ""
#define flvrecognizer_utility_m_lib ""
#define LIBS_packetsources_shared ""
#define omx_rv_component_m_mk ""
#define pviptransport_y_mk ""
#define pvomxbasedecnode_m_mk "/nodes/pvomxbasedecnode/build/make"
#define pvmp3_m_mk "/codecs_v2/audio/mp3/dec/build/make"
#define LIBS_codecs_utilities_static "  "
#define LIBDIR_omxjointimp_shared "/codecs_v2/omx/omx_mastercore/build/make_multithreaded"
#define unit_test_y_lib "-lunit_test"
#define pvrbroadcastpluginregpopulator_m_lib ""
#define omx_ra_component_imp_m_mk ""
#define omx_m4venc_component_m_mk "/codecs_v2/omx/omx_m4venc/build/make_multithreaded"
#define MODS_opencore_streamingreg "-lopencore_common"
#define unit_test_m_mk ""
#define pvomxaudiodecnode_m_mk "/nodes/pvomxaudiodecnode/build/make"
#define pvprotocolenginefasttrackdownloadinterface_m_lib ""
#define MODS_pvrtspunicastwithpvr_streamingreg "-lopencore_common -lopencore_streaming"
#define omx_common_m_mk "/codecs_v2/omx/omx_common/build/make_multithreaded"
#define pvrtsptunicast_streamingreg_aggregate_libtype "shared"
#define REGISTER_OMX_AACENC_COMPONENT 0
#define pvdivxffparsernode_y_mk ""
#define pvmediadatastruct_m_mk "/baselibs/media_data_structures/build/make"
#define pvsminterface_m_lib "-lpvsminterface"
#define MODS_omx_amrenc_sharedlibrary "-lomx_sharedlibrary -lopencore_common "
#define pvmp4ffparsernode_m_lib ""
#define pvfileparserutils_y_lib ""
#define MODS_pvmtpip "-lopencore_common -lpvdb"
#define omx_avcdec_sharedlibrary_link_type "loaded"
#define MODS_opencore_common ""
#define pvflvff_m_lib ""
#define pvcrypto_m_lib ""
#define pvplayready_link_type "loaded"
#define pvdivxoemsettings_aggregate_libtype "static"
#define pvmpeg2local_aggregate_libtype "static"
#define pvmpeg2ffrecognizer_y_mk ""
#define pvrmff_m_mk ""
//
// That's all, folks!
