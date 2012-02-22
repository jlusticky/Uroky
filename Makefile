NAME=uroky
CC=gcc
CFLAGS=-std=c99 -pedantic -Wall -W `pkg-config --cflags gtk+-2.0` `pkg-config --libs gtk+-2.0`
ALLFILES=uroky.c Makefile README

$(NAME): $(NAME).c
	$(CC) $(CFLAGS) $(NAME).c -o $(NAME)

.PHONY: clean pack

clean:
	rm -rf $(NAME)

pack:
	tar zcvf $(NAME).tar.gz $(ALLFILES)
