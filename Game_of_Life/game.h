#ifndef GAME_H
#define GAME_H

#define WIDTH 80
#define HEIGHT 25

typedef int Field[HEIGHT][WIDTH];

void read_txt_and_fill(Field field, char *filename);
void print(const Field field);
void change(Field field);
void copy(Field new_field, Field old_field);
void delay(int milliseconds);

#endif
