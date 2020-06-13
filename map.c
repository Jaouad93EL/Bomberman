#include "header.h"

char **init_map(const char *file_name)
{
    int file = open(file_name, O_RDONLY);
    char *str = read_file(file);
    return (my_str_to_wordtab(str));
}

element_e affect_case(int x, int y, element_e elem, int force)
{
    position_t posi = {x, y};
    element_e stock_elem = map_array[x][y];

    if (force == 1) {
        map_array[x][y] = elem;
        return (NONE);
    }
    if (map_array[x][y] == BRICK && elem == FIRE) {
        map_array[x][y] = elem;
        create_bonus(&posi);
    }
    else if (map_array[x][y] == EMPTY || map_array[x][y] == FIRE)
        map_array[x][y] = elem;
    else if (map_array[x][y] == BONUS) {
        list_delete(&bonus_li, list_get_by_coord(&bonus_li, &posi, BONUS));
        map_array[x][y] = elem;
    }
    else if (map_array[x][y] == BOMB || map_array[x][y] == RED_BOMB)
        trigger_bomb(&posi);
    return (stock_elem);
}

void free_map()
{
    free(map_array);
}