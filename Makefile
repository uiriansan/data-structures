CC=gcc
FLAGS=-Wall -ggdb
SRC_DIR=src
TEST_DIR=tests
BUILD_DIR=build/bin
T_BUILD_DIR=build/tests

.PHONY: all clean

SRCS=$(wildcard $(SRC_DIR)/*.c)
OBJS=$(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%,$(SRCS))

T_SRCS=$(wildcard $(TEST_DIR)/*.c)
T_OBJS=$(patsubst $(TEST_DIR)/%.c,$(T_BUILD_DIR)/%,$(T_SRCS))

all: $(OBJS) test

$(BUILD_DIR)/%: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $< $(FLAGS) -o $@

$(T_BUILD_DIR)/%: $(TEST_DIR)/%.c
	@mkdir -p $(T_BUILD_DIR)
	$(CC) $< $(FLAGS) -o $@

test: $(T_OBJS)
	@echo "Running tests..."
	@passes=0; \
	failures=0; \
	for test in $^; do \
		echo -n "$$test ... "; \
		if ./$$test > /dev/null 2>&1; then \
			echo -e "\e[0;32mOK\e[0m"; \
			passes=$$((passes + 1)); \
		else \
			echo -e "\e[0;31mFAIL\e[0m"; \
			failures=$$((failures + 1)); \
		fi; \
	done; \
	if [ $$failures -gt 0 ]; then \
		echo -e "\e[0;31m$$passes passed, $$failures failed.\e[0m"; \
	else \
		echo -e "\e[0;32m$$passes passed, $$failures failed.\e[0m"; \
	fi; \
		

clean:
	rm -rf $(BUILD_DIR) $(T_BUILD_DIR)
