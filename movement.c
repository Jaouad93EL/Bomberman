#include "header.h"

void move(player_t *p, int mouv_x, int mouv_y, player_e orientation)
{
    int x = p->position.x + mouv_x;
    int y = p->position.y + mouv_y;
    if(p->number_speed <= 0)
        return;
    if ((x >= 1 && x <= BLOCKS_HEIGHT - 1) && (y >= 1 && y <= BLOCKS_WIDTH - 1)) {
        if (map_array[x][y] == EMPTY || map_array[x][y] == BONUS) {
            p->position.x = x;
            p->position.y = y;
            p->number_speed--;
            p->orientation = orientation;
            if (map_array[x][y] == BONUS) {
                map_array[x][y] = EMPTY;
                affect_bonus(p);
            }
        }
    }
}

position_t *get_next_direction_player(player_e orientation)
{
    position_t *posi = malloc(sizeof(position_t));

    switch (orientation) {
        case UP:
            posi->x = -1;
            posi->y = 0;
            break;
        case DOWN:
            posi->x = 1;
            posi->y = 0;
            break;
        case LEFT:
            posi->x = 0;
            posi->y = -1;
            break;
        case RIGHT:
            posi->x = 0;
            posi->y = 1;
            break;
        default:
            break;
    }
    return (posi);
}