#include "header.h"

bomb_t *create_bomb(player_t *p)
{
    int x = p->position.x;
    int y = p->position.y;
    bomb_t *b = malloc(sizeof(bomb_t));

    if (p->number_bomb <= 0 || b == NULL)
        return (NULL);
    if ((x >= 1 && x <= BLOCKS_HEIGHT - 1) && (y >= 1 && y <= BLOCKS_WIDTH - 1)) {
        if (map_array[x][y] == EMPTY) {
            map_array[x][y] = BOMB;
            b->position.x = x;
            b->position.y = y;
            b->state = BOMB;
            b->player_number = p->player_number;
            b->player_scope = p->number_scope;
            b->now = 0;
            p->number_bomb--;
            return (b);
        }
    }
    return (NULL);
}

void create_red_bomb(bomb_t *b)
{
    if (map_array[b->position.x][b->position.y] == BOMB
        && b->state == BOMB) {
        map_array[b->position.x][b->position.y] = RED_BOMB;
        b->state = RED_BOMB;
    }
}

void create_explosion_bomb(bomb_t *b)
{
    element_e element_left = NONE;
    element_e element_right = NONE;
    element_e element_up = NONE;
    element_e element_down = NONE;

    if (b->state == RED_BOMB || b->state == BOMB) {
        affect_case(b->position.x, b->position.y, FIRE, 1);
        for (int value = 1; value <= b->player_scope; ++value) {
            if (element_left != BRICK)
                element_left = affect_case(b->position.x - value, b->position.y, FIRE, 0);
            if (element_right != BRICK)
                element_right = affect_case(b->position.x + value, b->position.y, FIRE, 0);
            if (element_up != BRICK)
                element_up = affect_case(b->position.x, b->position.y - value, FIRE, 0);
            if (element_down != BRICK)
                element_down = affect_case(b->position.x, b->position.y + value, FIRE, 0);
        }
        b->state = FIRE;
    }
}

void delete_explosion_bomb(bomb_t *b)
{
    if (b->state == FIRE) {
        affect_case(b->position.x, b->position.y, EMPTY, 1);
        for (int value = 1; value <= b->player_scope; ++value) {
            affect_case(b->position.x - value, b->position.y, EMPTY, 0);
            affect_case(b->position.x + value, b->position.y, EMPTY, 0);
            affect_case(b->position.x, b->position.y - value, EMPTY, 0);
            affect_case(b->position.x, b->position.y + value, EMPTY, 0);
        }
        b->state = EMPTY;
    }
}