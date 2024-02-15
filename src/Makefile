CC = gcc
CFLAGS = -Wall -Wextra -Werror -ncurses -std=c11
PTH = ../build/pong

all: pong

pong: pong_interactive.c
	$(CC) $(CFLAGS) pong_interactive.c -o $(PTH)

clean:
	rm -rf $(PTH)

rebuild: clean all