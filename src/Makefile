CC := gcc
AR := ar
CFLAGS := -Wall -Wextra -static
LDFLAGS := 
OUT := libvgs.a

ifeq ($(OS), Windows_NT)
	LDFLAGS += -lws2_32
endif

$(OUT) : core.o error.o select.o
	$(AR) rcs $@ $^

error.o : error.c
	$(CC) $^ -c -o $@ $(CFLAGS) $(LDFLAGS)
	
core.o : core.c
	$(CC) $^ -c -o $@ $(CFLAGS) $(LDFLAGS)

select.o : select.c
	$(CC) $^ -c -o $@ $(CFLAGS) $(LDFLAGS)

clean:
	rm -f *.o
	rm -f *.a