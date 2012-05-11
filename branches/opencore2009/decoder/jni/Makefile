#
# This is a shortcut Makefile  allowing to directly compile in VIM :mak
#

include ../../.ant.properties

all:
	make -f $(ndk.home)/build/core/build-local.mk $(make.options)

dump:
	make -f $(ndk.home)/build/core/build-local.mk dump

TAGS:
	ctags --links=no -R aac-decoder $(opencore-aacdec.dir)
