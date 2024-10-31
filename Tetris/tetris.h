#ifndef TETRIS_H
#define TETRIS_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#define HEIGHT 20
#define WIDTH 11

typedef struct {
  int shape[4][4];
} Tetromino;

Tetromino tetrominos[7] = {
    {{{1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}},
    {{{1, 1, 0, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}},
    {{{0, 1, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}},
    {{{0, 1, 1, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}},
    {{{1, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}},
    {{{1, 1, 0, 0}, {1, 0, 0, 0}, {1, 0, 0, 0}, {0, 0, 0, 0}}},
    {{{1, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}, {0, 0, 0, 0}}}};

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
} GameTet;

Tetromino get_random_tetromino(int* i);
TetField* create_tetfield(int height, int width);
TetFigure* create_tetfigure(int y, int x);
GameTet* create_game(int height, int width, int y, int x);
void print_tetfield(TetField* field);
void free_tetfield(TetField* field);
void free_game(GameTet* game);
int game_over(GameTet* game);
int figure_ground(GameTet* game);
void clear_block(GameTet* game);
char timed_getchar(int timeout_seconds);
void move_down(GameTet* game);
void draw_figure(GameTet* game);
void append_field(GameTet* game);
int check_left(GameTet* game);
void move_left(GameTet* game);
void move_right(GameTet* game);
int check_left(GameTet* game);
void block_reverse(GameTet* game);

#endif
