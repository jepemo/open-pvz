IDIR =./src
CC=gcc
CFLAGS=-Wall -I$(IDIR)
OUT_LIB=opvz.a
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

.PHONY: clean
clean:
	rm -f $(IDIR)/*.o *~ core $(IDIR)/$(OUT_LIB)
