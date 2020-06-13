#include "header.h"

int main(void)
{
	int error = init_sdl_context(&context);

    if (error == -1)
        return (error);
    menu_choice_e choice = display_menu(&context);
    if (choice == QUIT)
        return (-1);
    if (choice == SERVEUR) {
        if (create_serveur() != 0)
            return (-1);
    } else {
        create_client();
        display_all_players(context.renderer, context.textuTil_player);
        event_loop_client();
        destroy_sdl_context(&context);
        SDL_Quit();
        close(my_socket);
        return (-1);
    }
    map_array = init_map(MAP);

    init_list(&bomb_li);
    init_list(&bonus_li);
    init_all_players(&context);
    event_loop(&context, player_array[0]);
    destroy_sdl_context(&context);
    free(&bomb_li);
    free(&bonus_li);
    destroy_players();
    close(sock);

}
