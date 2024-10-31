.PHONY: all clean clang main tetris.a $(BUILD_DIR) install

CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11
GCOVFLAGS = -L. --coverage
OS = $(shell uname)
FLAGS = -lncurses

ifeq ($(OS), Linux)
    TFLAGS = -lcheck -pthread -lrt -lm -lsubunit -lncurses
else
    TFLAGS = -lcheck -lncurses
endif

BRICK_GAME_DIR = brick_game/tetris
GUI_DIR = gui/cli
BUILD_DIR = $(BRICK_GAME_DIR)/build

all: clean $(BUILD_DIR) clang tetris.a main

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/create_game.o: $(BRICK_GAME_DIR)/create_game.c $(BRICK_GAME_DIR)/tetris.h
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR)/create_tetfield.o: $(BRICK_GAME_DIR)/create_tetfield.c $(BRICK_GAME_DIR)/tetris.h
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR)/create_tetfigure.o: $(BRICK_GAME_DIR)/create_tetfigure.c $(BRICK_GAME_DIR)/tetris.h
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR)/get_random_tetromino.o: $(BRICK_GAME_DIR)/get_random_tetromino.c $(BRICK_GAME_DIR)/tetris.h
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR)/free_tetfield.o: $(BRICK_GAME_DIR)/free_tetfield.c $(BRICK_GAME_DIR)/tetris.h
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR)/free_game.o: $(BRICK_GAME_DIR)/free_game.c $(BRICK_GAME_DIR)/tetris.h
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR)/game_over.o: $(BRICK_GAME_DIR)/game_over.c $(BRICK_GAME_DIR)/tetris.h
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR)/check_down.o: $(BRICK_GAME_DIR)/check_down.c $(BRICK_GAME_DIR)/tetris.h
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR)/append_figure.o: $(BRICK_GAME_DIR)/append_figure.c $(BRICK_GAME_DIR)/tetris.h
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR)/check_right.o: $(BRICK_GAME_DIR)/check_right.c $(BRICK_GAME_DIR)/tetris.h
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR)/check_left.o: $(BRICK_GAME_DIR)/check_left.c $(BRICK_GAME_DIR)/tetris.h
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR)/block_reverse.o: $(BRICK_GAME_DIR)/block_reverse.c $(BRICK_GAME_DIR)/tetris.h
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR)/block_reverse_4.o: $(BRICK_GAME_DIR)/block_reverse_4.c $(BRICK_GAME_DIR)/tetris.h
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR)/check_left_block.o: $(BRICK_GAME_DIR)/check_left_block.c $(BRICK_GAME_DIR)/tetris.h
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR)/check_right_block.o: $(BRICK_GAME_DIR)/check_right_block.c $(BRICK_GAME_DIR)/tetris.h
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR)/draw_figure.o: $(BRICK_GAME_DIR)/draw_figure.c $(BRICK_GAME_DIR)/tetris.h
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR)/clear_block.o: $(BRICK_GAME_DIR)/clear_block.c $(BRICK_GAME_DIR)/tetris.h
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR)/down_figures.o: $(BRICK_GAME_DIR)/down_figures.c $(BRICK_GAME_DIR)/tetris.h
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR)/filter_filed.o: $(BRICK_GAME_DIR)/filter_filed.c $(BRICK_GAME_DIR)/tetris.h
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR)/check_to_temp.o: $(BRICK_GAME_DIR)/check_to_temp.c $(BRICK_GAME_DIR)/tetris.h
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR)/random_num.o: $(BRICK_GAME_DIR)/random_num.c $(BRICK_GAME_DIR)/tetris.h
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR)/draw_field.o: $(GUI_DIR)/draw_field.c $(BRICK_GAME_DIR)/tetris.h
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR)/temp_one.o: $(GUI_DIR)/temp_one.c $(BRICK_GAME_DIR)/tetris.h
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR)/control.o: $(GUI_DIR)/control.c $(BRICK_GAME_DIR)/tetris.h
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR)/temp_two.o: $(GUI_DIR)/temp_two.c $(BRICK_GAME_DIR)/tetris.h
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR)/game_tetris.o: $(GUI_DIR)/game_tetris.c $(BRICK_GAME_DIR)/tetris.h
	$(CC) $(CFLAGS) -c -o $@ $<

tetris.a: $(BUILD_DIR)/game_tetris.o $(BUILD_DIR)/random_num.o $(BUILD_DIR)/check_to_temp.o $(BUILD_DIR)/temp_two.o $(BUILD_DIR)/filter_filed.o $(BUILD_DIR)/temp_two.o $(BUILD_DIR)/control.o $(BUILD_DIR)/temp_one.o $(BUILD_DIR)/draw_field.o $(BUILD_DIR)/down_figures.o $(BUILD_DIR)/create_game.o $(BUILD_DIR)/create_tetfield.o $(BUILD_DIR)/create_tetfigure.o $(BUILD_DIR)/get_random_tetromino.o $(BUILD_DIR)/free_tetfield.o $(BUILD_DIR)/free_game.o $(BUILD_DIR)/game_over.o $(BUILD_DIR)/check_down.o $(BUILD_DIR)/append_figure.o $(BUILD_DIR)/check_right.o $(BUILD_DIR)/check_left.o $(BUILD_DIR)/block_reverse.o $(BUILD_DIR)/block_reverse_4.o $(BUILD_DIR)/check_left_block.o $(BUILD_DIR)/check_right_block.o $(BUILD_DIR)/draw_figure.o $(BUILD_DIR)/clear_block.o
	ar rcs $@ $^

main: main.o tetris.a
	$(CC) main.o tetris.a $(FLAGS) -o main && ./main

main.o: $(GUI_DIR)/main.c
	$(CC) $(CFLAGS) -c $(GUI_DIR)/main.c -o main.o

install:
	sudo apt-get update
	sudo apt-get install -y gcc clang-format libncurses-dev


clang:
	clang-format -i $(BRICK_GAME_DIR)/*.c $(BRICK_GAME_DIR)/*.h $(GUI_DIR)/*.c *.c && export LD_LIBRARY_PATH=/lib:/usr/lib:/usr/local/lib


clean:
	rm -rf $(BUILD_DIR) tetris.a main.o main
