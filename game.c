#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//
// Created by Scalphax on 25-5-7.
//

enum Suit {
    Wan,
    Dots,
    Bamboo,
    Word
};

enum Word {
    Dong,
    Nan,
    Xi,
    Bei,
    Bai,
    Fa,
    Zhong
};

struct Tile {
    int suit;
    int value;
    bool is_red;
};
typedef struct Tile TILE;

int init(TILE wall[136]) {
    int i = 0;
    // 初始化数牌
    for (enum Suit suit = Wan ; suit <= Bamboo ; suit++) {
        for (int value = 1 ; value <= 9 ; value++) {
            for (int num = 0 ; num <= 3 ; num++) {
                wall[i].suit = suit;
                wall[i].value = value;
                wall[i].is_red = false;
                i++;
            }
        }
    }
    // 初始化字牌
    for (enum Word word = Dong ; word <= Zhong ; word++) {
        for (int num = 0 ; num <= 3 ; num++) {
            wall[i].suit = Word;
            wall[i].value = word;
            wall[i].is_red = false;
            i++;
        }
    }
    // 标记红宝牌
    wall[16].is_red = true;
    wall[52].is_red = true;
    wall[88].is_red = true;
    return 0;
}

void shuffle(TILE wall[136]) {
    // 随机牌山
    srand(time(NULL));
    int k = 0;
    for (int j = 0 ; j < 136 ; j++) {
        k = rand() % (j + 1);
        const TILE temp = wall[k];
        wall[k] = wall[j];
        wall[j] = temp;
    }
}

void draw(TILE* wall, int* wall_now,TILE* tiles[],int* tiles_amount) {
    tiles[*tiles_amount] = &wall[*wall_now];
    (*wall_now)++;
    (*tiles_amount)++;
}

int in_game(void) {
    TILE wall[136];
    // 生成牌并洗牌
    init(wall);
    shuffle(wall);

    // 初始化玩家
    struct Player {
        bool is_ting;
        int fulu_start;
        enum Word wind;
        int tiles_amount;
        int score;
        TILE* tiles[18];
    }player1 = {0,-1,Dong,0,25000},
    player2 = {0,-1,Nan,0,25000},
    player3 = {0,-1,Xi,0,25000},
    player4 = {0,-1,Bei,0,25000};

    struct Player* players[] = {&player1,&player2,&player3,&player4};
    //取宝牌指示牌
    TILE* dora[10];
    for (int i = 0; i < 10; i++) {
        dora[i] = &wall[126 + i];
    }

    // 发牌
    int wall_now = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 13; j++) {
            draw(wall, &wall_now, players[i]->tiles, &players[i]->tiles_amount);
        }
    }
    // for (int i = 0 ; i < 10 ; i++) {
    //     printf("{%d,%d,%d}",dora[i]->suit,dora[i]->value,dora[i]->is_red);
    // }
    // printf("\n");
    // for (int i = 0 ; i < 4 ; i++) {
    //     for (int j = 0 ; j < 13 ; j++) {
    //         printf("{%d,%d,%d}",players[i]->tiles[j]->suit,players[i]->tiles[j]->value,players[i]->tiles[j]->is_red);
    //     }
    //     printf("\n");
    // }

    // 开始游戏
    return 0;
}