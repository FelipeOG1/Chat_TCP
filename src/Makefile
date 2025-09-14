CC := gcc
CFLAGS := -std=c11 -Wall -Wextra -D_POSIX_C_SOURCE=200112L
BIN_DIR := bin
LDLIBS := -lncurses
.PHONY: all client server clean

all: client server

client:
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) client/*.c common/*.c -o $(BIN_DIR)/client $(LDLIBS)

server:
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) server/*.c common/*.c -o $(BIN_DIR)/server

clean:
	rm -rf $(BIN_DIR)
