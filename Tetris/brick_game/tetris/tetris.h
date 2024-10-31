#ifndef TETRIS_H
#define TETRIS_H

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
// #include <sys/time.h>
// #include <sys/types.h>
#include <string.h>
#include <time.h>
// #include <unistd.h>

#define HEIGHT 20
#define WIDTH 10

typedef struct {
  int shape[4][4];
} Tetromino;

extern Tetromino tetrominos[7];

typedef struct TetField {
  int height;
  int width;
  int** field;
} TetField;

typedef struct TetFigure {
  int y;
  int x;
  int index;
  int block[4][4];
} TetFigure;

typedef struct GameTet {
  TetField* field;
  TetFigure* figure;
  int score;
  int temp_score;
  int speed;
  int level;
  int record_score;
} GameTet;

// brick_game

Tetromino get_random_tetromino(int* i, int index);
TetField* create_tetfield(int height, int width);
TetFigure* create_tetfigure(int y, int x, int i);
GameTet* create_game(int height, int width, int y, int x, int i);
void free_tetfield(TetField* field);
void free_game(GameTet* game);

int game_over(GameTet* game);
int check_down(GameTet* game);
void append_figure(GameTet* game);
int check_right(GameTet* game);
int check_left(GameTet* game);
void block_reverse(GameTet* game);
void block_reverse_4(GameTet* game);
int check_right_block(GameTet* game);
int check_left_block(GameTet* game);
void clear_block(GameTet* game);
void draw_figure(GameTet* game);
void down_figures(GameTet* game, int y);
void filter_filed(GameTet* game);
int check_to_temp(GameTet* game);
int random_num();
Tetromino get_tetromino(int index);

// tetris

// gui

void draw_field(GameTet* game, WINDOW* game_field, WINDOW* new_figure,
                WINDOW* win, int temp);
void temp_one(GameTet* game, WINDOW* game_field, WINDOW* new_figure,
              WINDOW* win, int temp);
void down(GameTet* game);
void right(GameTet* game);
void left(GameTet* game);
void temp_two(GameTet* game, WINDOW* game_field, WINDOW* new_figure,
              WINDOW* win, int temp);
int game_tetris(GameTet* game, WINDOW* game_field, WINDOW* new_figure,
                WINDOW* win);

// tetris

#endif
