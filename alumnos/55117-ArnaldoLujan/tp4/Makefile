

CC = gcc
CFLAGS = -g -Wall

TARGETS = servidor

all: $(TARGETS)

servidor: server.c funciones.c  
	  $(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)


clean:
	rm -f $(TARGETS) *.o *~

