CFLAGS=-Wall -pedantic -std=c11 -I. -g
OFILES=queue.o hash.o webpage.o pageio.o

all:	$(OFILES)
	ar cr ../lib/libutils.a $(OFILES)


%.o:	%.c %.h
	gcc $(CFLAGS) -c $<

clean:
	rm -f webpage.o pageio.o





