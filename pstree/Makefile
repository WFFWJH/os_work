NAME := $(shell basename $(PWD))
include ../Makefile
all: $(NAME)-64 $(NAME)-32
	./$(NAME)-32 -p

64:
	./$(NAME)-64 --show-pids

$(NAME)-32: $(NAME).c
	@echo "=== 运行程序 ==="
	echo $@
	echo %
	echo "$@"
	echo "%"
	@echo "===开始编译==="
	@echo "源文件: $<"
	@echo "目标名: $@"
	@echo "项目名: $(NAME)"
	@echo "CFLAGS: $(CFLAGS)"
	@echo "LDFLAGS:$(LDFLAGS)"
	@echo "SRCS: $(SRCS)"
	gcc -m32 $(CFLAGS) $< -o $@ $(LDFLAGS)
#	./$@ -p

test:
	@echo "===开始编译==="
	@echo "源文件: $<"
	@echo "目标名: $@"
	@echo "项目名: $(NAME)"

	echo "hello"
	echo $@
	echo %
	echo "$@"
	echo "%"
	echo "Hello"
	./$@ -p




