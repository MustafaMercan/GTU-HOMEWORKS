NAME_1 = appendMeMore
NAME_2 = Q2
NAME_3 = Q3
CC = gcc
SRC_1 = Q1.c
SRC_2 = Q2.c 
SRC_3 = Q3.c
RM = rm -f

all:
	@$(CC) $(SRC_1) -o $(NAME_1)
	@$(CC) $(SRC_2) -o $(NAME_2) 
	@$(CC) $(SRC_3) -o $(NAME_3)  

clean:
	@$(RM) $(NAME_1) $(NAME_2) $(NAME_3)

re: clean all

PHONY: clean all re
