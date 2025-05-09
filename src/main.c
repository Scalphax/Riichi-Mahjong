//File game.c

#include <stdio.h>
#include <windows.h>

void in_game(void);

int main(void) {
    setbuf(stdout,NULL);
    SetConsoleOutputCP(65001);
    printf("Press Enter to start a game.\n");
    // while (getchar() != '\n')
    //     ;
    in_game();
}

