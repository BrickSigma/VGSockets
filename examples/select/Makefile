CC := gcc
CFLAGS := -Wall -Wextra
LDFLAGS := -L../../src/ -lvgs
EXT :=

ifeq ($(OS), Windows_NT)
	LDFLAGS += -lws2_32
	EXT += .exe
else
	EXT += .out
endif

build: server.c client.c
	$(CC) server.c -o server$(EXT) $(CFLAGS) $(LDFLAGS)
	$(CC) client.c -o client$(EXT) $(CFLAGS) $(LDFLAGS)

clean:
	rm -f *$(EXT)