#include "header.h"

char buff[1000];


void event_loop_client()
{
    SDL_Event event;
    running = true;

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
                        send_client_action_to_serveur(SPACE);
                        break;
                    case 'w':
                        send_client_action_to_serveur(UP);
                        break;
                    case 's':
                        send_client_action_to_serveur(DOWN);
                        break;
                    case 'a':
                        send_client_action_to_serveur(LEFT);
                        break;
                    case 'd':
                        send_client_action_to_serveur(RIGHT);
                        break;
                }
                break;
        }
        display_map(context.renderer, context.textuTil);
        display_player(context.renderer, context.textuTil_player, player_array[1]);
        display_all_players(context.renderer, context.textuTil_player);
        SDL_RenderPresent(context.renderer);
    }
}

void get_player_informations(game_t *game)
{
    for (int i = 0; i <= game->nb_player; i++) {
        if (i == 0) {
            map_array[game->p1x][game->p1y] = '4';
            player_array[0]->position.x = game->p1x;
            player_array[0]->position.y = game->p1y;
            player_array[0]->orientation = game->p1o;
        }
        else if (i == 1) {
            map_array[game->p2x][game->p2y] = '4';
            player_array[1]->position.x = game->p2x;
            player_array[1]->position.y = game->p2y;
            player_array[1]->orientation = game->p2o;
        }
        else if (i == 2) {
            map_array[game->p3y][game->p3y] = '4';
            player_array[2]->position.x = game->p3x;
            player_array[2]->position.y = game->p3y;
            player_array[2]->orientation = game->p3o;
        }
        else if (i == 3) {
            map_array[game->p4x][game->p4y] = '4';
            player_array[3]->position.x = game->p4x;
            player_array[3]->position.y = game->p4y;
            player_array[3]->orientation = game->p4o;
        }
    }
}

void *thread_serveur(void *nb)
{
    int n = (int) nb;
    int m;
    game_t *game = malloc(sizeof(game_t));
    struct sockaddr_in client;
    unsigned int client_addr_len;
	client_addr_len = sizeof(struct sockaddr_in);
    player_array[0] = malloc(sizeof(player_t));
    player_array[1] = malloc(sizeof(player_t));
    player_array[2] = malloc(sizeof(player_t));
    player_array[3] = malloc(sizeof(player_t));


    while (1) {
        n = recvfrom(my_socket,
					game,
                    sizeof(*(game)),
                    0,
					(struct sockaddr *) &client,
					&client_addr_len);

        m = read(my_socket, buff, 1000);

        if (m > 0) {
            map_array = my_str_to_wordtab(buff);
        }
        if (n > 0) {
            get_player_informations(game);
            nb_client = game->nb_player;
        }
    }
    return (NULL);
}

int send_client_action_to_serveur(player_e direction)
{
    int direc = direction;
    int direc_htonl = htonl(direc);
    if (send(my_socket, &direc_htonl, sizeof(direc_htonl), MSG_SEND) < 0) {
        puts("send failed");
        close(my_socket);
        return (-1);
    }
    return (0);
}

int create_client()
{
    int n;
    int receive;
    pthread_t thread_c;
    struct sockaddr_in my_server;
    my_server.sin_addr.s_addr = inet_addr(ip);
    my_server.sin_family = AF_INET;
    my_server.sin_port = htons(atoi(portC));
    my_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (my_socket < 0) {
        printf("error socket");
        return (-1);
    }
    if (connect(my_socket, (struct sockaddr *)&my_server, sizeof(my_server)) < 0) {
        printf("not connect()");
        return -1;
    }
    pthread_create(&thread_c, NULL, thread_serveur, (void*) 0);
    n = read(my_socket, &receive, sizeof(receive));
    if (n == -1)
        return (-1);

    map_array = init_map(MAP);
    return (0);
}