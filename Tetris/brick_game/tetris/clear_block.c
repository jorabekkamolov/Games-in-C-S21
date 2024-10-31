#include "tetris.h"

void clear_block(GameTet* game) {
  for (int i = 0; i < game->field->height; i++) {
    for (int j = 0; j < game->field->width; j++) {
      if (game->field->field[i][j] == 1) {
        game->field->field[i][j] = 0;
      }
    }
  }
}
