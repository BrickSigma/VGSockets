CC := gcc
CFLAGS := -Wall -Wextra
LDFLAGS := -lws2_32

OUT := libvgs.a

$(OUT) : vgsockets.o
	ar rc $@ $^ $(LDFLAGS)

vgsockets.o : vgsockets.c
	$(CC) $^ -c -o $@ $(CFLAGS) $(LDFLAGS)

clean:
	rm -f *.o
	rm -f *.a