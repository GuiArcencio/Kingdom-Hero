#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include "header/knight.h"

#define SCREEN_W 800 // largura da tela
#define SCREEN_H 600 // altura da tela

int main(void) {
    al_init();
    al_install_keyboard();
    al_init_image_addon();

    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0); // timer
    ALLEGRO_EVENT_QUEUE* fila_eventos = al_create_event_queue(); // fila de eventos
    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST); // opções para melhorar os gráficos
    al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);

    ALLEGRO_DISPLAY* janela = al_create_display(SCREEN_W, SCREEN_H); // janela
    al_set_window_title(janela, "Jogo daora");

    al_register_event_source(fila_eventos, al_get_keyboard_event_source()); // registra as fontes de eventos na fila de eventos
    al_register_event_source(fila_eventos, al_get_display_event_source(janela));
    al_register_event_source(fila_eventos, al_get_timer_event_source(timer));

    ALLEGRO_BITMAP* background = al_load_bitmap("./assets/background.png");
    ALLEGRO_BITMAP* q0 = al_load_bitmap("./assets/qa.png");
    ALLEGRO_BITMAP* w0 = al_load_bitmap("./assets/wa.png");
    ALLEGRO_BITMAP* e0 = al_load_bitmap("./assets/ea.png");
    ALLEGRO_BITMAP* r0 = al_load_bitmap("./assets/ra.png");

    bool sair = false;
    bool desenha = false;

    ALLEGRO_EVENT evento;

    Knight* jogador = create_knight();

    al_start_timer(timer);
    while (!sair) {
        al_wait_for_event(fila_eventos, &evento);

        switch (evento.type) {
            case ALLEGRO_EVENT_TIMER:
                knight_update_frame(jogador);

                desenha = true;
                break;
            case ALLEGRO_EVENT_KEY_DOWN:
                switch (evento.keyboard.keycode) {
                    case ALLEGRO_KEY_ESCAPE:
                        sair = true; 
                        break;
                    case ALLEGRO_KEY_Q:
                    case ALLEGRO_KEY_W:
                    case ALLEGRO_KEY_E:
                    case ALLEGRO_KEY_R:
                        knight_attack(jogador);
                        break;
                    default:
                        break;
                }
                break;
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                sair = true;
                break;
        }


        // desenhar na tela
        if (desenha && al_is_event_queue_empty(fila_eventos)) {
            al_clear_to_color(al_map_rgb(255, 255, 255));

            al_draw_scaled_bitmap(background, 0, 0, 2048, 1546, 0, 0, SCREEN_W, SCREEN_H, 0);
            al_draw_bitmap(q0, 20, 20, 0);
            al_draw_bitmap(w0, 90, 20, 0);
            al_draw_bitmap(e0, 160, 20, 0);
            al_draw_bitmap(r0, 230, 20, 0);

            knight_draw(jogador);

            al_flip_display();
            desenha = false;
        }
    }

    al_destroy_display(janela);
    al_destroy_timer(timer);
    al_destroy_event_queue(fila_eventos);
    al_destroy_bitmap(background);
    al_destroy_bitmap(q0);
    al_destroy_bitmap(w0);
    al_destroy_bitmap(e0);
    al_destroy_bitmap(r0);
    destroy_knight(jogador);

    return 0;
}
