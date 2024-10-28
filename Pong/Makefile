CC = gcc
CFLAGS = -Wall -Wextra -Werror --std=c11

all: clean build valgrind cppcheck

clean:
	rm -rf pong

build:
	$(CC) $(CFLAGS) pong.c -o pong

valgrind:
	valgrind --leak-check=full ./pong


cppcheck:
	valgrind --leak-check=full ./pong



.PHONY: all clean build test valgrind cppcheck
