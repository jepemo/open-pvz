IDIR =./src
CC=gcc
CFLAGS=-Wall -fPIC -I$(IDIR)
OUT_LIB=libopvz.so
LDIR =./lib
LIBS=-lm
OBJECTS = $(patsubst %.c, %.o, $(wildcard $(IDIR)/*.c))
HEADERS = $(wildcard *.h)

A=$(wildcard $(IDIR)/*.c)

all: $(OUT_LIB)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

$(OUT_LIB): $(OBJECTS)
	#ar rcs -o $(IDIR)/$@ $^
	gcc -Wall -shared -fPIC -o $(IDIR)/$@ $^
	cp $(IDIR)/$@ bindings/lua
	gcc -Wall -shared -fPIC -o bindings/lua/libopvz_lua.so  -I/usr/include/lua5.2 -I./src -llua5.1 bindings/lua/libopvz_lua.c

.PHONY: clean
clean:
	rm -f $(IDIR)/*.o *~ core $(IDIR)/$(OUT_LIB) bindings/lua/*.so bindings/lua/*.a
