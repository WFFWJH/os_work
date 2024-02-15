NAME := $(shell basename $(PWD))
all: $(NAME)-64 $(NAME)-32
	./$(NAME)-32 -p

32:
	./$(NAME)-32 -p

64:
	./$(NAME)-64 --show-pids


include ../Makefile

