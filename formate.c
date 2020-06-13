#include "header.h"


char *my_array_to_string(char **array)
{
    char *str = malloc(sizeof(char) * ((BLOCKS_WIDTH * BLOCKS_HEIGHT) + BLOCKS_HEIGHT));
    int n = 0;

    for (int i = 0; i < BLOCKS_HEIGHT; ++i) {
        for (int j = 0; j < BLOCKS_WIDTH; j++) {
            str[n] = array[i][j];
            ++n;
        }
        str[n] = '\n';
        ++n;
    }
    str[n] = '\0';
    return (str);
}

char *player_to_string()
{
    char *str = malloc(sizeof(char) * (nb_client * 4));
    int n = 0;

    for (int i = 0; i <= nb_client; ++i) {
        str[n] = player_array[i]->position.x + '0';
        ++n;
        str[n] = '-';
        ++n;
        str[n] = player_array[i]->position.y + '0';
        ++n;
        str[n] = '\n';
        ++n;
    }
    str[n] = '\0';
    return (str);
}