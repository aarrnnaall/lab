

CC = gcc
CFLAGS = -g -Wall
LDLIBS=-pthread
TARGETS = servidor

all: $(TARGETS)

servidor: server.c funciones.c  
	  $(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)


clean:
	rm -f $(TARGETS) *.o *~


