#include "tetris.h"

TetField* create_tetfield(int height, int width) {
  TetField* tetf = (TetField*)malloc(sizeof(TetField));
  if (tetf == NULL) {
    fprintf(stderr, "Memory allocation failed for TetField\n");
    exit(EXIT_FAILURE);
  }

  tetf->height = height;
  tetf->width = width;
  tetf->field = (int**)malloc(sizeof(int*) * height);
  if (tetf->field == NULL) {
    fprintf(stderr, "Memory allocation failed for TetField rows\n");
    free(tetf);
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < height; i++) {
    tetf->field[i] = (int*)malloc(sizeof(int) * width);
    if (tetf->field[i] == NULL) {
      fprintf(stderr, "Memory allocation failed for TetField row %d\n", i);
      for (int j = 0; j < i; j++) {
        free(tetf->field[j]);
      }
      free(tetf->field);
      free(tetf);
      exit(EXIT_FAILURE);
    }
    for (int j = 0; j < width; j++) {
      tetf->field[i][j] = 0;
    }
  }
  return tetf;
}
