#include "header.h"

int random_bonus_or_not()
{
    int r = rand() % 3;
    return (r);
}

type_bonus_e random_choice_bonus()
{
    int r = rand() % 3;

    if (r == BONUS_SCOPE)
        return (BONUS_SCOPE);
    else if (r == BONUS_CAPACITY_BOMB)
        return (BONUS_CAPACITY_BOMB);
    else if (r == BONUS_SPEED)
        return (BONUS_SPEED);
    return (-1);
}

bonus_t *create_bonus(position_t *posi)
{
    int x = posi->x;
    int y = posi->y;
    bonus_t *bonus = malloc(sizeof(bonus_t));
    elmt_t *element = NULL;

    if (bonus == NULL || random_bonus_or_not() != 0)
        return (NULL);
    bonus->position.x = x;
    bonus->position.y = y;
    bonus->state = BONUS;
    bonus->type_bonus = random_choice_bonus();
    element = list_insert(&bonus_li, bonus_li.tail, (void *) bonus);
    if (element != NULL)
        pthread_create(&thread_b, NULL, thread_bonus, (void *) element);
    return (bonus);
}

int affect_bonus(player_t *p)
{
    elmt_t *element_bonus = list_get_by_coord(&bonus_li, &p->position, BONUS);

    if (element_bonus == NULL)
        return (-1);
    bonus_t *bonus = (bonus_t *) element_bonus->value; 
    if (bonus->type_bonus == BONUS_CAPACITY_BOMB) {
        if (p->capacity_bomb < 8) {
            p->capacity_bomb++;
            p->number_bomb++;
        }
    } else if (bonus->type_bonus == BONUS_SCOPE) {
        if (p->number_scope < 10)
            p->number_scope++;
    } else if (bonus->type_bonus == BONUS_SPEED)
        if (p->speed > 50) {
            p->speed -= 25;
            p->number_speed++;
            p->capacity_speed++;
        }
    list_delete(&bonus_li, element_bonus);
    return (0);
}