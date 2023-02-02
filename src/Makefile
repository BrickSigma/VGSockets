CC := gcc
AR := ar
CFLAGS := -Wall -Wextra -static
LDFLAGS := 

HEADERNAME := vgs
LIBNAME := libvgs
OUT := $(LIBNAME)

HEADERPATH := /usr/local/include
LIBPATH := /usr/local/lib

ifeq ($(OS), Windows_NT)
	LDFLAGS += -lws2_32
endif

$(OUT).a : core.o error.o select.o
	$(AR) rcs $@ $^

error.o : error.c
	$(CC) $^ -c -o $@ $(CFLAGS) $(LDFLAGS)
	
core.o : core.c
	$(CC) $^ -c -o $@ $(CFLAGS) $(LDFLAGS)

select.o : select.c
	$(CC) $^ -c -o $@ $(CFLAGS) $(LDFLAGS)

install:
ifeq ($(shell id -u), 0)
ifeq ($(OS), Windows_NT)
	@echo "Not yet implemented for Windows"
else
	cp $(LIBNAME).a $(LIBPATH)
	cp $(HEADERNAME).h $(HEADERPATH)
endif
else
	@echo "You need super user priviliges to install"
endif

uninstall:
ifeq ($(shell id -u), 0)
ifeq ($(OS), Windows_NT)
	@echo "Not yet implemented for Windows"
else
	rm -f $(LIBPATH)/$(LIBNAME).a
	rm -f $(HEADERPATH)/$(HEADERNAME).h
endif
else
	@echo "You need super user priviliges to install"
endif

clean:
	rm -f *.o
	rm -f *.a