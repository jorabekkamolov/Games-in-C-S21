#include "tetris.h"

int check_down(GameTet* game) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (game->figure->block[i][j]) {
        int new_y = game->figure->y + i + 1;
        if (new_y + 1 >= HEIGHT ||
            game->field->field[new_y][game->figure->x + j] > 1) {
          return 0;
        }
      }
    }
  }
  return 1;
}
