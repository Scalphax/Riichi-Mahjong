#include "../include/game.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//
// Created by Scalphax on 25-5-7.
//

int init(Tile wall[136]) {
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
    for (enum WordType word = Dong ; word <= Zhong ; word++) {
        for (int num = 0 ; num <= 3 ; num++) {
            wall[i].suit = Words;
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

// 牌面打印
void print_tile(const Tile* tile) {
    printf("{%d,%d,%d}",tile->suit,tile->value,tile->is_red);
}

// 随机牌山
void shuffle(Tile wall[136]) {
    srand(time(NULL));
    int k = 0;
    for (int j = 0 ; j < 136 ; j++) {
        k = rand() % (j + 1);
        const Tile temp = wall[k];
        wall[k] = wall[j];
        wall[j] = temp;
    }
}

// 抓牌
void draw(Tile* wall, int* wall_now,Tile* tiles[],int* tiles_amount) {
    tiles[*tiles_amount] = &wall[*wall_now];
    (*wall_now)++;
    (*tiles_amount)++;
}

// 大小比较
int compare(const void* a, const void* b) {
    const Tile* s1 = *(const Tile**)a;
    const Tile* s2 = *(const Tile**)b;
    if (s1 -> suit != s2 -> suit) {
        return s1 -> suit - s2 -> suit;  // 按 Suit 升序
    }
    // 若 Suit 相同，则比较 Value
    return s1 -> value - s2 -> value;  // 按 Value 升序
}

// 出牌阶段
void in_turn(Player* player) {
    printf("\n");
    for (int i = 0 ; i < player->tiles_amount-1 ; i++) {
        printf("(%d)",i+1);
        print_tile(player->tiles[i]);
    }
    printf("(%d)",player->tiles_amount);
    print_tile(player->tiles[player->tiles_amount-1]);
    printf("\n请键入要出的牌的序号,回车发送:");
    long select = player->tiles_amount - 1;
    char input[4];
    char* endptr;
    while (1) {
        fgets(input,sizeof(input),stdin);
        if (input[0] == '\n') {
            break;
        }
        long num = strtol(input, &endptr, 10);
        if (num > 0 && num <= player->tiles_amount) {
            if (endptr == input || *endptr != '\n') {
                printf("输入无效！\n");
            }
            else {
                select = num-1;
                break;
            }
        }
        else {
            printf("输入超出范围！\n");
            int ch;
            while((ch = getchar()) != '\n' && ch != EOF);
        }
    }
    // 放入弃牌堆
    player->discarded[player->discard_amount] = player->tiles[select];
    player->discard_amount++;
    player->tiles[select] = NULL;
    player->tiles_amount--;
    // 拿出的牌向前移
    for (int i = select; i < player->tiles_amount; i++) {
        player->tiles[i] = player->tiles[i+1];
    }
    player->tiles[player->tiles_amount] = NULL;
    // 排序
    qsort(player->tiles, player->tiles_amount, sizeof(Tile*), compare);
    check_waited(player);
    // todo 弃牌检测
    // if (check_action(player, player->tiles[select-1]) == 0) {
    //     player->discarded[player->discard_amount] = player->tiles[select-1];
    //     player->discard_amount++;
    // }

}

int in_game(void) {
    Tile wall[136];
    // 生成牌并洗牌
    init(wall);
    shuffle(wall);

    // 初始化玩家
    Player player1 = {"Player1",0,-1,Dong,0,25000,0,0};
    Player player2 = {"Player2",0,-1,Nan,0,25000,0,0};
    Player player3 = {"Player3",0,-1,Xi,0,25000,0,0};
    Player player4 = {"Player4",0,-1,Bei,0,25000,0,0};

    Player* players[] = {&player1,&player2,&player3,&player4};
    // 取宝牌指示牌
    Tile* dora[10];
    for (int i = 0; i < 10; i++) {
        dora[i] = &wall[126 + i];
    }

    // 发牌
    int wall_now = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 13; j++) {
            draw(wall, &wall_now, players[i]->tiles, &players[i]->tiles_amount);
        }
        // 排序
        qsort(players[i]->tiles, 13, sizeof(Tile*), compare);
    }
    // for (int i = 0 ; i < 10 ; i++) {
    //     printf("{%d,%d,%d}",dora[i]->suit,dora[i]->value,dora[i]->is_red);
    // }
    //printf("\n");
    for (int i = 0 ; i < 4 ; i++) {
        for (int j = 0 ; j < 13 ; j++) {
            print_tile(players[i]->tiles[j]);
        }
        printf("\n");
    }

    // 记录巡数
    int round = 1;
    // 从东家开始发牌
    while (1) {
        for (int i = 0 ; i < 4 ; i++) {
            if (wall_now < 136) {
                draw(wall, &wall_now, players[i]->tiles, &players[i]->tiles_amount);
                in_turn(players[i]);
            }
            else {
                goto out_of_tiles;
            }
        }
    }
    out_of_tiles:
        return 0;
}