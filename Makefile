IDIR =./src
CC=gcc
CFLAGS=-Wall -I$(IDIR)
OUT_LIB=opvz.so
LDIR =./lib
LIBS=-lm
OBJECTS = $(patsubst %.c, %.o, $(wildcard $(IDIR)/*.c))
HEADERS = $(wildcard *.h)

A=$(wildcard $(IDIR)/*.c)

all: $(OUT_LIB)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

$(OUT_LIB): $(OBJECTS)
	ar rcs -o $(IDIR)/$@ $^
	# cp $(IDIR)/$@ bindings/lua
	gcc -Wall -shared -fPIC -o bindings/lua/opvzlib.so  -I/usr/include/lua5.1 -I./src -llua5.1 bindings/lua/opvz_binding.c

.PHONY: clean
clean:
	rm -f $(IDIR)/*.o *~ core $(IDIR)/$(OUT_LIB) bindings/lua/*.so bindings/lua/*.a
