CC=gcc
CFLAGS=-O3 -Werror=format-security -Werror=implicit-function-declaration -Wall -Wextra
INSTALL_PATH=/usr/bin
MAN_PATH=/usr/local/share/man/man1

clean:
	rm -f lib/*.o
	rmdir lib/
	rm -f $(INSTALL_PATH)/onload $(INSTALL_PATH)/cbar-opts
	rm -f $(MAN_PATH)/onload.1.gz $(MAN_PATH)/onload.1

install:
	mkdir -p lib/
	$(CC) -g -fPIC -O -c include/onload/onload.c -o lib/onload.o $(CFLAGS)
	$(CC) -g -fPIC -O -c include/colourbar/colourbar.c -o lib/colourbar.o $(CFLAGS)

	$(CC) -o $(INSTALL_PATH)/onload main.c lib/onload.o lib/colourbar.o $(CFLAGS)
	$(CC) -o $(INSTALL_PATH)/cbar-opts cbar_opts.c lib/colourbar.o $(CFLAGS)

	cp onload.1 $(MAN_PATH)
	gzip $(MAN_PATH)/onload.1
