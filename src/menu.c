#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <stdlib.h>

#define SCREEN_W 800 // largura da tela
#define SCREEN_H 600 // altura da tela

int main(void)
{
    al_init();
    al_init_image_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_primitives_addon();
    al_install_mouse();

    ALLEGRO_BITMAP *background = NULL;
    ALLEGRO_TIMER *timer = al_create_timer(1.0/60.0);
    ALLEGRO_FONT *Titulo = al_load_font("C:\\Users\\matte\\Downloads\\celtic\\Celtic.ttf", 100, 0);
    ALLEGRO_FONT *Comandos = al_load_font("C:\\Users\\matte\\Downloads\\celtic\\Celtic.ttf", 35, 0);
    ALLEGRO_FONT *dados = al_create_builtin_font();
    ALLEGRO_DISPLAY* janela = al_create_display(800, 600);//Cria o display em que será mostrado o menu
    ALLEGRO_EVENT_QUEUE *events = NULL;

    background = al_load_bitmap("C:\\Users\\matte\\Documents\\Matteus\\background3.jpeg");//carregando o background
    if (janela == NULL) exit(1);

    events = al_create_event_queue();

    al_register_event_source(events,al_get_mouse_event_source());
    al_register_event_source(events,al_get_display_event_source(janela));

    float x, y;
    x = 100;
    y = 100;

    bool done = false;
    bool redraw = true;
     int area = 0;
     //area = 1 iniciar, area = 2 como jogar, area = 0 restante da tela
     al_start_timer(timer);

    while(1){
        ALLEGRO_EVENT event;
        al_wait_for_event(events, &event);
        switch(event.type)
        {
            case ALLEGRO_EVENT_MOUSE_AXES:
                x = event.mouse.x;
                y = event.mouse.y;
                if (x>=320 && x<=480)
                {
                    if (y>=450 && y<=500)
                        area = 1;
                    else if(y>=350 && y<=400)
                        area = 2;
                    else
                        area = 0;

                }
                redraw = true;
                break;
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                done = true;
            case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
                break;
		redraw = true;
            case ALLEGRO_EVENT_TIMER:
                redraw = true;
                break;
        }

        if (done)
            break;

        if (redraw && al_is_event_queue_empty(events))
        {
            al_draw_scaled_bitmap(background, 0, 0, 1067, 1080, 0, 0, SCREEN_W, SCREEN_H, 0);//Desenha o background
            al_draw_text(Titulo,al_map_rgb(255,255,255),400, 200,ALLEGRO_ALIGN_CENTRE,"Kingdom Hero");//desenha o titulo do jogo

            al_draw_rectangle(320, 450,480, 500, al_map_rgb(255,255,255),0);
            al_draw_text(Comandos, al_map_rgb(255,255,255),400,475, ALLEGRO_ALIGN_CENTRE, "Iniciar");

            al_draw_rectangle(320, 350, 480, 400, al_map_rgb(255,255,255),0);
            al_draw_text(Comandos, al_map_rgb(255,255,255), 400, 375, ALLEGRO_ALIGN_CENTRE, "Como jogar");

            al_draw_textf(dados,al_map_rgb(255,255,255),0,0,0,"area = %d\nx = %f\ny = %f",area,x,y);

            al_flip_display();

            redraw = false;
        }
    }

    al_destroy_bitmap(background);
    al_destroy_font(Titulo);
    al_destroy_font(Comandos);
    al_destroy_display(janela);
    return 0;
}