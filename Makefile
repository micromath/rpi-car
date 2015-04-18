CC=gcc
CC_FLAGS=-lwiringPi
NAME=carctl


all: $(NAME)

run: $(NAME)
	./$(NAME)

clear:
	rm -fv $(NAME)

$(NAME): $(NAME).c
	$(CC) $(NAME).c -o $(NAME) $(CC_FLAGS)



