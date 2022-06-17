CC=gcc
CFLAGS=-O3 -Werror=format-security -Werror=implicit-function-declaration -Wall -Wextra
INSTALL_PATH=/usr/bin

clean: $(GENERATED)
	rm -f lib/*.o
	rmdir lib/
	rm -f $(INSTALL_PATH)/onload $(INSTALL_PATH)/cbar-opts

install:
	mkdir -p lib/
	$(CC) -g -fPIC -O -c include/onload/onload.c -o lib/onload.o $(CFLAGS)
	$(CC) -g -fPIC -O -c include/colourbar/colourbar.c -o lib/colourbar.o $(CFLAGS)

	$(CC) -o $(INSTALL_PATH)/onload main.c lib/onload.o lib/colourbar.o $(CFLAGS)
	$(CC) -o $(INSTALL_PATH)/cbar-opts cbar_opts.c lib/colourbar.o $(CFLAGS)
