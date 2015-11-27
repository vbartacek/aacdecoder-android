# Makefile segment for aac utility when required along with the decoder

SRCS += ../util/getactualaacconfig/src/getactualaacconfig.cpp

# Currently, we don't have a dynamic build that will build only the AAC
# decoder and not the utility.
#HDRS += ../util/getactualaacconfig/include/getactualaacconfig.h
