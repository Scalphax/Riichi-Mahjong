//
// Created by Scalphax on 25-5-8.
//

#ifndef COMMON_H
#define COMMON_H
#include <stdbool.h>
enum Suit {
    Wan,
    Dots,
    Bamboo,
    Words
};
enum WordType {
    Dong,
    Nan,
    Xi,
    Bei,
    Bai,
    Fa,
    Zhong
};

typedef struct {
    int suit;
    int value;
    bool is_red;
} Tile;

/*
   type = 0 听牌
        = 1 吃
        = 2 碰
        = 3 杠
*/

typedef struct {
    Tile waited_tile;
    int type;
} WaitedTile;

typedef struct {
    char name[100];
    bool is_ting;
    int fulu_start;
    enum WordType wind;
    int tiles_amount;
    int score;
    int discard_amount;
    int waited_tiles_amount;
    Tile* tiles[18];
    Tile* discarded[40];
    WaitedTile waited_tiles[10];
} Player;
#endif //COMMON_H