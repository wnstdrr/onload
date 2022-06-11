CC=gcc
CFLAGS=-O3 -Werror=format-security -Werror=implicit-function-declaration -Wall -Wextra
INSTALL_PATH=/usr/bin

onload:
	$(CC) -o onload main.c include/colourbar/colourbar.c include/onload/onload.c $(CFLAGS)

clean:
	rm /usr/bin/onload
	rm /usr/local/share/man/man1/onload.1
	rm /usr/local/share/man/man1/onload.1.gz

install:
	$(CC) -o onload main.c include/colourbar/colourbar.c include/onload/onload.c $(CFLAGS)
	mv onload $(INSTALL_PATH)
	mkdir -p /usr/local/share/man/man1
	cp onload.1 /usr/local/share/man/man1/onload.1
	gzip /usr/local/share/man/man1/onload.1
