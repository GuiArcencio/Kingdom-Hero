#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>

typedef struct comojogar{
    ALLEGRO_BITMAP* background;
    ALLEGRO_BITMAP* botaoQ;
    ALLEGRO_BITMAP* botaoW;
    ALLEGRO_BITMAP* botaoE;
    ALLEGRO_BITMAP* botaoR;
    ALLEGRO_FONT *fonteComoJogar;
    ALLEGRO_FONT *fonteTexto;
    ALLEGRO_FONT *fonteComandos;
}ComoJogar;

ComoJogar* como_jogar_create();

void como_jogar_draw(ComoJogar* m);

void destroy_como_jogar(ComoJogar* m);

bool clique_iniciar(int x, int y);

bool clique_menu(int x, int y);
