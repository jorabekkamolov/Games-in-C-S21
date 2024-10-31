#include "tetris.h"

int check_to_temp(GameTet* game) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (game->figure->block[i][j] == 1) {
        int new_y = game->figure->y + i + 1;
        if (new_y > HEIGHT) {
          return 0;
        }
      }
    }
  }
  return 1;
}
