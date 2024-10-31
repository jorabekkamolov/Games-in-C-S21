#include "tetris.h"

void free_game(GameTet* game) {
  free_tetfield(game->field);
  free(game->figure);
  free(game);
}
