//
// Created by Scalphax on 25-5-9.
//

#ifndef GAME_H
#define GAME_H
#include "common.h"
#include "checks.h"

int init(Tile wall[136]);
void print_tile(const Tile* tile);
void shuffle(Tile wall[136]);
void draw(Tile* wall, int* wall_now,Tile* tiles[],int* tiles_amount);
void in_turn(Player* player, Player* players[]);
int in_game(void);
int compare(const void* a, const void* b);

#endif //GAME_H
