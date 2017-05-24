IDIR =./src
CC=gcc
CFLAGS=-Wall -fPIC -I$(IDIR)
OUT_LIB=libopvz.so
LDIR =./lib
LIBS=-lm
OBJECTS = $(patsubst %.c, %.o, $(wildcard $(IDIR)/*.c))
BIN_TESTS = $(patsubst %.c, %.bin, $(wildcard tests/*.c))
HEADERS = $(wildcard *.h)

A=$(wildcard $(IDIR)/*.c)

all: $(OUT_LIB)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

%.bin: %.c
	$(CC) -Wall -I./src $< -o $@ -L./src ./src/$(OUT_LIB)
	./$@

$(OUT_LIB): $(OBJECTS)
	gcc -Wall -shared -fPIC -o $(IDIR)/$@ $^
	cp $(IDIR)/$@ bindings/lua
	gcc -Wall -shared -fPIC -o bindings/lua/libopvz_lua.so  -I/usr/include/lua5.2 -I./src -llua5.1 bindings/lua/libopvz_lua.c ./src/*.c

.PHONY: clean test
test: clean all $(BIN_TESTS)
	@echo "All TESTS executed."
clean:
	rm -f $(IDIR)/*.o *~ core $(IDIR)/$(OUT_LIB) bindings/lua/*.so bindings/lua/*.a tests/*.bin
