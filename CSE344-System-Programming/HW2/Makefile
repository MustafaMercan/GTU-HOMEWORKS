CC=gcc
CFLAGS=-I.

SRCS=./srcs/log_utils.c \
     ./srcs/terminal_utils.c \
     ./srcs/utils.c

OBJS=$(SRCS:.c=.o)

EXECUTABLE=hw2

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJS) main.o
	$(CC) -o $@ $^

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	rm -f $(OBJS) main.o $(EXECUTABLE)
	rm -rf ./logs/*

re: clean all

.PHONY: all clean re

