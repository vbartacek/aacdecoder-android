#
# Compile OpenCORE aacdec.
# 
# NDK scripts concatenates the LOCAL_PATH and LOCAL_SRC_FILES files,
# so we have to set LOCAL_PATH to ''
#
LOCAL_PATH :=
my_LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := opencore-aacdec
LOCAL_SRC_FILES := sbr_create_limiter_bands.c get_ga_specific_config.c idct32.c \
				tns_decode_coef.c digit_reversal_tables.c sbr_decode_huff_cw.c \
				sbr_inv_filt_levelemphasis.c pvmp4audiodecoderinitlibrary.c intensity_right.c \
				ps_all_pass_fract_delay_filter.c fwd_short_complex_rot.c pns_intensity_right.c \
				mix_radix_fft.c tns_ar_filter.c get_dse.c \
				inv_long_complex_rot.c q_normalize.c dct64.c \
				decode_noise_floorlevels.c hcbtables_binary.c extractframeinfo.c \
				check_crc.c esc_iquant_scaling.c getmask.c \
				sbr_get_additional_data.c get_adif_header.c pv_div.c \
				pvmp4setaudioconfig.c sbr_crc_check.c qmf_filterbank_coeff.c \
				getfill.c sbr_get_dir_control_data.c getactualaacconfig.c \
				sbr_extract_extended_data.c getics.c apply_ms_synt.c \
				pulse_nc.c sbr_requantize_envelope_data.c sbr_open.c \
				decode_huff_cw_binary.c gen_rand_vector.c calc_sbr_envelope.c \
				fft_rx4_short.c iquant_table.c long_term_synthesis.c \
				buf_getbits.c ps_decode_bs_utils.c deinterleave.c \
				sbr_get_envelope.c dst32.c get_pulse_data.c \
				sbr_get_cpe.c calc_sbr_synfilterbank.c fft_rx4_long.c \
				pv_sine.c pns_left.c ps_hybrid_filter_bank_allocation.c \
				window_tables_fxp.c get_tns.c dst16.c \
				sbr_downsample_lo_res.c synthesis_sub_band.c calc_auto_corr.c \
				long_term_prediction.c ms_synt.c inv_short_complex_rot.c \
				hufffac.c sbr_code_book_envlevel.c get_sbr_bitstream.c \
				get_adts_header.c sfb.c sbr_update_freq_scale.c \
				sbr_generate_high_freq.c sbr_get_sce.c huffdecode.c \
				pv_sqrt.c tns_inv_filter.c ps_hybrid_analysis.c \
				sbr_dec.c sbr_envelope_calc_tbl.c analysis_sub_band.c \
				ps_decorrelate.c pv_normalize.c dst8.c \
				find_adts_syncword.c ps_read_data.c pvmp4audiodecodergetmemrequirements.c \
				sbr_decode_envelope.c ps_init_stereo_mixing.c pv_pow2.c \
				fwd_long_complex_rot.c sbr_find_start_andstop_band.c lt_decode.c \
				get_ele_list.c unpack_idx.c get_sbr_startfreq.c \
				ps_hybrid_synthesis.c sbr_read_data.c ps_channel_filtering.c \
				mdct_fxp.c sbr_aliasing_reduction.c imdct_fxp.c \
				get_ics_info.c mdct_tables_fxp.c ps_stereo_processing.c \
				get_prog_config.c fft_rx4_tables_fxp.c trans4m_freq_2_time_fxp.c \
				apply_tns.c getgroup.c set_mc_info.c \
				sbr_reset_dec.c pvmp4audiodecoderresetbuffer.c ps_allocate_decoder.c \
				pvmp4audiodecoderframe.c pv_log2.c init_sbr_dec.c \
				infoinit.c mdst.c ps_pwr_transient_detection.c \
				sbr_get_header_data.c pns_corr.c huffcb.c \
				calc_sbr_anafilterbank.c dct16.c trans4m_time_2_freq_fxp.c \
				sbr_envelope_unmapping.c ps_bstr_decoding.c idct8.c \
				calc_gsfb_table.c get_audio_specific_config.c huffspec_fxp.c \
				ps_fft_rx8.c get_sbr_stopfreq.c sbr_applied.c \
				pvmp4audiodecoderconfig.c ps_applied.c ps_all_pass_filter_coeff.c \
				byte_align.c idct16.c sbr_get_noise_floor_data.c \
				shellsort.c

LOCAL_SRC_FILES := $(foreach srcfile,$(LOCAL_SRC_FILES),$(OPENCORE_DIR)/src/$(srcfile))
LOCAL_C_INCLUDES := $(my_LOCAL_PATH) $(OPENCORE_DIR)/include $(OPENCORE_DIR)/src $(OPENCORE_DIR)/oscl
LOCAL_ARM_MODE := arm

include $(BUILD_STATIC_LIBRARY)

