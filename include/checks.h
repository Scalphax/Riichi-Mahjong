//
// Created by Scalphax on 25-5-8.
//
#pragma once
#ifndef CHECKS_H
#define CHECKS_H
#include "common.h"
#endif //CHECKS_H

//int check_action(Player* player,Tile* discard);
bool if_equal(const Tile* a, const Tile* b, const int diff);
void check_waited(Player* player);
int check_action(Player* players_list[], const Tile* discarded_tile,Action actions[], Player* curren_player);