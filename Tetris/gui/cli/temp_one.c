#include "../../brick_game/tetris/tetris.h"

void temp_one(GameTet* game, WINDOW* game_field, WINDOW* new_figure,
              WINDOW* win, int temp) {
  int c;
  while (check_down(game)) {
    halfdelay(game->speed);
    c = wgetch(game_field);

    if (c == 'p') {
      int x, y;
      getmaxyx(game_field, y, x);

      int text_x = x / 2;
      int text_y = y / 2 - 2;

      while (1) {
        wclear(game_field);
        wclear(new_figure);
        wclear(win);

        mvwprintw(game_field, text_y, text_x - strlen("---PAUSE---") / 2,
                  "---PAUSE---");
        mvwprintw(game_field, text_y + 1,
                  text_x - strlen("---PRESS [p]---") / 2, "---PRESS [p]---");
        mvwprintw(game_field, text_y + 3, text_x - strlen("---START---") / 2,
                  "---START---");
        mvwprintw(game_field, text_y + 4,
                  text_x - strlen("---PRESS [s]---") / 2, "---PRESS [s]---");
        wrefresh(game_field);
        wrefresh(new_figure);
        wrefresh(win);

        int pause_c = wgetch(game_field);
        if (pause_c == 's') {
          break;
        }
      }
      continue;
    }

    if (c == ERR) {
      clear_block(game);
      down(game);
      draw_figure(game);
      draw_field(game, game_field, new_figure, win, temp);
    } else if (c == KEY_DOWN) {
      clear_block(game);
      down(game);
      draw_figure(game);
      draw_field(game, game_field, new_figure, win, temp);
    } else if (c == KEY_RIGHT) {
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
    } else if (c == KEY_UP) {
      if (check_left_block(game) && check_right_block(game) &&
          game->figure->index != 1) {
        if (game->figure->index == 0) {
          block_reverse_4(game);
          clear_block(game);
          draw_figure(game);
          draw_field(game, game_field, new_figure, win, temp);
        } else {
          block_reverse(game);
          clear_block(game);
          draw_figure(game);
          draw_field(game, game_field, new_figure, win, temp);
        }
      }
    }
  }
}
