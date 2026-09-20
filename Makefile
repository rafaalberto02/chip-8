MKDIR := mkdir -p
RM := rm -r
CC := cc

COMMON_FLAGS := -Wall -Wextra -Werror -Wpedantic -MMD -MP

SRC_DIR := src
INC_DIRS := include $(SRC_DIR)
BUILD_DIR := build
BIN_DIR := bin
TST_DIR := tests

TARGET := $(BIN_DIR)/chip_8
TARGET_TST := $(BIN_DIR)/chip_8_tst

BUILD ?= debug

ifeq ($(BUILD),release)
	OBJ_DIR := $(BUILD_DIR)/release
	CFLAGS := $(COMMON_FLAGS) -O2 -DNDEBUG
else ifeq ($(BUILD),debug)
	OBJ_DIR := $(BUILD_DIR)/debug
	CFLAGS := $(COMMON_FLAGS) -g -O0 -DDEBUG
else
	$(error BUILD must be `debug` or `release`, got '$(BUILD)')
endif

CFLAGS += $(addprefix -I,$(INC_DIRS))

SRCS := $(shell find $(SRC_DIR) -name "*.c")
OBJS := $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))
DEPS := $(OBJS:.o=.d)

# Build

$(TARGET): $(OBJS) $(BIN_DIR)
	$(CC) $(OBJS) $(CFLAGS) -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(MKDIR) $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR) $(BUILD_DIR):
	@$(MKDIR) $@

# Commands

run: $(TARGET)
	./$(TARGET)

clean:
	$(RM) $(BUILD_DIR) $(BIN_DIR)

-include $(DEPS)

.PHONY: run clean
