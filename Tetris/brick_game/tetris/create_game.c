#include "tetris.h"

GameTet* create_game(int height, int width, int y, int x, int i) {
  GameTet* gamet = (GameTet*)malloc(sizeof(GameTet));
  if (gamet == NULL) {
    fprintf(stderr, "Memory allocation failed for GameTet\n");
    exit(EXIT_FAILURE);
  }

  gamet->field = create_tetfield(height, width);
  gamet->figure = create_tetfigure(y, x, i);
  gamet->score = 0;
  gamet->temp_score = 600;
  gamet->speed = 10;
  gamet->level = 0;
  gamet->record_score = 0;
  return gamet;
}
