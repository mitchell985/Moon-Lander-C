# Makefile for testing game.c
# this is need to compile game.c as gnu11 and enable -lcurses
# By: Mitchell Caddy
# Date: June 2015

# things to enable
LDFLAGS=-std=gnu11 -lncurses

all:

	gcc -o game curses_startup.c menu.c game.c $(LDFLAGS)

menu: curses_startup.h curses_startup.c menu.h menu.c 

	gcc -o menu curses_startup.c menu.c $(LDFLAGS)

#this one is useful to have
clean:
	rm –f *.o menu game