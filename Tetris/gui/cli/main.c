#include "../../brick_game/tetris/tetris.h"

#define HEIGHT_START 30
#define WIDTH_START 30

int get_high_score() {
  int high_score = 0;
  FILE* file = fopen("gui/cli/db.txt", "r");

  if (file != NULL) {
    fscanf(file, "%d", &high_score);
    fclose(file);
  } else {
    printf("Rekord fayli topilmadi, yangi rekord yaratamiz.\n");
  }

  return high_score;
}

void update_high_score(int new_score) {
  FILE* file = fopen("gui/cli/db.txt", "w");

  if (file != NULL) {
    fprintf(file, "%d", new_score);
    fclose(file);
  } else {
    printf("Rekordni saqlashda xatolik yuz berdi!\n");
  }
}

int main() {
  WINDOW* game_field;
  WINDOW* new_figure;
  WINDOW* win;
  WINDOW* start_win;
  int temp;
  temp = random_num();
  GameTet* game = create_game(HEIGHT, WIDTH, 0, 4, temp);
  int offsetx, offsety;
  int row, column;
  int x_start, y_start;
  game->record_score = get_high_score();
  initscr();
  start_color();
  noecho();
  curs_set(FALSE);
  getmaxyx(stdscr, row, column);

  init_pair(2, COLOR_RED, COLOR_RED);
  init_pair(8, COLOR_YELLOW, COLOR_YELLOW);
  init_pair(5, COLOR_GREEN, COLOR_GREEN);
  init_pair(4, COLOR_BLUE, COLOR_BLACK);
  init_pair(3, COLOR_MAGENTA, COLOR_MAGENTA);
  init_pair(6, COLOR_CYAN, COLOR_CYAN);
  init_pair(7, COLOR_WHITE, COLOR_YELLOW);
  init_pair(10, COLOR_BLUE, COLOR_WHITE);

  init_pair(11, COLOR_RED, COLOR_BLACK);
  init_pair(12, COLOR_YELLOW, COLOR_BLACK);
  init_pair(13, COLOR_GREEN, COLOR_BLACK);
  init_pair(14, COLOR_CYAN, COLOR_BLACK);
  init_pair(15, COLOR_MAGENTA, COLOR_BLACK);

  offsetx = (column - WIDTH * 4) / 2;
  offsety = (row - HEIGHT * 2) / 2;

  game_field = newwin(HEIGHT * 2, WIDTH * 4, offsety, offsetx);

  int new_figure_width = WIDTH * 2;
  int new_figure_height = HEIGHT * 2 / 3;
  int new_figure_offsetx = offsetx + WIDTH * 4 + 2;
  int new_figure_offsety = offsety;

  new_figure = newwin(new_figure_height, new_figure_width, new_figure_offsety,
                      new_figure_offsetx);

  int win_width = WIDTH * 2;
  int win_height = (HEIGHT * 2 / 3) + 14;
  int win_offsetx = offsetx + WIDTH * 4 + 2;
  int win_offsety = new_figure_offsety + new_figure_height;

  win = newwin(win_height, win_width, win_offsety, win_offsetx);

  x_start = (column - WIDTH_START) / 2;
  y_start = (row - HEIGHT_START) / 2;

  start_win = newwin(HEIGHT_START, WIDTH_START, y_start, x_start);

  keypad(game_field, TRUE);
  int c;
  int i = 3;
  while (1) {
    if (i == 3) {
      int x, y;
      getmaxyx(start_win, y, x);
      int text_x = x / 2;
      int text_y = y / 2 - 2;
      mvwprintw(start_win, text_y, text_x - strlen("---WELCOM TETRIS---") / 2,
                "---WELCOM TETRIS---");
      mvwprintw(start_win, text_y + 2, text_x - strlen("---GAME---") / 2,
                "---GAME---");
      mvwprintw(start_win, text_y + 3, text_x - strlen("---PRESS [g]---") / 2,
                "---PRESS [g]---");
      mvwprintw(start_win, text_y + 5, text_x - strlen("---EXIT---") / 2,
                "---EXIT---");
      mvwprintw(start_win, text_y + 6, text_x - strlen("---PREES [q]---") / 2,
                "---PREES [q]---");
      int temp = 0;
      for (int i = game->record_score; i != 0; i /= 10) {
        temp++;
      }
      mvwprintw(start_win, text_y + 8, text_x - strlen("---YOU RECORD ---") / 2,
                "---YOU RECORD---");

      mvwprintw(start_win, text_y + 9, text_x - (strlen("------") + temp) / 2,
                "---%d---", game->record_score);

      c = wgetch(start_win);
      wclear(start_win);
      wrefresh(start_win);
    }
    if (c == 'g') {
      i = game_tetris(game, game_field, new_figure, win);
      if (game->score > game->record_score) {
        game->record_score = game->score;
        update_high_score(game->record_score);
      }
    } else if (c == 'q') {
      break;
    }
    if (i == 0) {
      break;
    } else if (i == 1) {
      free_game(game);
      temp = random_num();

      game = create_game(HEIGHT, WIDTH, 0, 4, temp);
      game->record_score = get_high_score();
    }
  }

  delwin(game_field);
  delwin(new_figure);
  delwin(win);
  delwin(start_win);
  endwin();
  free_game(game);
  return 0;
}
