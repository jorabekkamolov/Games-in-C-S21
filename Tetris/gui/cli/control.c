#include "../../brick_game/tetris/tetris.h"

void down(GameTet* game) { game->figure->y += 1; }
void right(GameTet* game) { game->figure->x += 1; }
void left(GameTet* game) { game->figure->x -= 1; }
