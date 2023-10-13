CC = g++
CFLAGS = -Wall
LIBS = -lncurses
BIN = bin

all:
	test -d $(BIN) || mkdir $(BIN)
	$(CC) main.cpp -o $(BIN)/main $(CFLAGS) $(LIBS)

clean:
	rm -f $(BIN)/*

