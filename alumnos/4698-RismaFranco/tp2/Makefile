CC=gcc
CFLAGS=-g -Wall
TARGETS=tp2

all: $(TARGETS)

format:
	fold -w 80 -s noticia > noticia

tp2: *.c
	$(CC) $(CFLAGS) -o $@ $^

test: tp2
	cat noticia | ./tp2 -o "salida.txt"

strace: tp2
	cat noticia | strace -f ./tp2 -o "salida.txt"

clean:
	$(RM) tp2 *.o *~ $(TARGETS)
