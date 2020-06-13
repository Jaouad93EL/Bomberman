#include "header.h"

int init_sdl_context(sdl_context_t *context)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "Erreur SDL_Init : %s", SDL_GetError());
        return (-1);
    }
    context->window = SDL_CreateWindow("Bomberman :        )", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            WIDTH_TILE * BLOCKS_WIDTH, HEIGHT_TILE * BLOCKS_HEIGHT, SDL_WINDOW_SHOWN);
    if (context->window == NULL) {
        fprintf(stderr, "Erreur SDL_CreateWindow : %s", SDL_GetError());
        return (-1);

    }
    context->renderer = SDL_CreateRenderer(context->window, -1, SDL_RENDERER_ACCELERATED);
    if (context->renderer == NULL) {
        fprintf(stderr, "Erreur SDL_CreateRenderer : %s", SDL_GetError());
        return (-1);
    }
    context->tileset = IMG_Load(TILESET);
    if (context->tileset == NULL) {
        fprintf(stderr, "Erreur chargement image droite : %s", SDL_GetError());
        return (-1);
    }

    context->tileset_info_player = IMG_Load(TILESET_INFO_PLAYER);
    if (context->tileset_info_player == NULL) {
        fprintf(stderr, "Erreur chargement image droite : %s", SDL_GetError());
        return (-1);
    }
    context->textuTil = SDL_CreateTextureFromSurface(context->renderer, context->tileset);
    if (context->textuTil == NULL) {
        fprintf(stderr, "Erreur SDL_CreateTexturetil : %s", SDL_GetError());
        return (-1);
    }

    context->textuTil_info_player = SDL_CreateTextureFromSurface(context->renderer, context->tileset_info_player);
    if (context->textuTil_info_player == NULL) {
        fprintf(stderr, "Erreur SDL_CreateTexturetil : %s", SDL_GetError());
        return (-1);
    }
    SDL_FreeSurface(context->tileset);
    return (0);
}

void destroy_sdl_context(sdl_context_t *context)
{
    if (context->window != NULL)
        SDL_DestroyWindow(context->window);
    if (context->renderer != NULL)
        SDL_DestroyRenderer(context->renderer);
    if (context->textuTil != NULL)
        SDL_DestroyTexture(context->textuTil);
    if (context->textuTil_player != NULL)
        SDL_DestroyTexture(context->textuTil_player);
    if (context->textuTil_info_player != NULL)
        SDL_DestroyTexture(context->textuTil_info_player);
    SDL_Quit();
}

void event_loop(sdl_context_t *context, player_t *p)
{
    SDL_Event event;
    running = true;
    elmt_t *element = NULL;

    pthread_create(&thread_b, NULL, thread_speed, (void *) player_array[0]);
    pthread_create(&thread_b, NULL, thread_speed, (void *) player_array[1]);
    pthread_create(&thread_b, NULL, thread_speed, (void *) player_array[2]);
    pthread_create(&thread_b, NULL, thread_speed, (void *) player_array[3]);


    while(running == true) {
        SDL_PollEvent(&event);
        switch(event.type) {
            case SDL_QUIT:
                running = false;
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        running = false;
                        break;
                    case SDLK_SPACE:
                        element = list_insert(&bomb_li, bomb_li.tail, (void *) create_bomb(p));
                        if (element != NULL)
                            pthread_create(&thread_b, NULL, thread_bomb, (void *) element);
                        break;
                    case 'w':
                        move(player_array[0], -1, 0, UP);
                        break;
                    case 's':
                        move(player_array[0], 1, 0, DOWN);
                        break;
                    case 'a':
                        move(player_array[0], 0, -1, LEFT);
                        break;
                    case 'd':
                        move(player_array[0], 0, 1, RIGHT);
                        break;
                }
                break;
        }
        display_map(context->renderer, context->textuTil);
        display_all_players(context->renderer, context->textuTil_player);
        display_info_player(context->renderer, context->textuTil_info_player, player_array[0]);
        send_map_to_all_clients();
        SDL_RenderPresent(context->renderer);
    }
}