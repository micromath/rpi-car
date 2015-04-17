CC=g++
CC_FLAGS=
NAME=carGPIO
LIBS=-lmraa -lupm-i2clcd -lm 


all: $(NAME)

run: $(NAME)
	./$(NAME)

clear:
	rm -fv $(NAME)

$(NAME): $(NAME).c
	$(CC) $(NAME).c -o $(NAME) $(LIBS)



