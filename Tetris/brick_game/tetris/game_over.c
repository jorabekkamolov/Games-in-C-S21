#include "tetris.h"

int game_over(GameTet* game) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (game->figure->block[i][j]) {
        int new_y = game->figure->y + i + 1;
        if (game->field->field[new_y][game->figure->x + j]) {
          return 0;
        }
      }
    }
  }
  return 1;
}
// int game_over(GameTet* game) {
//   for (int i = 0; i < 4; i++) {
//     for (int j = 0; j < 4; j++) {
//       if (game->figure->block[i][j]) {
//         int new_y = game->figure->y + i + 1;
//         if (new_y >= game->field->height ||
//             game->field->field[new_y][game->figure->x + j] == 1) {
//           return 1;
//         }
//       }
//     }
//   }
//   return 0;
// }
