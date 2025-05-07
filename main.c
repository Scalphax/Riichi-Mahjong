//File game.c

#include <stdio.h>

void in_game(void);

int main(void) {
    printf("Press Enter to start a game.\n");
    while (getchar() != '\n')
        ;
    in_game();
}

