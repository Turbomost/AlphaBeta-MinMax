CC=gcc
CFLAGS=-Wall -std=c11 -pedantic -lm -ggdb3 -g
FILES= alphabeta.c

.PHONY: run clean

all:run

run: $(FILES)
	$(CC) $(CFLAGS) -o $@ $(FILES)

clean:
	@rm -f run