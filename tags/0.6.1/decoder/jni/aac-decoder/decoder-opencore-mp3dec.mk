LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE 			:= decoder-opencore-mp3dec
LOCAL_SRC_FILES 		:= mp3-opencore-decoder.c

LOCAL_C_INCLUDES 		:= $(OPENCORE_DIR)/include \
							$(OSCL_DIR)/osclbase/src \
							$(OSCL_DIR)/config/android \
							$(OSCL_DIR)/config/shared

LOCAL_C_INCLUDES 		:= $(OPENCORE_MP3)/include $(OPENCORE_MP3)/src $(LOCAL_PATH)/../opencore-mp3dec/oscl

LOCAL_CFLAGS 			:= $(cflags_loglevels)

include $(BUILD_STATIC_LIBRARY)

