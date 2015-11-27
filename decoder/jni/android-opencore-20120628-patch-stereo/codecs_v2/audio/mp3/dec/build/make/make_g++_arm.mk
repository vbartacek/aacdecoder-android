# Additional assembly files for linux-arm
ifeq ($(GLOBAL_CPU_ARCH_VERSION),0)
    ASM_INCLUSION:=0
else ifeq ($(GLOBAL_CPU_ARCH_VERSION),1)
    ASM_INCLUSION:=0
else ifeq ($(GLOBAL_CPU_ARCH_VERSION),2)
    ASM_INCLUSION:=0
else ifeq ($(GLOBAL_CPU_ARCH_VERSION),3)
    ASM_INCLUSION:=0
else
    ASM_INCLUSION:=1
endif

ifneq ($(ASM_INCLUSION),0)
SRCS+=  asm/pvmp3_polyphase_filter_window_gcc.s \
        asm/pvmp3_mdct_18_gcc.s \
        asm/pvmp3_dct_9_gcc.s \
        asm/pvmp3_dct_16_gcc.s
endif
