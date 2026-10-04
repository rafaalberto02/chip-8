MKDIR := mkdir -p
RM := rm -rf
CC := cc

COMMON_FLAGS := -Wall -Wextra -Werror -Wpedantic -MMD -MP

BUILD_DIR := build

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

INC_DIRS := include/chip_8 $(SRC_DIR)

CFLAGS += $(addprefix -I,$(INC_DIRS)) 
CFLAGS += $(shell pkg-config --cflags raylib)

LDFLAGS = $(shell pkg-config --libs raylib) # -framework IOKit -framework Cocoa -framework OpenGL -framework CoreVideo

# Build

SRC_DIR := src
BIN_DIR := bin

SRCS := $(shell find $(SRC_DIR) -name "*.c")
OBJS := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))
DEPS := $(OBJS:.o=.d)
TARGET := $(BIN_DIR)/chip_8

$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CC) $(OBJS) $(CFLAGS) $(LDFLAGS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(MKDIR) $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Build Tests

BIN_DIR_TST := bin/tests
OBJ_DIR_TST := $(OBJ_DIR)/tests
TST_DIR := tests

SRCS_TST := $(shell find $(TST_DIR) -name "*.c")
OBJS_TST := $(patsubst $(TST_DIR)/%.c, $(OBJ_DIR_TST)/%.o, $(SRCS_TST)) $(filter-out $(OBJ_DIR)/main.o,$(OBJS))
DEPS_TST := $(OBJS_TST:.o=.d)
TARGETS_TST := $(patsubst $(TST_DIR)/%.c,$(BIN_DIR_TST)/%,$(SRCS_TST))
TARGETS_TST_DIR := $(dir $(TARGETS_TST))

CFLAGS_TST = $(CFLAGS) $(addprefix -I,$(TST_DIR))
$(BIN_DIR_TST)/%: $(OBJS_TST) | $(TARGETS_TST_DIR)
	$(CC) $^ $(CFLAGS_TST) -o $@

$(OBJ_DIR_TST)/%.o: $(TST_DIR)/%.c
	$(MKDIR) $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Directories

$(BIN_DIR) $(OBJ_DIR) $(TARGETS_TST_DIR):
	@$(MKDIR) $@

# Commands

test: $(TARGETS_TST)
	@for t in $(TARGETS_TST); do echo "RUN $$t"; ./$$t || exit 1; done

check: test

run: $(TARGET)
	./$(TARGET)

clean:
	$(RM) $(BUILD_DIR) $(BIN_DIR)

-include $(DEPS)

.PHONY: run clean test check
