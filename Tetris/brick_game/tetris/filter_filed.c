#include "tetris.h"

void filter_filed(GameTet* game) {
  int kill = 0;
  for (int i = HEIGHT - 1; i > 0; i--) {
    int temp = 0;
    for (int j = 1; j < WIDTH - 1; j++) {
      if (game->field->field[i][j]) {
        temp++;
      } else {
        break;
      }
    }
    if (temp == WIDTH - 2) {
      for (int t = 1; t < WIDTH; t++) {
        game->field->field[i][t] = 0;
      }
      down_figures(game, i - 1);
      i++;
      kill++;
    }
  }
  if (kill == 1) {
    game->score += 100;
  } else if (kill == 2) {
    game->score += 300;
  } else if (kill == 3) {
    game->score += 700;
  } else if (kill == 4) {
    game->score += 1500;
  }
}
