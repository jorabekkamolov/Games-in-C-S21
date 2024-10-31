#include "tetris.h"

void append_figure(GameTet* game) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (game->figure->block[i][j]) {
        game->field->field[game->figure->y + i][game->figure->x + j] =
            game->figure->block[i][j];
      }
    }
  }
  // game->field->field[39][39] = 2;
}
