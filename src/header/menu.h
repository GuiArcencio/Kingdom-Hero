#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>

typedef struct menu {
    ALLEGRO_BITMAP* background;
    ALLEGRO_FONT* fonteTitulo;
    ALLEGRO_FONT* fonteComandos;
} Menu;

void menu_draw(Menu* m);

Menu* menu_create();

void destroy_menu(Menu* m);

bool clique_iniciar(int x, int y);