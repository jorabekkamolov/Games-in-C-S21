#include "../../brick_game/tetris/tetris.h"
int game_tetris(GameTet* game, WINDOW* game_field, WINDOW* new_figure,
                WINDOW* win) {
  int temp_new;
  while (game_over(game)) {
    // wclear(win);
    temp_new = random_num();
    while (check_to_temp(game)) {
      temp_one(game, game_field, new_figure, win, temp_new);
      temp_two(game, game_field, new_figure, win, temp_new);
      if (!check_down(game)) {
        break;
      }
    }
    append_figure(game);
    free(game->figure);
    game->figure = create_tetfigure(0, 4, temp_new);
    filter_filed(game);
  }
  int x, y;
  getmaxyx(game_field, y, x);
  int i;
  int text_x = x / 2;
  int text_y = y / 2 - 2;
  while (1) {
    wclear(game_field);
    wclear(new_figure);
    wclear(win);
    // wattron(game_field, COLOR_PAIR(2));
    mvwprintw(game_field, text_y, text_x - strlen("---GAME OVER---") / 2,
              "---GAME OVER---");
    // wattroff(game_field, COLOR_PAIR(2));
    mvwprintw(game_field, text_y + 2, text_x - strlen("---NEW GAME---") / 2,
              "---NEW GAME---");
    mvwprintw(game_field, text_y + 3, text_x - strlen("---PRESS [n]---") / 2,
              "---PRESS [n]---");
    mvwprintw(game_field, text_y + 5, text_x - strlen("---EXIT---") / 2,
              "---EXIT---");
    mvwprintw(game_field, text_y + 6, text_x - strlen("---PREES [q]---") / 2,
              "---PREES [q]---");
    wrefresh(game_field);
    wrefresh(new_figure);
    wrefresh(win);
    int pause_c = wgetch(game_field);
    if (pause_c == 'q') {
      i = 0;
      break;
    } else if (pause_c == 'n') {
      i = 1;
      break;
    }
  }
  return i;
}
