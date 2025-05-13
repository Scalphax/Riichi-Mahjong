//
// Created by Scalphax on 25-5-12.
//

#include "../include/ting_check.h"

#include <stdlib.h>
#include <string.h>

bool check_ting(Player* player) {
    // 4+1型
    int shunzi = 0;
    int kezi = 0;
    for (int waited_tile_num = 0; waited_tile_num < player->waited_tiles_amount; waited_tile_num++) {
        Tile* check_list[player->tiles_amount+1];
        memcpy(check_list, player->tiles,sizeof(Tile));
        check_list[player->tiles_amount] = &player->waited_tiles[waited_tile_num].waited_tile;
        qsort(check_list, player->tiles_amount+1, sizeof(Tile*), compare);
        for (int check_tile_num = 0; check_tile_num < player->tiles_amount+1; check_tile_num++) {
            // 先刻zi
            if (if_tile_empty(check_list[check_tile_num])) {
                continue;
            }
            if (check_tile_num > player->tiles_amount-1) {
                continue;
            }
            if (if_equal(check_list[check_tile_num],check_list[check_tile_num+1],0)&&if_equal(check_list[check_tile_num+1],check_list[check_tile_num+2], 0)) {

            }
        }
    }
}


