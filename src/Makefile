CC := gcc
AR := ar
CFLAGS := -Wall -Wextra
LDFLAGS := 
OUT := libvgs.a

ifeq ($(OS), Windows_NT)
	LDFLAGS += -lws2_32
endif

$(OUT) : vgsockets.o
	$(AR) rcs $@ $^ $(LDFLAGS)

vgsockets.o : vgsockets.c
	$(CC) $^ -c -o $@ $(CFLAGS) $(LDFLAGS)

clean:
	rm -f *.o
	rm -f *.a