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

// 优先级 胡>碰杠>吃
typedef enum {
    wait_Hu,
    wait_Peng,
    wait_Gang,
    wait_Chi,
} Wait_type;

typedef struct {
    int suit;
    int value;
    bool is_red;
} Tile;

typedef struct {
    Tile waited_tile;
    Wait_type type;
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
    WaitedTile waited_tiles[20];
} Player;

typedef struct {
    int player_id;
    Wait_type action_type;
    Tile* action_tile;
} Action;
#endif //COMMON_H