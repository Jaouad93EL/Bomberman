#ifndef HEADER_H
#define HEADER_H

#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <pthread.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <sys/times.h>
#include <string.h>
#include <stdint.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>

#define WIDTH_TILE 24
#define HEIGHT_TILE 20

#define BLOCKS_WIDTH 34
#define BLOCKS_HEIGHT 28

#define MAX_NAME_LENGTH 16

#define MAP "map.txt"
#define TILESET "tileset_element.bmp"
#define TILESET_PLAYER "player"
#define TILESET_INFO_PLAYER "tileset_info.bmp"
#define MENU_IMG "background.jpeg"

typedef struct client_s {
    int id;
    int client_sock;
} client_t;

typedef enum menu_choice_e {
    QUIT = -1,
    SERVEUR = 1,
    CLIENT = 2
} menu_choice_e;

typedef enum player_e {
    DOWN = '0',
    LEFT = '1',
    RIGHT = '2',
    UP = '3',
    SPACE ='4'
} player_e;

typedef enum element_e {
    NONE = '-',
    EMPTY = '0',
    BONUS = '1',
    BRICK = '2',
    WALL = '3',
    MARIO = '4',
    RED_BOMB = '5',
    FIRE = '6',
    BOMB = '7',
    PLAYER = '8',
} element_e;

typedef enum type_bonus_e {
    BONUS_SCOPE = 0,
    BONUS_CAPACITY_BOMB = 1,
    BONUS_SPEED = 2,
} type_bonus_e;

typedef struct sdl_context_s {
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Surface *tileset;
    SDL_Surface *tileset_player;
    SDL_Surface *tileset_info_player;
    SDL_Texture *textuTil;
    SDL_Texture *textuTil_player;
    SDL_Texture *textuTil_info_player;
} sdl_context_t;

typedef enum gameState_s {
    MENU,
    CLIENT_M,
    SERVEUR_M,
    EXIT
} gameState_t;

typedef struct Images_s {
    SDL_Texture* menuTex;
    SDL_Texture* input1Tex;
    SDL_Texture* input2Tex;
} Images_t;

typedef struct Button_s {
    int min_x;
    int max_x;
    int min_y;
    int max_y;
} Button_t;

typedef struct Buttons_s {
    Button_t clientBtn;
    Button_t serveurBtn;
    Button_t quitterBtn;
    Button_t validerBtn;
    Button_t retourBtn;
} Buttons_t;

typedef struct position_s {
    int x;
    int y;
} position_t;

typedef struct player_s {
    bool alive;
    int player_number;
    int capacity_bomb;
    int number_bomb;
    int number_scope;
    int number_speed;
    int capacity_speed;
    int speed;
    position_t case_info_player;
    position_t position;
    player_e orientation;
} player_t;

typedef struct game_s {
    int nb_player;
    int p1x;
    int p2x;
    int p3x;
    int p4x;

    int p1y;
    int p2y;
    int p3y;
    int p4y;

    int p1o;
    int p2o;
    int p3o;
    int p4o;
    // char *map_array_send;
} game_t;

typedef struct bomb_s {
    int player_number;
    int player_scope;
    int now;
    position_t position;
    element_e state;
} bomb_t;

typedef struct bonus_s {
    position_t position;
    type_bonus_e type_bonus;
    element_e state;
} bonus_t;

typedef struct elmt_s {
    void *value;
    struct elmt_s *next;
    struct elmt_s *prev;
} elmt_t;

typedef struct list_s {
    int size;
    elmt_t *head;
    elmt_t *tail;
} list_t;

// global
char *ip;
char *portC;
char *port;
sdl_context_t context;
bool running;
player_t p;
list_t bomb_li;
list_t bonus_li;
char **map_array;
pthread_t thread_b;
client_t *client_array[4];
player_t *player_array[4];
int sock;
int my_socket;
int nb_client;
int s;

//list.c
void init_list(list_t * list);
void list_destroy(list_t *list);
elmt_t *list_pop(list_t *list);
elmt_t *list_get_by_coord(list_t *list, position_t *posi, element_e elem);
elmt_t *list_insert(list_t *list, elmt_t *element, void *value);
int list_delete(list_t *list, elmt_t *element);
void list_debug(list_t *list, element_e elem);

//function_thread.c
void *thread_bomb(void *bomb_p);
void *thread_bomb_now(void *bomb_p);
void *thread_bonus(void *element_p);
void *thread_speed(void *element_p);

//bomberman.c
void event_loop(sdl_context_t *context, player_t *p);
int init_sdl_context(sdl_context_t *context);
void destroy_sdl_context(sdl_context_t *context);

//display.c
void display_map(SDL_Renderer *renderer, SDL_Texture *textuTil);
void display_player(SDL_Renderer *renderer, SDL_Texture *textuPlayer, player_t *p);
void display_all_players(SDL_Renderer *renderer, SDL_Texture *textuPlayer);
void display_info_player(SDL_Renderer *renderer, SDL_Texture *textuInfo, player_t *p);

//player.c
void init_all_players(sdl_context_t *context);
void init_player(player_t *p, int player_number);
void init_info_player(player_t *p);
int init_texture_player(sdl_context_t *context);
void destroy_players();

//movement.c
void move(player_t *p, int mouv_x, int mouv_y, player_e orientation);
position_t *get_next_direction_player(player_e orientation);

//bomb.c
bomb_t *create_bomb(player_t *p);
void create_red_bomb(bomb_t *b);
void create_explosion_bomb(bomb_t *b);
void delete_explosion_bomb(bomb_t *b);

//bomb_extends.c
void trigger_bomb(position_t *posi);

//delay.c
int msleep(long msec);

//bonus.c
int random_bonus_or_not();
type_bonus_e random_choice_bonus();
bonus_t *create_bonus(position_t *posi);
int affect_bonus(player_t *p);

//main.c
void init_game();

//map.c
char **init_map(const char *str);
element_e affect_case(int x, int y, element_e elem, int force);
void free_map();

//my_function.c
int my_cmp(char *s1, char *s2);
int my_strlen(char *str);
char *my_strcpy(char *dest, char *src);
char *my_strcat(char *dest, char *src);
char *my_strdup(char *arr);

//my_str_to_wordtab.c
int count_line(char *str);
char **my_str_to_wordtab(char *str);

//read_file.c
char *read_file(int fd);
char *my_realloc(char *file, int size);

//imy_getnumber.c
int my_getnbr(char *str);

//formate.c
char *my_array_to_string(char **array);
char *player_to_string();

//menu.c
menu_choice_e display_menu(sdl_context_t *context);
void free_images(Images_t *images);
void charge_images_menu(Images_t *images, SDL_Renderer *renderer);
void init_buttons(Buttons_t *btns);
int display_image(SDL_Renderer *renderer, SDL_Texture *texture);
int display_text(SDL_Renderer *renderer, SDL_Texture *texture, int posX, int posY);
int mouseABouton(int x, int y, Buttons_t btns);

//serveur.c
void player_informations(game_t *game);
void send_map_to_all_clients();
void *thread_client(void *element_p);
int create_serveur();

//client.c
void get_player_informations(game_t *game);
void *thread_serveur(void *element_p);
int send_client_action_to_serveur(player_e direction);
int create_client();
void event_loop_client();

#endif
