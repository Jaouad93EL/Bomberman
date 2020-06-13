#include "header.h"


void display_map(SDL_Renderer *renderer, SDL_Texture *textuTil)
{
    SDL_Rect Rect_dest;
    SDL_Rect Rect_source;

    Rect_source.w = WIDTH_TILE;
    Rect_dest.w   = WIDTH_TILE;
    Rect_source.h = HEIGHT_TILE;
    Rect_dest.h   = HEIGHT_TILE;
    for(int i = 0 ; i < BLOCKS_WIDTH; i++) {
        for(int j = 0 ; j < BLOCKS_HEIGHT; j++) {
            Rect_dest.x = i * WIDTH_TILE;
            Rect_dest.y = j * HEIGHT_TILE;
            Rect_source.x = (map_array[j][i] - '0') * WIDTH_TILE;
            Rect_source.y = 0;
            SDL_RenderCopy(renderer, textuTil, &Rect_source, &Rect_dest);
        }
    }
}

void display_player(SDL_Renderer *renderer, SDL_Texture *textuPlayer, player_t *p)
{
    SDL_Rect Rect_dest;
    SDL_Rect Rect_source;

    Rect_source.w = WIDTH_TILE;
    Rect_dest.w   = WIDTH_TILE;
    Rect_source.h = HEIGHT_TILE;
    Rect_dest.h   = HEIGHT_TILE;
    Rect_dest.x = p->position.y * WIDTH_TILE;
    Rect_dest.y = p->position.x * HEIGHT_TILE;
    Rect_source.x = (p->orientation - '0') * WIDTH_TILE;
    Rect_source.y = 0;
    SDL_RenderCopy(renderer, textuPlayer, &Rect_source, &Rect_dest);
}


void display_all_players(SDL_Renderer *renderer, SDL_Texture *textuPlayer)
{
    if (nb_client == 0)
        return;
    for (int i = 0; i <= nb_client; i++) {
        if (player_array[i] == NULL) {
            continue;
        }
        SDL_Rect Rect_dest;
        SDL_Rect Rect_source;

        Rect_source.w = WIDTH_TILE;
        Rect_dest.w = WIDTH_TILE;
        Rect_source.h = HEIGHT_TILE;
        Rect_dest.h = HEIGHT_TILE;
        Rect_dest.x = player_array[i]->position.y * WIDTH_TILE;
        Rect_dest.y = player_array[i]->position.x * HEIGHT_TILE;
        Rect_source.x = (player_array[i]->orientation - '0') * WIDTH_TILE;
        Rect_source.y = 0;
        SDL_RenderCopy(renderer, textuPlayer, &Rect_source, &Rect_dest);
    }
}

void display_info_player(SDL_Renderer *renderer, SDL_Texture *textuInfo, player_t *p)
{
    SDL_Rect Rect_dest;
    SDL_Rect Rect_source;

    Rect_source.w = WIDTH_TILE;
    Rect_dest.w   = WIDTH_TILE;
    Rect_source.h = HEIGHT_TILE;
    Rect_dest.h   = HEIGHT_TILE;
    Rect_dest.x = p->case_info_player.x * WIDTH_TILE;
    Rect_dest.y = p->case_info_player.y * HEIGHT_TILE;
    Rect_source.x = (p->number_bomb - 1) * WIDTH_TILE;
    Rect_source.y = 0;
    SDL_RenderCopy(renderer, textuInfo, &Rect_source, &Rect_dest);
}