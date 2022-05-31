CC=gcc
CFLAGS=-O3 -Werror=format-security -Werror=implicit-function-declaration -flto -Wall -Wextra

onload:
	$(CC) -o onload main.c include/colourbar/colourbar.c include/onload/onload.c $(CFLAGS)

clean:
	rm /usr/bin/onload

install:
	mv onload /usr/bin
