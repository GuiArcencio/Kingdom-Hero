#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#include "comojogar.h"

ComoJogar* como_jogar_create(){
    ComoJogar* comojogar = (ComoJogar*) malloc(sizeof(ComoJogar));
    if (comojogar == NULL) exit(1);
    al_init_primitives_addon();
    comojogar->background = al_load_bitmap("./assets/background3.jpeg");//carregando o background
    comojogar->botaoQ = al_load_bitmap("./assets/q.png");
    comojogar->botaoW = al_load_bitmap("./assets/w.png");
    comojogar->botaoE = al_load_bitmap("./assets/e.png");
    comojogar->botaoR = al_load_bitmap("./assets/r.png");
    comojogar->fonteComoJogar = al_load_font("./fonts/Celtic.ttf", 100, 0);
    comojogar->fonteComandos = al_load_font("./fonts/Celtic.ttf", 35, 0);
    comojogar->fonteTexto = al_load_font("./fonts/Celtic.ttf", 25, 0);

    return comojogar;
}

void destroy_menu(ComoJogar* m) {
    al_destroy_bitmap(m->background);
    al_destroy_bitmap(m->botaoQ);
    al_destroy_bitmap(m->botaoW);
    al_destroy_bitmap(m->botaoE);
    al_destroy_bitmap(m->botaoR);
    al_destroy_font(m->fonteComoJogar);
    al_destroy_font(m->fonteComandos);
    al_destroy_font(m->fonteTexto);
    free(m);
}

void como_jogar_draw(ComoJogar* m){
    al_draw_scaled_bitmap(m->background, 0, 0, 1067, 1080, 0, 0, 800, 600, 0);
    al_draw_text(m->fonteComoJogar,al_map_rgb(255,255,255),400,70,ALLEGRO_ALIGN_CENTRE,"Como Jogar");
    al_draw_text(m->fonteTexto, al_map_rgb(255,255,255),400, 130, ALLEGRO_ALIGN_CENTRE,"Voce e um cavaleiro e seu reino esta sendo invadido por inimigos");
    al_draw_text(m->fonteTexto, al_map_rgb(255,255,255),400, 170, ALLEGRO_ALIGN_CENTRE,"Defenda seu reino desses malignos viloes");
    al_draw_text(m->fonteTexto, al_map_rgb(255,255,255),400, 210, ALLEGRO_ALIGN_CENTRE,"Para tal voce nobre cavaleiro deve utilizar os botoes abaixo para lhes atacar");

    al_draw_bitmap(m->botaoQ,240, 230,0);
    al_draw_bitmap(m->botaoW,330, 230,0);
    al_draw_bitmap(m->botaoE,420, 230,0);
    al_draw_bitmap(m->botaoR,510, 230,0);

    al_draw_text(m->fonteTexto, al_map_rgb(255,255,255),400, 300, ALLEGRO_ALIGN_CENTRE,"Para pontuar voce deve acertar os botoes em seus devidos tempos");
    al_draw_text(m->fonteTexto, al_map_rgb(255,255,255),400, 340, ALLEGRO_ALIGN_CENTRE,"Se voce acertar com perfeicao se ganha quinze pontos");
    al_draw_text(m->fonteTexto, al_map_rgb(255,255,255),400, 380, ALLEGRO_ALIGN_CENTRE,"Se nao se ganha cinco pontos");
    al_draw_text(m->fonteTexto, al_map_rgb(255,255,255),400, 420, ALLEGRO_ALIGN_CENTRE,"Se voce nobre cavaleiro errar perdera um coracao");
    al_draw_text(m->fonteTexto, al_map_rgb(255,255,255),400, 460, ALLEGRO_ALIGN_CENTRE,"Se voce perder os tres coracoes seu castelo sera dominado e voce perde o jogo");

    al_draw_rectangle(40,500,200,550, al_map_rgb(255,255,255),0);
    al_draw_text(m->fonteComandos,al_map_rgb(255,255,255),80,525,0,"Menu");

    al_draw_rectangle(600,500,760,550,al_map_rgb_f(1,1,1),0);
    al_draw_text(m->fonteComandos,al_map_rgb_f(1,1,1),640,525,0,"Iniciar");
}

bool clique_iniciar(int x, int y){
    return (x>=600 && x<=760 && y>=500 && y<=550);
}

bool clique_menu(int x, int y){
    return (x>=40 && x<=200 && y>=500 && y<=550);
}
/*int comojogar(){
    al_init();
    al_init_font_addon();
    al_init_image_addon();
    al_init_ttf_addon();
    al_install_mouse();
    al_init_primitives_addon();

    ALLEGRO_BITMAP *background;
    ALLEGRO_BITMAP *botaoQ;
    ALLEGRO_BITMAP *botaoW;
    ALLEGRO_BITMAP *botaoE;
    ALLEGRO_BITMAP *botaoR;
    ALLEGRO_TIMER *timer = al_create_timer(1.0/60.0);
    ALLEGRO_FONT *Titulo = al_load_font("C:\\Users\\matte\\Downloads\\celtic\\Celtic.ttf", 80, 0);
    ALLEGRO_FONT *texto = al_load_font("C:\\Users\\matte\\Downloads\\celtic\\Celtic.ttf", 25, 0);
    ALLEGRO_FONT *comandos = al_load_font("C:\\Users\\matte\\Downloads\\celtic\\Celtic.ttf", 35, 0);
    ALLEGRO_DISPLAY* janela = al_create_display(800, 600);//Cria o display em que será mostrado como jogar
    ALLEGRO_EVENT_QUEUE *events = NULL;

    background = al_load_bitmap("C:\\Users\\matte\\Documents\\Matteus\\background3.jpeg");//carregando o background
    botaoQ = al_load_bitmap("C:\\Users\\matte\\Desktop\\Projeto-final\\assets\\q.png");
    botaoW = al_load_bitmap("C:\\Users\\matte\\Desktop\\Projeto-final\\assets\\w.png");
    botaoE = al_load_bitmap("C:\\Users\\matte\\Desktop\\Projeto-final\\assets\\e.png");
    botaoR = al_load_bitmap("C:\\Users\\matte\\Desktop\\Projeto-final\\assets\\r.png");

    events = al_create_event_queue();

    al_register_event_source(events, al_get_mouse_event_source());
    al_register_event_source(events, al_get_display_event_source(janela));
    al_register_event_source(events, al_get_timer_event_source(timer));

    float x, y;
    x = 100;
    y = 100;

    bool done = false;
    bool redraw = true;
     int area = 0;
     //area = 1 iniciar, area = 2 como jogar, area = 0 restante da tela
     al_start_timer(timer);
     while (1)
     {
         ALLEGRO_EVENT event;
         al_wait_for_event(events, &event);
         switch (event.type)
         {
            case ALLEGRO_EVENT_MOUSE_AXES:
                x = event.mouse.x;
                y = event.mouse.y;
                redraw = true;
                break;
            case ALLEGRO_EVENT_TIMER:
                redraw = true;
                break;
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                done = true;
                break;

         }
         if (done)
            break;

         if (redraw && al_is_event_queue_empty(events))
         {
             al_draw_scaled_bitmap(background, 0, 0, 1067, 1080, 0, 0, 800, 600, 0);
             al_draw_text(Titulo,al_map_rgb(255,255,255),400,70,ALLEGRO_ALIGN_CENTRE,"Como Jogar");
             al_draw_text(texto, al_map_rgb(255,255,255),400, 130, ALLEGRO_ALIGN_CENTRE,"Voce e um cavaleiro e seu reino esta sendo invadido por inimigos");
             al_draw_text(texto, al_map_rgb(255,255,255),400, 170, ALLEGRO_ALIGN_CENTRE,"Defenda seu reino desses malignos viloes");
             al_draw_text(texto, al_map_rgb(255,255,255),400, 210, ALLEGRO_ALIGN_CENTRE,"Para tal voce nobre cavaleiro deve utilizar os botoes abaixo para lhes atacar");

             al_draw_bitmap(botaoQ,240, 230,0);
             al_draw_bitmap(botaoW,330, 230,0);
             al_draw_bitmap(botaoE,420, 230,0);
             al_draw_bitmap(botaoR,510, 230,0);

             al_draw_text(texto, al_map_rgb(255,255,255),400, 300, ALLEGRO_ALIGN_CENTRE,"Para pontuar voce deve acertar os botoes em seus devidos tempos");
             al_draw_text(texto, al_map_rgb(255,255,255),400, 340, ALLEGRO_ALIGN_CENTRE,"Se voce acertar com perfeição se ganha quinze pontos");
             al_draw_text(texto, al_map_rgb(255,255,255),400, 380, ALLEGRO_ALIGN_CENTRE,"Se nao se ganha cinco pontos");
             al_draw_text(texto, al_map_rgb(255,255,255),400, 420, ALLEGRO_ALIGN_CENTRE,"Se voce nobre cavaleiro errar perdera um coracao");
             al_draw_text(texto, al_map_rgb(255,255,255),400, 460, ALLEGRO_ALIGN_CENTRE,"Se voce perder os tres coracoes seu castelo sera dominado e voce perde o jogo");

             al_draw_rectangle(40,500,200,550, al_map_rgb(255,255,255),0);
             al_draw_text(comandos,al_map_rgb(255,255,255),80,525,0,"Menu");

             al_draw_rectangle(600,500,760,550,al_map_rgb_f(1,1,1),0);
             al_draw_text(comandos,al_map_rgb_f(1,1,1),640,525,0,"Iniciar");

             al_flip_display();
             redraw = false;
         }
     }
     al_destroy_bitmap(background);
    al_destroy_font(Titulo);
    al_destroy_font(texto);
    al_destroy_display(janela);
     return 0;
}*/

