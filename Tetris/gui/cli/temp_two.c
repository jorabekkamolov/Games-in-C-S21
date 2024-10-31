#include "../../brick_game/tetris/tetris.h"

void temp_two(GameTet* game, WINDOW* game_field, WINDOW* new_figure,
              WINDOW* win, int temp) {
  int c;
  for (int i = 0; i < 2; i++) {
    halfdelay(4);
    c = wgetch(game_field);
    if (c == KEY_RIGHT) {
      if (check_right(game)) {
        clear_block(game);
        right(game);
        draw_figure(game);
        draw_field(game, game_field, new_figure, win, temp);
      }
    } else if (c == KEY_LEFT) {
      if (check_left(game)) {
        clear_block(game);
        left(game);
        draw_figure(game);
        draw_field(game, game_field, new_figure, win, temp);
      }
    } else if (c == ERR) {
      break;
    }
  }
}
