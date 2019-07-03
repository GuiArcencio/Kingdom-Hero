#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#define SCREEN_W 800 // largura da tela
#define SCREEN_H 600 // altura da tela

void menu()
{
    al_init();
    al_install_mouse();
    al_install_keyboard();
    al_init_image_addon();
    al_init_font_addon();
    al_init_ttf_addon();

    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0); // timer
    ALLEGRO_EVENT_QUEUE* fila_eventos = al_create_event_queue(); // fila de eventos
    ALLEGRO_DISPLAY* janela = al_create_display(SCREEN_W, SCREEN_H); // janela
    ALLEGRO_BITMAP *botao = NULL;
    ALLEGRO_BITMAP *background = NULL;
    ALLEGRO_FONT *Titulo = al_load_ttf_font("C:\\Users\\matte\\Downloads\\celtic\\celtic.tff", 60, 0);

    botao = al_create_bitmap(100,40);//Botão para iniciar o jogo
    background = al_load_bitmap("C:\\Users\\matte\\Desktop\\Projeto-final\\assets\\background2.png");//carregando o background

    al_set_target_bitmap(botao);
    al_clear_to_color(al_map_rgba(0,0,0,25));

}
