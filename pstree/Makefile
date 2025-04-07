NAME := $(shell basename $(PWD))
all: $(NAME)-64 $(NAME)-32
	./$(NAME)-32 -p

64:
	./$(NAME)-64 --show-pids

%-32: %.c
	gcc -m32 $(CFLAGS) $(SRCS) -o $@ $(LDFLAGS)
	./$@-32 -p


include ../Makefile

