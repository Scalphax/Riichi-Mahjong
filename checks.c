//
// Created by Scalphax on 25-5-8.
//
#include "common.h"
#include "checks.h"
#include <stdbool.h>

int check_action(Player* player,Tile* discard) {
    if (0) {
        return 1;
    }
    {
        return 0;
    }
}
bool if_equal(const Tile* a, const Tile* b, const int diff) {
    if (a->suit == b->suit && a->value == b->value - diff) {
        return true;
    }
    return false;
}

// todo 吃碰杠荣检测
int check_waited(Player* player) {
    for (int i = 0; i < player->tiles_amount; i++) {
        // 检测吃
        if (player->tiles[i] -> suit < 3) {
            // 检测相邻吃
            if (i+1 > player->tiles_amount) {
                break;
            }
            if (if_equal(player->tiles[i], player->tiles[i+1], 1)) {
                if (player->tiles[i]->value < 8) {
                    player -> waited_tiles[player->waited_tiles_amount] = (WaitedTile) {
                        .waited_tile = {
                            .suit = player->tiles[i]->suit,
                            .value = player->tiles[i]->value+2,
                            .is_red = false},
                            .type = 1
                        };
                }
                if (player->tiles[i]->value > 1) {
                    player -> waited_tiles[player->waited_tiles_amount] = (WaitedTile) {
                        .waited_tile = {
                            .suit = player->tiles[i]->suit,
                            .value = player->tiles[i]->value-2,
                            .is_red = false},
                            .type = 1
                    };
                }
            }
            if (if_equal(player->tiles[i], player->tiles[i+1], 2)) {
                player->waited_tiles[player->waited_tiles_amount] = (WaitedTile) {
                    .waited_tile = {
                        .suit = player->tiles[i]->suit,
                        .value = player->tiles[i]->value+1,
                        .is_red = false},
                    };
            }
        }
    }
}

//Tile {player->tiles[i]->suit, player->tiles[i]->value+2, 0}, 1