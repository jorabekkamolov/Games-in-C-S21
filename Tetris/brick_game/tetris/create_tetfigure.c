#include "tetris.h"

TetFigure* create_tetfigure(int y, int x, int i) {
  TetFigure* tetfg = (TetFigure*)malloc(sizeof(TetFigure));
  if (tetfg == NULL) {
    fprintf(stderr, "Memory allocation failed for TetFigure\n");
    exit(EXIT_FAILURE);
  }
  tetfg->y = y;
  tetfg->x = x;
  int index;
  Tetromino random_tetromino = get_random_tetromino(&index, i);
  tetfg->index = index;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      tetfg->block[i][j] = random_tetromino.shape[i][j];
    }
  }
  return tetfg;
}
