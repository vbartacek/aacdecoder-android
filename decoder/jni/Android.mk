mydir := $(call my-dir)

#
# Include the user's properties:
#
include $(mydir)/../../.ant.properties

OPENCORE_DIR 	:=	$(opencore-aacdec.dir)
LOGLEVEL 		:=	$(jni.loglevel)

include $(mydir)/aac-decoder/Android.mk
include $(mydir)/opencore-aacdec/Android.mk

dump:
	$(warning $(modules-dump-database))
	$(warning $(dump-src-file-tags))
	$(error Dump finished)
