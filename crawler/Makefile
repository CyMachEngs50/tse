CFLAGS= -Wall -pedantic -std=c11 -I../utils -L../lib -g
LIBS=-lutils -lcurl

all: crawler pageiotest

crawler:
	gcc $(CFLAGS) crawler.c $(LIBS) -o $@

pageiotest:
	gcc  $(CFLAGS) pageiotest.c $(LIBS) -o $@

clean:
	rm -f crawler pageiotest
