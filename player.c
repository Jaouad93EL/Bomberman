#include "header.h"

void init_player(player_t *p, int player_number)
{
    p->player_number = player_number;
    if (p->player_number == 1) {
        p->position.x = 4;
        p->position.y = 3;
        p->orientation = DOWN;
    } else if (p->player_number == 2) {
        p->position.x = 4;
        p->position.y = 4;
        p->orientation = DOWN;
    } else if (p->player_number == 3) {
        p->position.x = 4;
        p->position.y = 5;
        p->orientation = DOWN;
    } else {
        p->position.x = 4;
        p->position.y = 6;
        p->orientation = DOWN;
    }
}

void init_all_players(sdl_context_t *context)
{
    for (int i = 0; i <= nb_client; i++) {
        player_array[i] = malloc(sizeof(player_t));
        if (player_array[i] == NULL) {
            return;
        }
        init_player(player_array[i], i + 1);
        init_info_player(player_array[i]);
        init_texture_player(context);
    }
}

void init_info_player(player_t *p)
{
    p->alive = true;
    p->capacity_bomb = 1;
    p->number_bomb = 5;
    p->number_scope = 1;
    p->number_speed = 1;
    p->capacity_speed = 1;
    p->speed = 200;
    if (p->player_number == 1) {
        p->case_info_player.x = 2;
        p->case_info_player.y = 2;
    } else if (p->player_number == 2) {
        p->case_info_player.x = 2;
        p->case_info_player.y = 3;
    } else if (p->player_number == 3) {
        p->case_info_player.x = 2;
        p->case_info_player.y = 4;
    } else {
        p->case_info_player.x = 2;
        p->case_info_player.y = 5;
    }
}

int init_texture_player(sdl_context_t *context)
{
    context->tileset_player = IMG_Load("player1.bmp");
    if (context->tileset_player == NULL) {
        fprintf(stderr, "Erreur chargement image droite : %s", SDL_GetError());
        return (-1);
    }
    context->textuTil_player = SDL_CreateTextureFromSurface(context->renderer, context->tileset_player);
    if (context->textuTil_player == NULL) {
        fprintf(stderr, "Erreur SDL_CreateTexturetil : %s", SDL_GetError());
        return (-1);
    }
    return (0);
}

void destroy_players()
{
    for (int i = 0; i <= nb_client; i++)
        if (player_array[i] != NULL)
            free(player_array[i]);
}