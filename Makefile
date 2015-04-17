CC=gcc
NAME=carctl


all: $(NAME)

run: $(NAME)
	./$(NAME)

$(NAME): $(NAME).c
	$(CC) $(NAME).c -o $(NAME)



