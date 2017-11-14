

CC = gcc
CFLAGS = -g -Wall
LDLIBS=-pthread
TARGETS = servidor

all: $(TARGETS)

servidor: srv.c service.c  
	  $(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)


clean:
	rm -f $(TARGETS) *.o *~


