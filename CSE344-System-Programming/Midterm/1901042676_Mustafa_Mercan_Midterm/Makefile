CC = gcc
CFLAGS = -Isrcs

SRCS = ./srcs/command_functions.c \
       ./srcs/command_utils.c \
       ./srcs/utils.c


all: biboClient biboServer

biboClient: client.c $(SRCS)
	$(CC) $(CFLAGS) $^ -o $@

biboServer: server.c $(SRCS)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f biboClient biboServer

re: clean all

.PHONY: all clean re