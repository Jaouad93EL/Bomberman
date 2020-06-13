#include "header.h"

void trigger_bomb(position_t *posi)
{
    elmt_t *element = list_get_by_coord(&bomb_li, posi, BOMB);
    
    if(element != NULL) {
        if (((bomb_t *) element->value)->state != EMPTY)
            pthread_create(&thread_b, NULL, thread_bomb_now, (void *) element);
    }
}