//
// Created by Scalphax on 25-5-8.
//
#include "../include/checks.h"
#include "../include/game.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

int check_action(Player* players_list[],const Tile* discarded_tile,Action actions[], Player* curren_player) {
    int action_index = 0;
    for (int player_num = 0; player_num < 4; player_num++) {
        if (players_list[player_num] == curren_player) {
            continue;
        }
        for (int waited_tile_num = 0; waited_tile_num < players_list[player_num]->waited_tiles_amount; waited_tile_num++ ) {
            if (if_equal(discarded_tile, &players_list[player_num]->waited_tiles[waited_tile_num].waited_tile, 0)) {
                actions[action_index] = (Action) {.player_id = player_num,
                    .action_type = players_list[player_num]->waited_tiles[waited_tile_num].type,
                    .action_tile = &players_list[player_num]->waited_tiles[waited_tile_num].waited_tile};
                action_index++;
            }
        }
    }
    return action_index;
}

void print_wait(const Player* player, const int i) {
    printf("[");
    print_tile(&player->waited_tiles[i].waited_tile);
    printf(", %d]",player->waited_tiles[i].type);
}

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
    for (int i = 0; i + 1 < player->tiles_amount; i++) {
        // // 防止越界
        // if (i+2 >= player->tiles_amount) {
        //     break;
        // }
        // 检测吃
        if (player->tiles[i] -> suit < 3) {
            // 找到同样牌的最后一张
            if (if_equal(player->tiles[i],player->tiles[i+1],0)) {
                goto skip_to_pg;
            }
            // 检测相邻吃
            if (if_equal(player->tiles[i], player->tiles[i+1], 1)) {
                if (player->tiles[i]->value > 1) {
                    player -> waited_tiles[player->waited_tiles_amount] = (WaitedTile) {
                        .waited_tile = {
                            .suit = player->tiles[i]->suit,
                            .value = player->tiles[i]->value-1,
                            .is_red = false},
                            .type = wait_Chi
                        };
                    print_wait(player, player->waited_tiles_amount);
                    player->waited_tiles_amount++;
                }
                if (player->tiles[i]->value < 8) {
                    player -> waited_tiles[player->waited_tiles_amount] = (WaitedTile) {
                        .waited_tile = {
                            .suit = player->tiles[i]->suit,
                            .value = player->tiles[i]->value+2,
                            .is_red = false},
                            .type = wait_Chi
                    };
                    print_wait(player, player->waited_tiles_amount);
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
                        .type = wait_Chi
                        };
                    print_wait(player, player->waited_tiles_amount);
                    player->waited_tiles_amount++;
                    break;
                }
            }
        }
        // 检测碰杠
        skip_to_pg:
        if (if_equal(player->tiles[i], player->tiles[i+1], 0)) {
            if (i+2 < player->tiles_amount) {
                if (if_equal(player->tiles[i+1], player->tiles[i+2], 0)) {
                    player->waited_tiles[player->waited_tiles_amount] = (WaitedTile) {
                        .waited_tile = *player->tiles[i],
                        .type = wait_Gang
                    };
                    print_wait(player, player->waited_tiles_amount);
                    player->waited_tiles_amount++;
                    continue;
                }
            }
            player->waited_tiles[player->waited_tiles_amount] = (WaitedTile) {
                .waited_tile = *player->tiles[i],
                .type = wait_Peng
            };
            print_wait(player, player->waited_tiles_amount);
            player->waited_tiles_amount++;
        }
    }
}