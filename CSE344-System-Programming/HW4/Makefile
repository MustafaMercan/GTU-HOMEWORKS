CC = gcc
CFLAGS = -Isrcs

SRCS = ./srcs/utils.c \
		./srcs/command_handler.c \
		./srcs/command_utils.c


all: biboClient biboServer

biboClient: client.c $(SRCS)
	$(CC) $(CFLAGS) $^ -o $@

biboServer: server.c $(SRCS)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f biboClient biboServer

re: clean all

.PHONY: all clean re