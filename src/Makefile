
CC := gcc
CFLAGS := -std=c11 -Wall -Wextra -D_POSIX_C_SOURCE=200112L
BIN_DIR := bin
LDLIBS := -lncurses

SERVER_DIR := server
TEST_DIR := $(SERVER_DIR)/tests
COMMON_DIR := common

SRC_SERVER := $(wildcard $(SERVER_DIR)/*.c)
SRC_TESTS := $(wildcard $(TEST_DIR)/*.c)
COMMON_HEADERS := $(wildcard $(COMMON_DIR)/*.h)

# Excluir server/main.c del build de tests
SERVER_SRC_NO_MAIN := $(filter-out $(SERVER_DIR)/main.c, $(SRC_SERVER))

.PHONY: all client server tests clean

all: client server

client:
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) client/*.c $(COMMON_HEADERS) -o $(BIN_DIR)/client $(LDLIBS)

server:
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $(SRC_SERVER) $(COMMON_HEADERS) -o $(BIN_DIR)/server $(LDLIBS)

# ---- TESTS ----
tests: $(SRC_TESTS)
	@mkdir -p $(BIN_DIR)
	@for test_file in $(SRC_TESTS); do \
		test_name=$$(basename $$test_file .c); \
		echo " Compilando test: $$test_name"; \
		$(CC) $(CFLAGS) $$test_file $(SERVER_SRC_NO_MAIN) $(COMMON_HEADERS) -o $(BIN_DIR)/test_$$test_name $(LDLIBS); \
	done

clean:
	rm -rf $(BIN_DIR)

