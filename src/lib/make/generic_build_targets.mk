define GENERIC_BUILD_TGT

# Define new build targets
.PHONY: clean_$(1)
.PHONY: build_$(1)
.PHONY: test_$(1)
.PHONY: package_$(1)

$(BUILD_DIR)/$(1)/Makefile:
	mkdir -p $(BUILD_DIR)/$(1)
	cd $(BUILD_DIR)/$(1) && cmake \
      -D BUILD_INFO_TOOLCHAIN=$(1) \
      -D CMAKE_TOOLCHAIN_FILE=$(SOURCE_DIR)/lib/cmake/toolchains/$(1).cmake \
      -G "Unix Makefiles" \
      $(SOURCE_DIR)

clean_$(1): $(BUILD_DIR)/$(1)/Makefile
	$(MAKE) -C $(BUILD_DIR)/$(1) clean

_build_info_$(1):
	printf "\033[0;32mBUILD INFORMATION\n"
	printf "TOOLCHAIN: $(1)\n\033[0m"

build_$(1): _build_info_$(1) $(BUILD_DIR)/$(1)/Makefile
	$(MAKE) -C $(BUILD_DIR)/$(1)

# Link build targets to parent targets
build: build_$(1)
test: test_$(1)
package: package_$(1)

endef