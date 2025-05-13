//
// Created by Scalphax on 25-5-8.
//
#pragma once
#ifndef CHECKS_H
#define CHECKS_H
#include "common.h"
#include "game.h"
#endif //CHECKS_H

//int check_action(Player* player,Tile* discard);
bool if_equal(const Tile* a, const Tile* b, const int diff);
void check_waited(Player* player);
int check_action(Player* players_list[], const Tile* discarded_tile,Action actions[], const Player* curren_player);
bool if_empty (const WaitedTile* target_tile);
bool if_tile_empty (const Tile* target_tile);