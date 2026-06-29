DESTDIR := /usr/bin

cc:
		gcc fetch.c -o fetch

static:
		gcc fetch.c -o fetch -static

install:
		cp fetch $(DESTDIR)

clean:
		rm -f fetch

clear:
		rm -f fetch
