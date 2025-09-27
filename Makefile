# ======================================================
# Makefile for application and unity tests
#
# Terminal commands:
#   make clean      	- Remove all build artifacts
#   make test       	- Build the Unity test runner (modules + test/*.c)
#   make run-test   	- Run all unit tests (./build/run_test)
#   make app        	- Build the application (src/*.c including main.c)
#   make run-app    	- Run the application (./build/app)
#
# Recommended workflow:
#   1. make clean		- Start fresh
#   2. make app 		- make sure the application compiles
#   3. make test		- make sure the tests compile
#   4. make run-test 	- Run the tests first (catch regressions early)
#  	5. make run-app  	- Then run the application
#
# ======================================================

# Makefile for app + Unity tests (MSYS2/Unix)
CC        = gcc
CFLAGS    = -Wall -Wextra -g -std=c11 -Isrc -Iunity
LDFLAGS   =
LDLIBS    = -lm
BUILD_DIR = build

# ----------------------------
# App (src/main.c + modules)
# ----------------------------
SRC_DIR   = src
APP_BIN   = $(BUILD_DIR)/app

SRCS_APP  := $(wildcard $(SRC_DIR)/*.c)
OBJS_APP  := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/src_%.o,$(SRCS_APP))

# ----------------------------
# Tests (Unity)
# ----------------------------
TEST_DIR  = test
UNITY_DIR = unity
UNITY_SRC = $(UNITY_DIR)/unity.c
TEST_BIN  = $(BUILD_DIR)/run_test

TEST_SRCS := $(wildcard $(TEST_DIR)/*.c)
OBJS_TEST := $(patsubst $(TEST_DIR)/%.c,$(BUILD_DIR)/test_%.o,$(TEST_SRCS))

MODULE_SRCS := $(filter-out $(SRC_DIR)/main.c,$(SRCS_APP))
MODULE_OBJS := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/src_%.o,$(MODULE_SRCS))

# ----------------------------
# Phony targets
# ----------------------------
.PHONY: all app run-app test run-test clean

all: app test

# ----------------------------
# Build App
# ----------------------------
app: $(APP_BIN)

$(APP_BIN): $(OBJS_APP) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LDLIBS)

# Compile src/*.c -> build/src_%.o
$(BUILD_DIR)/src_%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

run-app: app
	./$(APP_BIN)

# ----------------------------
# Build Tests (Unity)
# ----------------------------
test: $(TEST_BIN)

$(TEST_BIN): $(MODULE_OBJS) $(OBJS_TEST) $(UNITY_SRC) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(MODULE_OBJS) $(OBJS_TEST) $(UNITY_SRC) $(LDLIBS)

# Compile test/*.c -> build/test_%.o
$(BUILD_DIR)/test_%.o: $(TEST_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

run-test: test
	./$(TEST_BIN)

# ----------------------------
# Utilities
# ----------------------------
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)
