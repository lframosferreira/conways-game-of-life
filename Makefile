CC = gcc
CFLAGS = -Wall
LIBS = -lncurses
BIN = bin

all:
	test -d $(BIN) || mkdir $(BIN)
	$(CC) main.c -o $(BIN)/main $(CFLAGS) $(LIBS)

test:
	$(BIN)/main

clean:
	rm -f $(BIN)/*

