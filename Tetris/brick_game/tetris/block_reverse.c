#include "tetris.h"

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
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (game->figure->block[i][j]) {
        int new_x = game->figure->x + j + 1;
        if (new_x == WIDTH) {
          game->figure->x -= 1;
        } else if (new_x - 1 == 0) {
          game->figure->x += 1;
        }
      }
    }
  }
}
