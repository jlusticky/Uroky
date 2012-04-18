NAME=uroky
CC=gcc
CFLAGS=-std=c99 -pedantic -Wall -Wextra
GTKLIBS=`pkg-config --cflags gtk+-2.0` `pkg-config --libs gtk+-2.0`
ALLFILES=uroky.c uroky-win.c Makefile README

$(NAME): $(NAME).c
	$(CC) $(CFLAGS) $(GTKLIBS) $(NAME).c -g -o $(NAME)

$(NAME).exe: $(NAME)-win.c
	i586-mingw32msvc-gcc $(CFLAGS) $(NAME)-win.c -g -o $(NAME).exe

.PHONY: clean pack

clean:
	rm -rf $(NAME) $(NAME).exe

pack:
	tar zcvf $(NAME).tar.gz $(ALLFILES)
