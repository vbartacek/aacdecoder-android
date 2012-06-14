LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOGLEVELS =

# Loglevels
ifeq ($(LOGLEVEL),error)
	LOGLEVELS	+= ERROR
endif
ifeq ($(LOGLEVEL),warn)
	LOGLEVELS	+= ERROR WARN
endif
ifeq ($(LOGLEVEL),info)
	LOGLEVELS	+= ERROR WARN INFO
endif
ifeq ($(LOGLEVEL),debug)
	LOGLEVELS	+= ERROR WARN INFO DEBUG
endif
ifeq ($(LOGLEVEL),trace)
	LOGLEVELS	+= ERROR WARN INFO DEBUG TRACE
endif

cflags_loglevels	:= $(foreach ll,$(LOGLEVELS),-DAACD_LOGLEVEL_$(ll))


# Final library:
LOCAL_MODULE 			:= aacdecoder
LOCAL_SRC_FILES 		:= aac-decoder.c
LOCAL_CFLAGS 			:= $(cflags_loglevels)
LOCAL_LDLIBS 			:= -llog
LOCAL_STATIC_LIBRARIES 	:= decoder-opencore-aacdec decoder-opencore-mp3dec libpv_aac_dec libpv_mp3_dec
include $(BUILD_SHARED_LIBRARY)


# Build components:
include $(LOCAL_PATH)/decoder-opencore-aacdec.mk
include $(LOCAL_PATH)/decoder-opencore-mp3dec.mk

