CC := gcc
CFLAGS := -Wall -Wextra
LDFLAGS := -L../../src/ -lvgs

ifeq ($(OS), Windows_NT)
	LDFLAGS += -lws2_32
endif

build: server.c client.c
	$(CC) server.c -o server $(CFLAGS) $(LDFLAGS)
	$(CC) client.c -o client $(CFLAGS) $(LDFLAGS)
