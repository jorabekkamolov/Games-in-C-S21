#include <stdio.h>

void ping_pong(int a, int b, int c, int d) {
    int x = 80;
    int y = 25;
    char table[y][x];

    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            table[i][j] = ' ';
        }
    }
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            if (j == 0 || i == 0 || i == y - 1 || j == x - 1) {
                table[i][j] = '*';
            }
        }
    }
    for (int i = a; i < a + 3; i++) {
        table[i][1] = '|';
    }
    for (int i = b; i < b + 3; i++) {
        table[i][78] = '|';
    }
    table[d][c] = 'o';
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            printf("%c", table[i][j]);
        }
        printf("\n");
    }
}
int main() {
    int left = 10;
    int right = 10;
    int n_x = 40;
    int n_y = 12;
    int o_x;
    int o_y;
    int temp_y = 1;
    int temp_x = 1;
    char s;

    while (1) {
        scanf("%c", &s);
        if (s == 'z') {
            if (left == 21) {
                continue;
            }
            left += 1;
        }
        else if(s == 'q'){
          return 1;
        }
        else if (s == 'a') {
            if (left == 1) {
                continue;
            }
            left -= 1;
        }
        else if (s == 'm') {
            if (right == 21) {
                continue;
            }
            right += 1;
        }
        else if (s == 'k') {
            if (right == 1) {
                continue;
            }
            right -= 1;
        }
        else if (n_y == 23 && n_x > o_x && n_y > o_y) {
            temp_y = -1;
            temp_x = 1;
        }
        else if (n_y == 1 && n_x < o_x && n_y < o_y) {
            temp_y = 1;
            temp_x = -1;
        }
        else if (n_y == 1 && n_x > o_x && n_y < o_y) {
            temp_y = 1;
            temp_x = 1;
        }
        else if (n_y == 23 && n_x < o_x && n_y > o_y) {
            temp_y = -1;
            temp_x = -1;
        }
        else if (n_x == 77 &&
            (n_y == right || n_y == right + 1 || n_y == right + 2 || n_y == right + 3 || n_y == right - 1)) {
            temp_x = -1;
            temp_y = -1;
        }
        else if (n_x == 2 &&
            (n_y == left || n_y == left + 1 || n_y == left + 2 || n_y == left + 3 || n_y == left - 1)) {
            printf("%d", n_y);
            printf("%d", left);
            temp_x = 1;
            temp_y = 1;
        }
        else if (n_x == 79) {
            n_x = 40;
            n_y = 12;
        }
        else if (n_x == 1) {
            n_x = 40;
            n_y = 12;
        }
        o_x = n_x;
        o_y = n_y;
        n_x = n_x + temp_x;
        n_y = n_y + temp_y;
        if (s == ' ') {
            ping_pong(left, right, n_x, n_y);
        }

        ping_pong(left, right, n_x, n_y);
    }
}
