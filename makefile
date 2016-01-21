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
	rm -rf bld

build: $(BUILD_DIR)/Makefile
	$(MAKE) -C $(BUILD_DIR)

$(BUILD_DIR)/Makefile:
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && \
       cmake -G "Unix Makefiles" $(SOURCE_DIR)

