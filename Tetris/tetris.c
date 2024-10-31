#include "tetris.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

Tetromino get_random_tetromino(int* i) {
  int index = rand() % 7;
  *(i) = index;
  return tetrominos[index];
}

char timed_getchar(int timeout_seconds) {
  fd_set set;
  struct timeval timeout;
  int rv;
  char c = ' ';

  FD_ZERO(&set);
  FD_SET(STDIN_FILENO, &set);

  timeout.tv_sec = timeout_seconds;
  timeout.tv_usec = 0;

  rv = select(1, &set, NULL, NULL, &timeout);

  if (rv == -1) {
    perror("select");
    exit(EXIT_FAILURE);
  } else if (rv == 0) {
  } else {
    c = getchar();
  }

  return c;
}

TetField* create_tetfield(int height, int width) {
  TetField* tetf = (TetField*)malloc(sizeof(TetField));
  if (tetf == NULL) {
    fprintf(stderr, "Memory allocation failed for TetField\n");
    exit(EXIT_FAILURE);
  }

  tetf->height = height;
  tetf->width = width;
  tetf->field = (int**)malloc(sizeof(int*) * height);
  if (tetf->field == NULL) {
    fprintf(stderr, "Memory allocation failed for TetField rows\n");
    free(tetf);
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < height; i++) {
    tetf->field[i] = (int*)malloc(sizeof(int) * width);
    if (tetf->field[i] == NULL) {
      fprintf(stderr, "Memory allocation failed for TetField row %d\n", i);
      for (int j = 0; j < i; j++) {
        free(tetf->field[j]);
      }
      free(tetf->field);
      free(tetf);
      exit(EXIT_FAILURE);
    }
    for (int j = 0; j < width; j++) {
      tetf->field[i][j] = 0;
    }
  }
  return tetf;
}

TetFigure* create_tetfigure(int y, int x) {
  TetFigure* tetfg = (TetFigure*)malloc(sizeof(TetFigure));
  if (tetfg == NULL) {
    fprintf(stderr, "Memory allocation failed for TetFigure\n");
    exit(EXIT_FAILURE);
  }
  tetfg->y = y;
  tetfg->x = x;
  int index;
  Tetromino random_tetromino = get_random_tetromino(&index);
  tetfg->index = index;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      tetfg->block[i][j] = random_tetromino.shape[i][j];
    }
  }
  return tetfg;
}

GameTet* create_game(int height, int width, int y, int x) {
  GameTet* gamet = (GameTet*)malloc(sizeof(GameTet));
  if (gamet == NULL) {
    fprintf(stderr, "Memory allocation failed for GameTet\n");
    exit(EXIT_FAILURE);
  }

  gamet->field = create_tetfield(height, width);
  gamet->figure = create_tetfigure(y, x);
  return gamet;
}

void print_tetfield(TetField* field) {
  for (int i = 0; i < field->height; i++) {
    for (int j = 0; j < field->width; j++) {
      printf("%d ", field->field[i][j]);
    }
    printf("\n");
  }
}

void free_tetfield(TetField* field) {
  for (int i = 0; i < field->height; i++) {
    free(field->field[i]);
  }
  free(field->field);
  free(field);
}

void free_game(GameTet* game) {
  free_tetfield(game->field);
  free(game->figure);
  free(game);
}

int game_over(GameTet* game) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (game->figure->block[i][j]) {
        int new_y = game->figure->y + i + 1;
        if (new_y >= game->field->height ||
            game->field->field[new_y][game->figure->x + j] == 1) {
          return 1;
        }
      }
    }
  }
  return 0;
}

int figure_ground(GameTet* game) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (game->figure->block[i][j]) {
        int new_y = game->figure->y + i + 1;
        if (new_y >= HEIGHT ||
            game->field->field[new_y][game->figure->x + j] == 1) {
          return 1;
        }
      }
    }
  }
  return 0;
}

void clear_block(GameTet* game) {
  for (int i = 0; i < game->field->height; i++) {
    for (int j = 0; j < game->field->width; j++) {
      if (game->field->field[i][j] == 2) {
        game->field->field[i][j] = 0;
      }
    }
  }
}

void move_down(GameTet* game) { game->figure->y += 1; }

void draw_figure(GameTet* game) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (game->figure->block[i][j]) {
        game->field->field[game->figure->y + i][game->figure->x + j] = 2;
      }
    }
  }
}

void append_field(GameTet* game) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (game->figure->block[i][j]) {
        game->field->field[game->figure->y + i][game->figure->x + j] = 1;
      }
    }
  }
}

int check_left(GameTet* game) {
  for (int i = 0; i < 4; i++) {
    int new_y = game->figure->y + i;
    for (int j = 0; j < 4; j++) {
      if (game->figure->block[i][j]) {
        int new_x = game->figure->x + j;
        if (new_x < 0 || game->field->field[new_y][new_x]) {
          return 0;
        }
        break;
      }
    }
  }
  return 1;
}

int check_right(GameTet* game) {
  for (int i = 0; i < 4; i++) {
    int new_y = game->figure->y + i;
    for (int j = 0; j < 4; j++) {
      if (game->figure->block[i][j]) {
        int new_x = game->figure->x + j;
        if (new_x > game->field->width || game->field->field[new_y][new_x]) {
          return 0;
        }
      }
    }
  }
  return 1;
}

void move_left(GameTet* game) { game->figure->x -= 1; }

void move_right(GameTet* game) { game->figure->x += 1; }

void block_reverse(GameTet* game) {
  int block[3][3];
  for (int i = 0; i < 3; i++) {
    for (int j = 0, k = 2; j < 3; j++, k--) {
      block[i][j] = game->figure->block[k][i];
    }
  }
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      game->figure->block[i][j] = block[i][j];
    }
  }
}

void block_reverse_4(GameTet* game) {
  int block[4][4];
  for (int i = 0; i < 4; i++) {
    for (int j = 0, k = 3; j < 4; j++, k--) {
      block[i][j] = game->figure->block[k][i];
    }
  }
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      game->figure->block[i][j] = block[i][j];
    }
  }
}

int main() {
  srand(time(0));
  int c;
  GameTet* game = create_game(HEIGHT, WIDTH, 0, 4);
  while (!game_over(game)) {
    while (!figure_ground(game)) {
      c = timed_getchar(1);
      system("clear");
      if (c == ' ') {
        clear_block(game);
        move_down(game);
        draw_figure(game);
        print_tetfield(game->field);
        printf("\n");
      } else if (c == 'a') {
        clear_block(game);
        move_left(game);
        if (check_left(game)) {
          draw_figure(game);
          print_tetfield(game->field);
          printf("\n");
        } else {
          game->figure->x += 1;
        }
      } else if (c == 'd') {
        clear_block(game);
        move_right(game);
        if (check_right(game)) {
          draw_figure(game);
          print_tetfield(game->field);
          printf("\n");
        } else {
          game->figure->x -= 1;
        }
      } else if (c == 's') {
        clear_block(game);
        move_down(game);
        if (!figure_ground(game)) {
          draw_figure(game);
          print_tetfield(game->field);
          printf("\n");
        } else {
          game->figure->y -= 1;
        }
      } else if (c == 'w' && game->figure->index != 0 &&
                 game->figure->index != 1) {
        clear_block(game);
        if (check_left(game) && check_right(game)) {
          block_reverse(game);
          draw_figure(game);
          print_tetfield(game->field);
          printf("\n");
        }
      }
    }
    append_field(game);
    free(game->figure);
    game->figure = create_tetfigure(0, 4);
  }
  printf("Game Over\n");
  print_tetfield(game->field);
  free_game(game);

  return 0;
}

// wclear(game_field);

// box(game_field, 0, 0);
// mvwprintw(game_field, 0, 0,"%d",game->figure->x);
// wborder(game_field, '|', '|', '-', '-', '+', '+', '+', '+');
// wattron(game_field, COLOR_PAIR(1)); // Rangli kubikni yoqish
// mvwaddch(game_field, y, x, ACS_CKBOARD);
// mvwaddch(game_field, y, x+1, ACS_CKBOARD); // Kubik belgisi (ACS_CKBOARD -
// ko'k kvadrat) wattroff(game_field, COLOR_PAIR(1)); // Rangli kubikni
// o'chirish wrefresh(game_field);
