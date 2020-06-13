#include "header.h"

void *thread_bomb(void *element_p)
{
    bomb_t *bomb = (bomb_t *) ((elmt_t *) element_p)->value;

    if(bomb == NULL)
        return (NULL);
    msleep(2000);
    create_red_bomb(bomb);
    msleep(1000);
    create_explosion_bomb(bomb);
    msleep(1000);
    delete_explosion_bomb(bomb);
    free(bomb);
    list_delete(&bomb_li, (elmt_t *) element_p);
    if (player_array[0]->capacity_bomb > player_array[0]->number_bomb)
        player_array[0]->number_bomb++;
    return (NULL);
}

void *thread_bomb_now(void *element_p)
{
    bomb_t *bomb = (bomb_t *) ((elmt_t *) element_p)->value;

    if(bomb == NULL)
        return (NULL);
    create_explosion_bomb(bomb);
    msleep(1000);
    delete_explosion_bomb(bomb);
    return (NULL);
}

void *thread_bonus(void *element_p)
{
    bonus_t *bonus = (bonus_t *) ((elmt_t *) element_p)->value;
    msleep(1050);
    map_array[bonus->position.x][bonus->position.y] = BONUS;
    return (NULL);
}

void *thread_speed(void *element_p)
{
    player_t *player = (player_t *) element_p;
    while (running == true) {
        if (player->number_speed < player->capacity_speed) {
            msleep(player->speed);
            player->number_speed++;
        }
    }
    return (NULL);
}