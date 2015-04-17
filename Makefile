CC=gcc
CC_FLAGS=
NAME=carctl
LIBS=-lwiringPi

all: $(NAME)

run: $(NAME)
	./$(NAME)

clear:
	rm -fv $(NAME)

$(NAME): $(NAME).c
	$(CC) $(NAME).c -o $(NAME) $(LIBS)



