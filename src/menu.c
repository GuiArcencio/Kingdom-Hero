#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <stdlib.h>

#include "header/menu.h"

Menu* menu_create() {
    Menu* menu = (Menu*) malloc(sizeof(Menu));
    if (menu == NULL) exit(1);
    al_init_primitives_addon();
    menu->background = al_load_bitmap("./assets/background3.jpeg");//carregando o background
    menu->fonteTitulo = al_load_font("./fonts/Celtic.ttf", 100, 0);
    menu->fonteComandos = al_load_font("./fonts/Celtic.ttf", 35, 0);

    return menu;
}

void destroy_menu(Menu* m) {
    al_destroy_bitmap(m->background);
    al_destroy_font(m->fonteTitulo);
    al_destroy_font(m->fonteComandos);
    free(m);
}

void menu_draw(Menu* m) {
    al_draw_scaled_bitmap(m->background, 0, 0, 1067, 1080, 0, 0, 800, 600, 0);//Desenha o background
    al_draw_text(m->fonteTitulo,al_map_rgb(255,255,255),400, 200,ALLEGRO_ALIGN_CENTRE,"Kingdom Hero");//desenha o titulo do jogo

    al_draw_rectangle(320, 450,480, 500, al_map_rgb(255,255,255),0);
    al_draw_text(m->fonteComandos, al_map_rgb(255,255,255),400,475, ALLEGRO_ALIGN_CENTRE, "Iniciar");

    al_draw_rectangle(320, 350, 480, 400, al_map_rgb(255,255,255),0);
    al_draw_text(m->fonteComandos, al_map_rgb(255,255,255), 400, 375, ALLEGRO_ALIGN_CENTRE, "Como jogar");
}

bool clique_iniciar(int x, int y) {
    return (x >= 320 && x <= 480 && y >= 450 && y <= 500);
}

bool clique_como_jogar(int x, int y){
    return (x >= 320 && x <= 480 && y >= 350 && y <= 400);
}