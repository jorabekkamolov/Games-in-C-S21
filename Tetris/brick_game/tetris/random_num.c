#include "tetris.h"

int random_num() {
  srand(time(NULL));
  int index = rand() % 7;
  return index;
}
