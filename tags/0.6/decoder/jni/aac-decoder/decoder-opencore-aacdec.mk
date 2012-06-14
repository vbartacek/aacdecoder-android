LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE 			:= decoder-opencore-aacdec
LOCAL_SRC_FILES 		:= aac-opencore-decoder.c

LOCAL_C_INCLUDES 		:= $(OPENCORE_DIR)/include \
							$(OSCL_DIR)/osclbase/src \
							$(OSCL_DIR)/config/android \
							$(OSCL_DIR)/config/shared

LOCAL_C_INCLUDES 		:= $(OPENCORE_DIR)/include $(LOCAL_PATH)/../opencore-aacdec/oscl

LOCAL_CFLAGS 			:= $(cflags_loglevels)

include $(BUILD_STATIC_LIBRARY)

