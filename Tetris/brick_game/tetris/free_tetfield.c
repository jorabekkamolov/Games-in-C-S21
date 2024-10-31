#include "tetris.h"

void free_tetfield(TetField* field) {
  for (int i = 0; i < field->height; i++) {
    free(field->field[i]);
  }
  free(field->field);
  free(field);
}
