#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "game.h"

char *choise(int input) {
    char *file;
    switch (input) {
        case 1:
            file = "движение.txt";
            break;
        case 2:
            file = "устойчивые.txt";
            break;
        case 3:
            file = "периодические.txt";
            break;
        case 4:
            file = "разрушение.txt";
            break;
        case 5:
            file = "ружьё.txt";
            break;
    }

    return file;
}

int main() {
    Field field;
    int input, milliseconds;

<<<<<<< HEAD
    printf("1. Движение\t2. Устойчивые\t3. Периодические\t4. Разрушение\t5. Ружьё\n");
=======
    printf("1. Стрелок\t2. Движение\n");
>>>>>>> afb093e09acbb2599e9d1500d2e1c4bdd6cb3bba
    printf("Выберите вариант:\n");
    scanf("%d", &input);
    printf("Введите задержку в миллисекундах:\n");
    scanf("%d", &milliseconds);

    read_txt_and_fill(field, choise(input));

    while (1) {
        print(field);
        change(field);
        delay(milliseconds);
        system("clear");
    }
}
