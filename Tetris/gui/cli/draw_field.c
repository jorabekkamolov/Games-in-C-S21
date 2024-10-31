#include "../../brick_game/tetris/tetris.h"

void draw_field(GameTet* game, WINDOW* game_field, WINDOW* new_figure,
                WINDOW* win, int temp) {
  wclear(game_field);
  wclear(new_figure);
  wclear(win);
  int block_width = 4;
  int block_height = 2;
  Tetromino figure = get_tetromino(temp);

  box(new_figure, 0, 0);
  int y = 4, x = 2;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (figure.shape[i][j]) {
        wattron(new_figure, COLOR_PAIR(figure.shape[i][j]));
        if (figure.shape[i][j] == 3) {
          x += 4;
        } else if (figure.shape[i][j] != 2) {
          x += 2;
        }
        for (int h = 0; h < block_height; h++) {
          for (int w = 0; w < block_width; w++) {
            mvwaddch(new_figure, i * block_height + y + h,
                     j * block_width + w + x, ACS_CKBOARD);
          }
        }
        x = 2;
        wattroff(new_figure, COLOR_PAIR(figure.shape[i][j]));
      }
    }
  }
  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      if (i == 0 || i == HEIGHT - 1 || j == 0 || j == WIDTH - 1) {
        for (int h = 0; h < block_height; h++) {
          for (int w = 0; w < block_width; w++) {
            mvwaddch(game_field, i * block_height + h, j * block_width + w,
                     ACS_CKBOARD);
          }
        }
      } else if (game->field->field[i][j]) {
        wattron(game_field, COLOR_PAIR((game->field->field[i][j] == 1)
                                           ? game->figure->index + 2
                                           : game->field->field[i][j]));
        for (int h = 0; h < block_height; h++) {
          for (int w = 0; w < block_width; w++) {
            mvwaddch(game_field, i * block_height + h, j * block_width + w,
                     ACS_CKBOARD);
          }
        }
        wattroff(game_field, COLOR_PAIR((game->field->field[i][j] == 1)
                                            ? game->figure->index + 2
                                            : game->field->field[i][j]));
      } else {
        for (int h = 0; h < block_height; h++) {
          for (int w = 0; w < block_width; w++) {
            mvwaddch(game_field, i * block_height + h, j * block_width + w,
                     ' ');
          }
        }
      }
    }
  }
  if (game->score >= game->temp_score) {
    if (game->speed != 1) {
      game->speed -= 1;
    }
    if (game->level != 10) {
      game->level += 1;
    }
    game->temp_score += 600;
  }
  wclear(win);
  box(win, 0, 0);
  int start_x = 5;
  int a = 11, b = 11;

  wattron(win, COLOR_PAIR(15));
  mvwprintw(win, 2, start_x, "LEVEL:");
  wattroff(win, COLOR_PAIR(15));
  wattron(win, COLOR_PAIR(11));
  mvwprintw(win, 2, start_x + 8, "%d", game->level);
  wattroff(win, COLOR_PAIR(11));
  if (game->score > game->record_score) {
    a = 13;
    b = 15;
  }
  wattron(win, COLOR_PAIR(15));
  mvwprintw(win, 4, start_x, "SCORE:");
  wattroff(win, COLOR_PAIR(12));
  wattron(win, COLOR_PAIR(a));
  mvwprintw(win, 4, start_x + 8, "%d", game->score);
  wattroff(win, COLOR_PAIR(b));

  wattron(win, COLOR_PAIR(15));
  mvwprintw(win, 6, start_x, "SPEED:");
  wattroff(win, COLOR_PAIR(15));
  wattron(win, COLOR_PAIR(11));
  mvwprintw(win, 6, start_x + 8, "%d", game->speed);
  wattroff(win, COLOR_PAIR(11));

  wattron(win, COLOR_PAIR(15));
  mvwprintw(win, 8, start_x, "RECORD:");
  wattroff(win, COLOR_PAIR(15));
  wattron(win, COLOR_PAIR(11));
  if (game->score > game->record_score) {
    mvwprintw(win, 8, start_x + 8, "%d", game->score);
  } else {
    mvwprintw(win, 8, start_x + 8, "%d", game->record_score);
  }
  wattroff(win, COLOR_PAIR(11));

  wrefresh(win);
  wrefresh(game_field);
  wrefresh(new_figure);
}
