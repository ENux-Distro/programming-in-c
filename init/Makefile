DESTDIR := /usr/local/sbin

cc:
		gcc init.c -o init

static:
		gcc init.c -o init -static

install:
		cp init $(DESTDIR)/init
