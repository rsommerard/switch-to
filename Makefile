CC	= gcc
CFLAGS	= -Wall -Werror -pedantic -m32
OBJS	= main.o switch_to.o
EXEC	= main

all: $(EXEC)

main: $(OBJS)
	$(CC) $(OBJS) -o $@

main.o: main.c switch_to.h
switch_to.o: switch_to.c switch_to.h

.PHONY: clean
clean:
	rm -f $(OBJS) $(EXEC) *~
