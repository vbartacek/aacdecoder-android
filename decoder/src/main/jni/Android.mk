mydir := $(call my-dir)

opencore-top.dir=./android-opencore-20120628-patch-stereo
jni.loglevel=info

PV_TOP 		:=	$(opencore-top.dir)
OPENCORE_DIR 	:=	$(opencore-top.dir)/codecs_v2/audio/aac/dec
OPENCORE_MP3 	:=	$(opencore-top.dir)/codecs_v2/audio/mp3/dec
OSCL_DIR	:=	$(opencore-top.dir)/oscl/oscl
LOGLEVEL 	:=	debug

include $(mydir)/aac-decoder/Android.mk
include $(mydir)/opencore-aacdec/Android.mk
include $(mydir)/opencore-mp3dec/Android.mk

dump:
	$(warning $(modules-dump-database))
	$(warning $(dump-src-file-tags))
	$(error Dump finished)
