CC=gcc
CFLAGS=-O3 -Werror=format-security -Werror=implicit-function-declaration -Wall -Wextra
INSTALL_PATH=/usr/bin
MAN_PATH=/usr/share/man/man1

clean:
	rm -f /usr/lib/onload/*
	rm -f /usr/include/onload/*
	rmdir /usr/lib/onload /usr/include/onload/
	rm -f $(INSTALL_PATH)/onload $(INSTALL_PATH)/cbar-opts
	rm -f $(MAN_PATH)/onload.1.gz $(MAN_PATH)/onload.1

libcolourbar.so libonload.so:
	mkdir -p /usr/lib/onload
	$(CC) -shared -o /usr/lib/onload/libonload.so onload.c -fPIC $(CFLAGS)
	$(CC) -shared -o /usr/lib/onload/libcolourbar.so colourbar.c -fPIC $(CFLAGS)

install: libonload.so libcolourbar.so
	mkdir /usr/include/onload/
	cp onload.h /usr/include/onload
	cp colours.h /usr/include/onload
	cp config.h /usr/include/onload
	$(CC) -o $(INSTALL_PATH)/onload main.c /usr/lib/onload/libonload.so /usr/lib/onload/libcolourbar.so $(CFLAGS)
	$(CC) -o $(INSTALL_PATH)/cbar-opts cbar_opts.c /usr/lib/onload/libcolourbar.so $(CFLAGS)
	cp onload.1 $(MAN_PATH) && gzip $(MAN_PATH)/onload.1
