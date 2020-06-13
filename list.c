#include "header.h"

void init_list(list_t *list)
{
    list->size = 0;
    list->head = NULL;
    list->tail = NULL;
}

void list_destroy(list_t *list)
{
    elmt_t *old_element;

    while (list->size > 0) {
        old_element = list_pop(list);
        free(old_element);
    }
}

elmt_t *list_insert(list_t *list, elmt_t *element, void *value)
{
    elmt_t *new_element = (elmt_t *) malloc(sizeof(elmt_t));

    if (new_element == NULL || value == NULL)
        return (NULL);
    new_element->value = value;
    if (list->size == 0) {
        list->head = new_element;
        list->head->prev = NULL;
        list->head->next = NULL;
        list->tail = new_element;
    } else {
        new_element->next = element->next;
        new_element->prev = element;
        if (element->next == NULL)
            list->tail = new_element;
        else
            element->next->prev = new_element;
        element->next = new_element;
    }
    list->size++;
    return (new_element);
}

elmt_t *list_pop(list_t *list)
{
    elmt_t *old_element;

    if (list->size == 0)
        return (NULL);
    old_element = list->head;
    list->head = list->head->next;
    if (list->size == 1)
        list->tail = NULL;
    list->size--;
    return (old_element);
}

elmt_t *list_get_by_coord(list_t *list, position_t *posi, element_e elem)
{
    elmt_t *element = (elmt_t *) malloc(sizeof(elmt_t));
    bomb_t *bomb = (bomb_t *) malloc(sizeof(bomb_t));
    bonus_t *bonus = (bonus_t *) malloc(sizeof(bonus_t));

    element = list->head;
    for (int i = 0;  i < list->size; i++) {
        if (elem == BONUS) {
            bonus = (bonus_t *) element->value;
            if (bonus->position.x == posi->x && bonus->position.y == posi->y)
                return (element);
        } else {
            bomb = (bomb_t *) element->value;
            if (bomb->position.x == posi->x && bomb->position.y == posi->y)
                return (element);
        }
        element = element->next;
    }
    return (NULL);
}

int list_delete(list_t *list, elmt_t *element)
{
    if (element == NULL || list->size == 0)
        return (-1);
    if (element == list->head) {
        list->head = element->next;
        if (list->head == NULL)
            list->tail = NULL;
        else
            element->next->prev = NULL;
    }
    else {
        element->prev->next = element->next;
        if (element->next == NULL)
            list->tail = element->prev;
        else
            element->next->prev = element->prev;
    }
    if (element != NULL)
        free(element);
    list->size--;
    return (0);
}

void list_debug(list_t *list, element_e elem)
{
    elmt_t *element = (elmt_t *) malloc(sizeof(elmt_t));
    bomb_t *bomb = (bomb_t *) malloc(sizeof(bomb_t));
    bonus_t *bonus = (bonus_t *) malloc(sizeof(bonus_t));
    element = list->head;
    for (int i = 0;  i < list->size; i++) {
        if (elem == BONUS) {
            bonus = ((bonus_t *) element->value);
            printf("{%d -> x: %d | y: %d}\n", i, bonus->position.x, bonus->position.y);
        }
        else {
            bomb = ((bomb_t *) element->value);
            printf("{%d -> x: %d | y: %d}\n", i, bomb->position.x, bomb->position.y);
        }
        element = element->next;
    }
}