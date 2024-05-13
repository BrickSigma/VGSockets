CC := gcc
AR := ar
CFLAGS := -Wall -Wextra -static
LDFLAGS := 

LIBRARY ?= STATIC

ifeq (${LIBRARY}, SHARED)
	LDFLAGS += -fPIC
endif

HEADERNAME := vgs
LIBNAME := libvgs
STATIC_EXT := .a
SHARED_EXT := .so
OUT := $(LIBNAME)

HEADERPATH := /usr/local/include
LIBPATH := /usr/local/lib

$(OUT) : core.o error.o poll.o
ifeq (${LIBRARY}, STATIC)
	$(AR) rcs $@${STATIC_EXT} $^
else
	gcc -shared $(LDFLAGS) -o $@${SHARED_EXT} $^
endif

error.o : error.c
	$(CC) $^ -c -o $@ $(CFLAGS) $(LDFLAGS)
	
core.o : core.c
	$(CC) $^ -c -o $@ $(CFLAGS) $(LDFLAGS)

poll.o : poll.c
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
	@echo "Removing $(LIBPATH)/$(LIBNAME).a and $(HEADERPATH)/$(HEADERNAME).h"
	@rm -f $(LIBPATH)/$(LIBNAME).a
	@rm -f $(HEADERPATH)/$(HEADERNAME).h
endif
else
	@echo "You need super user priviliges to install"
endif

.PHONY: clean
clean:
	rm -f *.o
	rm -f ${LIBNAME}.a
	rm -f ${LIBNAME}.so