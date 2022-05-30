CC=gcc

main:
	gcc -o onload main.c include/colourbar/colourbar.c include/onload/onload.c -Wall -Wextra

clean:
	rm /usr/bin/onload

install:
	mv onload /usr/bin
