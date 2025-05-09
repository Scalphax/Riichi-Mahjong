//
// Created by Scalphax on 25-5-8.
//
#include "../include/checks.h"
#include "../include/game.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

// todo 吃重复计算(如235 去重即可)以及莫名其妙的非等牌
// todo 碰杠不生效
// int check_action(Player* player,Tile* discard) {
//     if (0) {
//         return 1;
//     }
//     {
//         return 0;
//     }
// }
bool if_equal(const Tile* a, const Tile* b, const int diff) {
    if (a->suit == b->suit && a->value == b->value - diff) {
        return true;
    }
    return false;
}

// 等吃碰杠检测
void check_waited(Player* player) {
    // 清空等牌列表
    player->waited_tiles_amount = 0;
    memset(&player->waited_tiles, 0, sizeof(player->waited_tiles));
    for (int i = 0; i < player->tiles_amount; i++) {
        // 检测吃
        if (player->tiles[i] -> suit < 3) {
            // 防止越界
            if (i+2 >= player->tiles_amount) {
                break;
            }
            // 找到同样牌的最后一张
            if (if_equal(player->tiles[i],player->tiles[i+1],0)) {
                continue;
            }
            // 检测相邻吃
            if (if_equal(player->tiles[i], player->tiles[i+1], 1)) {
                if (player->tiles[i]->value < 8) {
                    player -> waited_tiles[player->waited_tiles_amount] = (WaitedTile) {
                        .waited_tile = {
                            .suit = player->tiles[i]->suit,
                            .value = player->tiles[i]->value+2,
                            .is_red = false},
                            .type = 1
                        };
                    player->waited_tiles_amount++;
                }
                if (player->tiles[i]->value > 1) {
                    player -> waited_tiles[player->waited_tiles_amount] = (WaitedTile) {
                        .waited_tile = {
                            .suit = player->tiles[i]->suit,
                            .value = player->tiles[i]->value-2,
                            .is_red = false},
                            .type = 1
                    };
                    player->waited_tiles_amount++;
                }
            }
            // 检测夹吃
            for (int j =1 ; j < 5 ; j++) {
                if (if_equal(player->tiles[i], player->tiles[i+1], 2)) {
                    player->waited_tiles[player->waited_tiles_amount] = (WaitedTile) {
                        .waited_tile = {
                            .suit = player->tiles[i]->suit,
                            .value = player->tiles[i]->value+1,
                            .is_red = false},
                        .type = 1
                        };
                    player->waited_tiles_amount++;
                    break;
                }
            }
        }
        // 检测碰杠
        if (if_equal(player->tiles[i], player->tiles[i+1], 0)) {
            if (if_equal(player->tiles[i+1], player->tiles[i+2], 0)) {
                player->waited_tiles[player->waited_tiles_amount] = (WaitedTile) {
                    .waited_tile = *player->tiles[i],
                    .type = 3
                };
                player->waited_tiles_amount++;
                continue;
            }
            player->waited_tiles[player->waited_tiles_amount] = (WaitedTile) {
                .waited_tile = *player->tiles[i],
                .type = 2
            };
            player->waited_tiles_amount++;
        }
    }
}

//Tile {player->tiles[i]->suit, player->tiles[i]->value+2, 0}, 1