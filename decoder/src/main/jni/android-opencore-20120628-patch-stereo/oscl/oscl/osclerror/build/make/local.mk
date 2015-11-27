# Get the current local path as the first operation
LOCAL_PATH := $(call get_makefile_dir)

# Clear out the variables used in the local makefiles
include $(MK)/clear.mk


TARGET = osclerror


SRCDIR = ../../src
INCSRCDIR = ../../src

SRCS =  oscl_errno.cpp \
	oscl_error.cpp \
	oscl_error_imp_jumps.cpp \
	oscl_error_trapcleanup.cpp \
	oscl_heapbase.cpp

HDRS =  oscl_errno.h \
	oscl_error_allocator.h \
	oscl_error_codes.h \
	oscl_error.h \
	oscl_error_imp_cppexceptions.h \
	oscl_error_imp_fatalerror.h \
	oscl_error_imp.h \
	oscl_error_imp_jumps.h \
	oscl_error_trapcleanup.h \
	oscl_exception.h \
	oscl_heapbase.h \
	oscl_namestring.h \
	oscl_errno.inl \
	oscl_heapbase.inl


include $(MK)/library.mk

