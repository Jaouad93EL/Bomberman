#include "header.h"


menu_choice_e display_menu(sdl_context_t *context)
{
	menu_choice_e choice = QUIT;
	Images_t images;
    Buttons_t btns;
    gameState_t gs = MENU;

    int portServeurTexteLength = 0;
    int ipClientTexteLength = 0; 
    int portClientTexteLength = 0;

    char *portServeurTexteInput = malloc(16);
    char *ipClientTexteInput = malloc(16); 
    char *portClientTexteInput = malloc(16);

    bool isPortServeurTexteInput = false;
    bool isIpClientTexteInput = false; 
    bool isPortClientTexteInput = false;

    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    init_buttons(&btns);

    SDL_SetWindowResizable(context->window, SDL_FALSE);
    if (context->window == NULL) {
        printf("Error : %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    if (context->renderer == NULL) {
        printf("Error : %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    SDL_SetRenderDrawBlendMode(context->renderer, SDL_BLENDMODE_BLEND);
    charge_images_menu(&images, context->renderer);
    
    SDL_Rect PortServeurTexteRect;
    SDL_Rect IpClientTexteRect;
    SDL_Rect PortClientTexteRect;

    PortServeurTexteRect.x = 248;
    IpClientTexteRect.x = 59;
    PortClientTexteRect.x = 435;
    PortServeurTexteRect.y = IpClientTexteRect.y = PortClientTexteRect.y = 226;
    PortServeurTexteRect.w = IpClientTexteRect.w = PortClientTexteRect.w = 305;
    PortServeurTexteRect.h = IpClientTexteRect.h = PortClientTexteRect.h = 98;
    
    TTF_Font* SamanthaFBFont = TTF_OpenFont("The Foreign.otf", 64);
    if (SamanthaFBFont == NULL){
        printf("Error : %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }
    SDL_Color black = {0, 0, 0, 0};

    SDL_Surface *PortServeurSurfaceTexte = NULL;
    SDL_Surface *IpClientSurfaceTexte = NULL; 
    SDL_Surface *PortClientSurfaceTexte = NULL;
    SDL_Surface *IpSurfaceTexte = NULL;
    SDL_Surface *PortSurfaceTexte = NULL;

    SDL_Texture *PortServeurTexte = NULL;
    SDL_Texture *IpClientTexte = NULL; 
    SDL_Texture *PortClientTexte = NULL;
    SDL_Texture *IpTexte = NULL;
    SDL_Texture *PortTexte = NULL;

    while (gs != EXIT) {
        switch (gs) {
            case MENU:
                if (display_image(context->renderer, images.menuTex) == EXIT_FAILURE)
                    return EXIT_FAILURE;
            break;
            case CLIENT_M:
                if (display_image(context->renderer, images.input2Tex) == EXIT_FAILURE)
                    return EXIT_FAILURE;
                SDL_RenderCopy(context->renderer, IpClientTexte, NULL, &IpClientTexteRect);
                SDL_RenderCopy(context->renderer, PortClientTexte, NULL, &PortClientTexteRect);
            break;
            case SERVEUR_M:
                if (display_image(context->renderer, images.input1Tex) == EXIT_FAILURE)
                    return EXIT_FAILURE;
                SDL_RenderCopy(context->renderer, PortServeurTexte, NULL, &PortServeurTexteRect);
            break;
            default: 
            break;
        }

        SDL_Event event;
        SDL_WaitEvent(&event);
        switch(event.type) {
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_BACKSPACE) {
                    if (gs == SERVEUR_M && portServeurTexteLength > 0) {
                        portServeurTexteLength--;
                        portServeurTexteInput[strlen(portServeurTexteInput)-1] = 0;
                        PortServeurSurfaceTexte = TTF_RenderText_Blended(SamanthaFBFont, portServeurTexteInput, black);
                        PortServeurTexte = SDL_CreateTextureFromSurface(context->renderer, PortServeurSurfaceTexte);
                    } else if (gs == CLIENT_M) {
                        if (isIpClientTexteInput && ipClientTexteLength > 0) {
                            ipClientTexteLength--;
                            ipClientTexteInput[strlen(ipClientTexteInput)-1] = 0;
                            IpClientSurfaceTexte = TTF_RenderText_Blended(SamanthaFBFont, ipClientTexteInput, black);
                            IpClientTexte = SDL_CreateTextureFromSurface(context->renderer, IpClientSurfaceTexte);
                        }
                        else if (isPortClientTexteInput && portClientTexteLength > 0) {
                            portClientTexteLength--;
                            portClientTexteInput[strlen(portClientTexteInput)-1] = 0;
                            PortClientSurfaceTexte = TTF_RenderText_Blended(SamanthaFBFont, portClientTexteInput, black);
                            PortClientTexte = SDL_CreateTextureFromSurface(context->renderer, PortClientSurfaceTexte);
                        }
                    }
                }
            break;
            case SDL_TEXTINPUT:
                if (gs == SERVEUR_M && portServeurTexteLength < MAX_NAME_LENGTH) {
                    portServeurTexteLength++;
                    strcat(portServeurTexteInput, event.text.text);
                    PortServeurSurfaceTexte = TTF_RenderText_Blended(SamanthaFBFont, portServeurTexteInput, black);
                    PortServeurTexte = SDL_CreateTextureFromSurface(context->renderer, PortServeurSurfaceTexte);
                } else if (gs == CLIENT_M) {
                    if (isIpClientTexteInput && ipClientTexteLength < MAX_NAME_LENGTH) {
                        ipClientTexteLength++;
                        strcat(ipClientTexteInput, event.text.text);
                        IpClientSurfaceTexte = TTF_RenderText_Blended(SamanthaFBFont, ipClientTexteInput, black);
                        IpClientTexte = SDL_CreateTextureFromSurface(context->renderer, IpClientSurfaceTexte);
                    }
                    else if (isPortClientTexteInput && portClientTexteLength < MAX_NAME_LENGTH) {
                        portClientTexteLength++;
                        strcat(portClientTexteInput, event.text.text);
                        PortClientSurfaceTexte = TTF_RenderText_Blended(SamanthaFBFont, portClientTexteInput, black);
                        PortClientTexte = SDL_CreateTextureFromSurface(context->renderer, PortClientSurfaceTexte);
                    }
                }
            break;
            case SDL_MOUSEBUTTONDOWN:
                if (gs == CLIENT_M)
                {
                    int x = event.button.x, y=event.button.y;
                    if (x >= IpClientTexteRect.x && x <= IpClientTexteRect.x+IpClientTexteRect.w &&
                        y >= IpClientTexteRect.y && y <= IpClientTexteRect.y+IpClientTexteRect.h)
                    {
                        SDL_StartTextInput();
                        isIpClientTexteInput = true;
                        isPortClientTexteInput = false;
                    } else if (x >= PortClientTexteRect.x && x <= PortClientTexteRect.x+PortClientTexteRect.w &&
                        y >= PortClientTexteRect.y && y <= PortClientTexteRect.y+PortClientTexteRect.h)
                    { 
                        SDL_StartTextInput();
                        isIpClientTexteInput = false;
                        isPortClientTexteInput = true;
                    } else {
                        isIpClientTexteInput = false;
                        isPortClientTexteInput = false;
                        SDL_StopTextInput();
                    }
                    if (x >= btns.validerBtn.min_x && x <= btns.validerBtn.max_x &&
                        y >= btns.validerBtn.min_y && y <= btns.validerBtn.max_y)
                    {
                        ip = ipClientTexteInput;
                        portC = portClientTexteInput;
                        choice = CLIENT;
                        return (choice);
                    }

                    if (x >= btns.retourBtn.min_x && x <= btns.retourBtn.max_x &&
                        y >= btns.retourBtn.min_y && y <= btns.retourBtn.max_y)
                    {
                        gs = MENU;
                    }
                } else if (gs == SERVEUR_M) {
                    int x = event.button.x, y=event.button.y;
                    if (x >= PortServeurTexteRect.x && x <= PortServeurTexteRect.x+PortServeurTexteRect.w &&
                        y >= PortServeurTexteRect.y && y <= PortServeurTexteRect.y+PortServeurTexteRect.h)
                    {
                        isPortServeurTexteInput = true;
                        SDL_StartTextInput();
                    } else {
                        isPortServeurTexteInput = false;
                        SDL_StopTextInput();
                    }
                    if (x >= btns.validerBtn.min_x && x <= btns.validerBtn.max_x &&
                        y >= btns.validerBtn.min_y && y <= btns.validerBtn.max_y) {
                        port = portServeurTexteInput;
                        choice = SERVEUR;
                        return (choice);
                    }
                    if (x >= btns.retourBtn.min_x && x <= btns.retourBtn.max_x &&
                        y >= btns.retourBtn.min_y && y <= btns.retourBtn.max_y)
                    {
                        gs = MENU;
                    }
                } else if (gs == MENU) {
                    int bouton = mouseABouton(event.button.x, event.button.y, btns);
                    if (bouton == 0) {
                        gs = CLIENT_M;
                    } else if (bouton == 1) {
                        gs = SERVEUR_M;
                    } else if (bouton == 2) {
                        gs = EXIT;
                    }
                }
                break;
            case SDL_QUIT:
                gs = EXIT;
                break;
        }
        SDL_SetRenderDrawColor(context->renderer, 255, 0, 0, 100);
        if (isPortServeurTexteInput)
            SDL_RenderFillRect(context->renderer, &PortServeurTexteRect);
        if (isIpClientTexteInput)
            SDL_RenderFillRect(context->renderer, &IpClientTexteRect);
        if (isPortClientTexteInput)
            SDL_RenderFillRect(context->renderer, &PortClientTexteRect);
        SDL_RenderPresent(context->renderer);
    }

    free_images(&images);
    SDL_FreeSurface(PortServeurSurfaceTexte);
    SDL_FreeSurface(IpSurfaceTexte);
    SDL_FreeSurface(PortSurfaceTexte);
    SDL_DestroyTexture(PortServeurTexte);
    SDL_DestroyTexture(IpTexte);
    SDL_DestroyTexture(PortTexte);
    TTF_CloseFont(SamanthaFBFont);
    TTF_Quit();
    IMG_Quit();
    return (choice);
}

void init_buttons(Buttons_t *btns)
{
    int w = 305;
    int h = 98;

    btns->clientBtn.min_x = btns->serveurBtn.min_x = 
    btns->retourBtn.min_x = btns->quitterBtn.min_x = 
    btns->validerBtn.min_x = 248;
    btns->clientBtn.max_x = btns->serveurBtn.max_x = 
    btns->retourBtn.max_x = btns->quitterBtn.max_x = 
    btns->validerBtn.max_x =248 + w;
    btns->serveurBtn.min_y = 206;
    btns->serveurBtn.max_y = 206 + h;
    btns->clientBtn.min_y = btns->validerBtn.min_y = 334;
    btns->clientBtn.max_y = btns->validerBtn.max_y = 334 + h;
    btns->retourBtn.min_y = btns->quitterBtn.min_y = 461;
    btns->retourBtn.max_y = btns->quitterBtn.max_y = 461 + h;
}
void free_images(Images_t *images)
{
    SDL_DestroyTexture(images->menuTex);
    SDL_DestroyTexture(images->input1Tex);
    SDL_DestroyTexture(images->input2Tex);
}
void charge_images_menu(Images_t *images, SDL_Renderer* renderer)
{
    SDL_Surface* s = IMG_Load("menu.png");
    images->menuTex = SDL_CreateTextureFromSurface(renderer, s);

    s = IMG_Load("input1.png");
    images->input1Tex = SDL_CreateTextureFromSurface(renderer, s);

    s = IMG_Load("input2.png");
    images->input2Tex = SDL_CreateTextureFromSurface(renderer, s);
}

int display_image(SDL_Renderer* renderer, SDL_Texture* texture)
{
    SDL_Rect dest = {0, 0, 800, 600};

    if (texture == NULL || SDL_RenderCopy(renderer, texture, NULL, &dest) != 0) {
        printf("Error : %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

int display_text(SDL_Renderer* renderer, SDL_Texture* texture, int posX, int posY)
{
    SDL_Rect dest = {posX, posY, 200, 57};

    if (SDL_RenderCopy(renderer, texture, NULL, &dest) != 0) {
        printf("Error : %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int mouseABouton(int x, int y, Buttons_t btns)
{
    int bouton = -1;

    if (x >= btns.serveurBtn.min_x && x <= btns.serveurBtn.max_x) {
        if (y >= btns.clientBtn.min_y && y <= btns.clientBtn.max_y)
            bouton = 0;
        else if (y >= btns.serveurBtn.min_y && y <= btns.serveurBtn.max_y)
            bouton = 1;
        else if (y >= btns.quitterBtn.min_y && y <= btns.quitterBtn.max_y)
            bouton = 2;
    }
    return bouton;
}