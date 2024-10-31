#include "tetris.h"

void down_figures(GameTet* game, int y) {
  for (int i = y; i > 1; i--) {
    for (int j = 1; j < WIDTH; j++) {
      if (game->field->field[i][j]) {
        game->field->field[i + 1][j] = game->field->field[i][j];
        game->field->field[i][j] = 0;
      }
    }
  }
}
