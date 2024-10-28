#define _XOPEN_SOURCE 500

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "game.h"

void read_txt_and_fill(Field field, char *filename) {
    FILE *file;
    file = fopen(filename, "r");
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            fscanf(file, "%d", &field[i][j]);
        }
    }
    fclose(file);
}

void print(const Field field) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (field[i][j] == 1) {
                printf("#");
            } else {
                printf("\'");
            }
        }
        printf("\n");
    }
}

int get_x(int i) { return (HEIGHT + i) % HEIGHT; }

int get_y(int j) { return (WIDTH + j) % WIDTH; }

void change(Field field) {
    Field old_field;
    copy(field, old_field);

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            int count = 0;
            count += old_field[get_x(i - 1)][get_y(j - 1)];
            count += old_field[get_x(i - 1)][get_y(j)];
            count += old_field[get_x(i - 1)][get_y(j + 1)];
            count += old_field[get_x(i)][get_y(j - 1)];
            count += old_field[get_x(i)][get_y(j + 1)];
            count += old_field[get_x(i + 1)][get_y(j - 1)];
            count += old_field[get_x(i + 1)][get_y(j)];
            count += old_field[get_x(i + 1)][get_y(j + 1)];

            if (old_field[i][j] == 0 && count == 3) {
                field[i][j] = 1;
            } else if (count < 2 || count > 3) {
                field[i][j] = 0;
            } else {
                field[i][j] = old_field[i][j];
            }
        }
    }
}

void copy(Field new_field, Field old_field) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            old_field[i][j] = new_field[i][j];
        }
    }
}

void delay(int milliseconds) { usleep(milliseconds * 1000); }
