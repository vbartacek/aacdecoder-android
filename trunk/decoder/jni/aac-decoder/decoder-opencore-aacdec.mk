LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE 			:= decoder-opencore-aacdec
LOCAL_SRC_FILES 		:= aac-opencore-decoder.c
LOCAL_C_INCLUDES 		:= $(OPENCORE_DIR)/include
LOCAL_CFLAGS 			:= $(cflags_loglevels)

include $(BUILD_STATIC_LIBRARY)

