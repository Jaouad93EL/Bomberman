#include "header.h"

void player_informations(game_t *game)
{
    if (player_array[0] != NULL) {
        game->p1x = player_array[0]->position.x;
        game->p1y = player_array[0]->position.y;
        game->p1o = player_array[0]->orientation;
    }
    if (player_array[1] != NULL) {
        game->p2x = player_array[1]->position.x;
        game->p2y = player_array[1]->position.y;
        game->p2o = player_array[0]->orientation;

    }
    if (player_array[2] != NULL) {
        game->p3x = player_array[2]->position.x;
        game->p3y = player_array[2]->position.y;
        game->p3o = player_array[0]->orientation;
    }
    if (player_array[3] != NULL) {
        game->p4x = player_array[3]->position.x;
        game->p4y = player_array[3]->position.y;
        game->p4o = player_array[0]->orientation;
    }
}

void send_map_to_all_clients()
{
    unsigned int client_addr_len = sizeof(struct sockaddr_in);
    struct sockaddr_in client;
    game_t *game = malloc(sizeof(game_t));
    
    game->nb_player = nb_client;
    player_informations(game);

    for (int i = 1; i <= nb_client; i++) {
        int sender = sendto(client_array[i]->client_sock,
                            game,
					        sizeof(*(game)),
                            MSG_SEND,
			                (struct sockaddr *)&client,
                            client_addr_len);
        if (sender > 0) {
        }

        int s = send(client_array[i]->client_sock, my_array_to_string(map_array), 1000, MSG_SEND);
        if (s > 0) {
        }
    }
}

void send_nb_client_to_client(int client_sock, int nb_client)
{
    int nb_client_htonl = htonl(nb_client);

    send(client_sock, &nb_client_htonl, sizeof(nb_client_htonl), MSG_SEND);
}

void *thread_client(void *element_p)
{
    int n;
    int receive;
    client_t *client =  (client_t *) element_p;

    while (true) {
        n = read(client->client_sock, &receive, sizeof(receive));
        if (n > 0) {
            if (player_array[client->id] != NULL) {

                if (ntohl(receive) == SPACE) {
                        elmt_t *element = list_insert(&bomb_li, bomb_li.tail, (void *) create_bomb(player_array[client->id]));
                        if (element != NULL)
                            pthread_create(&thread_b, NULL, thread_bomb, (void *) element);
                } else {
                    position_t *posi = get_next_direction_player(ntohl(receive));
                    move(player_array[client->id], posi->x, posi->y, ntohl(receive));
                }
            }
        }
    }
    return (NULL);
}

int create_serveur()
{
    int client_sock = 1;
    socklen_t client_addr_len;
    struct sockaddr_in server;
    struct sockaddr_in client_addr;
    pthread_t thread_c;
    nb_client = 0;


    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        perror("socket()");
        return 1;
    }

    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_family = AF_INET;
    server.sin_port = htons(atoi(port)); 

    if (bind(sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("bind()");
        return 1;
    }

    listen(sock, 5);

    client_array[nb_client] = malloc(sizeof(client_t));
    client_array[nb_client]->client_sock = 0;
    client_array[nb_client]->id = 0;

    puts("waiting client ...");
    while (client_sock && nb_client < 3) {
        puts("waiting for accept");
        client_sock = accept(sock, (struct sockaddr *)&client_addr, &client_addr_len);
        if (client_sock < 0) {
            perror("accept()");
            return (-1);
        }
        puts("new client");
        nb_client += 1;
        send_nb_client_to_client(client_sock, nb_client);
        client_array[nb_client] = malloc(sizeof(client_t));
        client_array[nb_client]->client_sock = client_sock;
        client_array[nb_client]->id = nb_client;
        pthread_create(&thread_c, NULL, thread_client, (void *) client_array[nb_client]);
    }
    printf("end create_serveur\n");
    return (0);
}