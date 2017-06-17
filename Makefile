UNAME := $(shell uname)
IDIR =./src
CC=gcc
CFLAGS=-Wall -fPIC -I$(IDIR)
OUT_LIB=libopvz.so
LDIR =./lib
LIBS=-lm
OBJECTS = $(patsubst %.c, %.o, $(wildcard $(IDIR)/*.c))
BIN_TESTS = $(patsubst %.c, %.bin, $(wildcard tests/*.c))
HEADERS = $(wildcard *.h)

ifeq ($(UNAME), Linux)
	LUA_HEADERS=/usr/include/lua5.2
	LUA_FLAGS=-llua5.1
endif
ifeq ($(UNAME), Darwin)
	LUA_HEADERS=/usr/local/include/lua5.2
	LUA_FLAGS=-undefined dynamic_lookup
endif

A=$(wildcard $(IDIR)/*.c)

all: $(OUT_LIB)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

%.bin: %.c
	$(CC) -Wall -I./src $< -o $@ -L./src ./src/$(OUT_LIB)
	./$@

$(OUT_LIB): $(OBJECTS)
	@echo "OS is $(UNAME)"
	gcc -Wall -shared -fPIC -o $(IDIR)/$@ $^
	cp $(IDIR)/$@ bindings/lua
	gcc -Wall -shared -fPIC -o bindings/lua/libopvz_lua.so  -I$(LUA_HEADERS) -I./src $(LUA_FLAGS) bindings/lua/libopvz_lua.c ./src/*.c	

.PHONY: clean test
test: clean all $(BIN_TESTS)
	@echo "All TESTS executed."
clean:
	rm -f $(IDIR)/*.o *~ core $(IDIR)/$(OUT_LIB) bindings/lua/*.so bindings/lua/*.a tests/*.bin
