.PHONY: clean

TARGET_EXEC ?= run

SOURCE_DIR = .
OUTPUT_DIR = ../exec

SRCS := $(shell find $(SOURCE_DIR) -name *.cxx)
OBJS := $(SRCS:%=$(OUTPUT_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

INCLUDE_DIRS := $(shell find $(SOURCE_DIR) -type d)
INCLUDE_FLAG := $(addprefix -I,$(INCLUDE_DIRS))

C++ ?= g++

COMPILER_VERS ?= -std=c++20
COMPILER_FLAG ?= $(COMPILER_VERS) $(INCLUDE_FLAG) -MMD -MP -lopencv_dnn -lopencv_core -lopencv_imgcodecs

MKDIR ?= mkdir --parents

$(OUTPUT_DIR)/$(TARGET_EXEC): $(OBJS)
	$(C++) $(COMPILER_FLAG) -o $@ $(OBJS)

$(OUTPUT_DIR)/%.cxx.o: %.cxx
	$(MKDIR) $(dir $@)
	$(C++) $(COMPILER_FLAG) -o $@ -c $<

clean:
	$(RM) --recursive $(OUTPUT_DIR)

-include $(DEPS)