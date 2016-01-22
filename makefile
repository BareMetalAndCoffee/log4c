MAKEFLAGS=--silent

ROOT_DIR=$(CURDIR)
BUILD_DIR=$(ROOT_DIR)/bld
SOURCE_DIR=$(ROOT_DIR)/src

all: clean build test package

.PHONY: clean
.PHONY: build
.PHONY: test
.PHONY: package

clean:
	rm -rf $(BUILD_DIR)

include $(SOURCE_DIR)/lib/make/generic_build_targets.mk
$(eval $(call GENERIC_BUILD_TGT,linux-x86-gcc))
$(eval $(call GENERIC_BUILD_TGT,linux-x86-clang))