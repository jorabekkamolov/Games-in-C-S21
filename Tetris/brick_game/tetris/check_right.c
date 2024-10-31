#include "tetris.h"

int check_right(GameTet* game) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (game->figure->block[i][j]) {
        int new_x = game->figure->x + j + 1;
        if (new_x + 2 > WIDTH ||
            game->field->field[game->figure->y + i][new_x] > 1) {
          return 0;
        }
      }
    }
  }
  return 1;
}
