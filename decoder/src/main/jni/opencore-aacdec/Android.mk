#
# Compile OpenCORE aacdec - retrieved from Android's GIT repo.
# 

# Set up the PV variables
include $(PV_TOP)/Config.mk

my_LOCAL_PATH := $(call my-dir)
LOCAL_PATH := $(OPENCORE_DIR)
include $(CLEAR_VARS)

LOCAL_SRC_FILES := \
	src/analysis_sub_band.cpp \
 	src/apply_ms_synt.cpp \
 	src/apply_tns.cpp \
 	src/buf_getbits.cpp \
 	src/byte_align.cpp \
 	src/calc_auto_corr.cpp \
 	src/calc_gsfb_table.cpp \
 	src/calc_sbr_anafilterbank.cpp \
 	src/calc_sbr_envelope.cpp \
 	src/calc_sbr_synfilterbank.cpp \
 	src/check_crc.cpp \
 	src/dct16.cpp \
 	src/dct64.cpp \
 	src/decode_huff_cw_binary.cpp \
 	src/decode_noise_floorlevels.cpp \
 	src/decoder_aac.cpp \
 	src/deinterleave.cpp \
 	src/digit_reversal_tables.cpp \
 	src/dst16.cpp \
 	src/dst32.cpp \
 	src/dst8.cpp \
 	src/esc_iquant_scaling.cpp \
 	src/extractframeinfo.cpp \
 	src/fft_rx4_long.cpp \
 	src/fft_rx4_short.cpp \
 	src/fft_rx4_tables_fxp.cpp \
 	src/find_adts_syncword.cpp \
 	src/fwd_long_complex_rot.cpp \
 	src/fwd_short_complex_rot.cpp \
 	src/gen_rand_vector.cpp \
 	src/get_adif_header.cpp \
 	src/get_adts_header.cpp \
 	src/get_audio_specific_config.cpp \
 	src/get_cce.cpp \
 	src/get_dse.cpp \
 	src/get_ele_list.cpp \
 	src/get_ga_specific_config.cpp \
 	src/get_ics_info.cpp \
 	src/get_prog_config.cpp \
 	src/get_pulse_data.cpp \
 	src/get_sbr_bitstream.cpp \
 	src/get_sbr_startfreq.cpp \
 	src/get_sbr_stopfreq.cpp \
 	src/get_tns.cpp \
 	src/getfill.cpp \
 	src/getgroup.cpp \
 	src/getics.cpp \
 	src/getmask.cpp \
 	src/hcbtables_binary.cpp \
 	src/huffcb.cpp \
 	src/huffdecode.cpp \
 	src/hufffac.cpp \
 	src/huffspec_fxp.cpp \
 	src/idct16.cpp \
 	src/idct32.cpp \
 	src/idct8.cpp \
 	src/imdct_fxp.cpp \
 	src/infoinit.cpp \
 	src/init_sbr_dec.cpp \
 	src/intensity_right.cpp \
 	src/inv_long_complex_rot.cpp \
 	src/inv_short_complex_rot.cpp \
 	src/iquant_table.cpp \
 	src/long_term_prediction.cpp \
 	src/long_term_synthesis.cpp \
 	src/lt_decode.cpp \
 	src/mdct_fxp.cpp \
 	src/mdct_tables_fxp.cpp \
 	src/mdst.cpp \
 	src/mix_radix_fft.cpp \
 	src/ms_synt.cpp \
 	src/pns_corr.cpp \
 	src/pns_intensity_right.cpp \
 	src/pns_left.cpp \
 	src/ps_all_pass_filter_coeff.cpp \
 	src/ps_all_pass_fract_delay_filter.cpp \
 	src/ps_allocate_decoder.cpp \
 	src/ps_applied.cpp \
 	src/ps_bstr_decoding.cpp \
 	src/ps_channel_filtering.cpp \
 	src/ps_decode_bs_utils.cpp \
 	src/ps_decorrelate.cpp \
 	src/ps_fft_rx8.cpp \
 	src/ps_hybrid_analysis.cpp \
 	src/ps_hybrid_filter_bank_allocation.cpp \
 	src/ps_hybrid_synthesis.cpp \
 	src/ps_init_stereo_mixing.cpp \
 	src/ps_pwr_transient_detection.cpp \
 	src/ps_read_data.cpp \
 	src/ps_stereo_processing.cpp \
 	src/pulse_nc.cpp \
 	src/pv_div.cpp \
 	src/pv_log2.cpp \
 	src/pv_normalize.cpp \
 	src/pv_pow2.cpp \
 	src/pv_sine.cpp \
 	src/pv_sqrt.cpp \
 	src/pvmp4audiodecoderconfig.cpp \
 	src/pvmp4audiodecoderframe.cpp \
 	src/pvmp4audiodecodergetmemrequirements.cpp \
 	src/pvmp4audiodecoderinitlibrary.cpp \
 	src/pvmp4audiodecoderresetbuffer.cpp \
 	src/q_normalize.cpp \
 	src/qmf_filterbank_coeff.cpp \
 	src/sbr_aliasing_reduction.cpp \
 	src/sbr_applied.cpp \
 	src/sbr_code_book_envlevel.cpp \
 	src/sbr_crc_check.cpp \
 	src/sbr_create_limiter_bands.cpp \
 	src/sbr_dec.cpp \
 	src/sbr_decode_envelope.cpp \
 	src/sbr_decode_huff_cw.cpp \
 	src/sbr_downsample_lo_res.cpp \
 	src/sbr_envelope_calc_tbl.cpp \
 	src/sbr_envelope_unmapping.cpp \
 	src/sbr_extract_extended_data.cpp \
 	src/sbr_find_start_andstop_band.cpp \
 	src/sbr_generate_high_freq.cpp \
 	src/sbr_get_additional_data.cpp \
 	src/sbr_get_cpe.cpp \
 	src/sbr_get_dir_control_data.cpp \
 	src/sbr_get_envelope.cpp \
 	src/sbr_get_header_data.cpp \
 	src/sbr_get_noise_floor_data.cpp \
 	src/sbr_get_sce.cpp \
 	src/sbr_inv_filt_levelemphasis.cpp \
 	src/sbr_open.cpp \
 	src/sbr_read_data.cpp \
 	src/sbr_requantize_envelope_data.cpp \
 	src/sbr_reset_dec.cpp \
 	src/sbr_update_freq_scale.cpp \
 	src/set_mc_info.cpp \
 	src/sfb.cpp \
 	src/shellsort.cpp \
 	src/synthesis_sub_band.cpp \
 	src/tns_ar_filter.cpp \
 	src/tns_decode_coef.cpp \
 	src/tns_inv_filter.cpp \
 	src/trans4m_freq_2_time_fxp.cpp \
 	src/trans4m_time_2_freq_fxp.cpp \
 	src/unpack_idx.cpp \
 	src/window_tables_fxp.cpp \
 	src/pvmp4setaudioconfig.cpp
 	
#src/../util/getactualaacconfig/src/getactualaacconfig.cpp


PV_INCLUDES	:= $(PV_INCLUDES) \
				$(PV_TOP)/oscl/oscl/osclbase/src \
				$(PV_TOP)/oscl/oscl/osclmemory/src \
				$(PV_TOP)/oscl/oscl/osclerror/src

#$(PV_TOP)/codecs_v2/audio/aac/dec/util/getactualaacconfig/include


LOCAL_MODULE := libpv_aac_dec

# 2013-12-29: To compile for all platforms we must force
# evaluating of the PV Config.mk for each of them:
EXTERNAL_OPENCORE_CONFIG_ONCE :=
PV_CFLAGS :=

# Unfortunately PS causes crash for certain streams:
# fixed 2012-06-28
#LOCAL_CFLAGS := -DAAC_PLUS -DHQ_SBR $(PV_CFLAGS)
LOCAL_CFLAGS := -DAAC_PLUS -DHQ_SBR -DPARAMETRICSTEREO $(PV_CFLAGS)

ifeq ($(TARGET_ARCH),arm)
	LOCAL_ARM_MODE := arm
endif

LOCAL_STATIC_LIBRARIES := 

LOCAL_SHARED_LIBRARIES := 

LOCAL_C_INCLUDES := \
	$(PV_TOP)/codecs_v2/audio/aac/dec/src \
 	$(PV_TOP)/codecs_v2/audio/aac/dec/include \
 	$(PV_INCLUDES)

LOCAL_COPY_HEADERS_TO := $(PV_COPY_HEADERS_TO)

LOCAL_COPY_HEADERS := \
	include/decoder_aac.h \
 	include/e_tmp4audioobjecttype.h \
 	include/pv_audio_type_defs.h \
 	include/pvmp4audiodecoder_api.h

include $(BUILD_STATIC_LIBRARY)
