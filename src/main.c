#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>

#define SCREEN_W 800 // largura da tela
#define SCREEN_H 600 // altura da tela

int main() {
    al_init();
    al_install_keyboard();
    al_init_image_addon();

    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0); // timer
    ALLEGRO_EVENT_QUEUE* fila_eventos = al_create_event_queue(); // fila de eventos
    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST); // opções para melhorar os gráficos
    al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);
    al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);
    ALLEGRO_DISPLAY* janela = al_create_display(SCREEN_W, SCREEN_H); // janela
    al_set_window_title(janela, "Jogo daora");

    al_register_event_source(fila_eventos, al_get_keyboard_event_source()); // registra as fontes de eventos na fila de eventos
    al_register_event_source(fila_eventos, al_get_display_event_source(janela));
    al_register_event_source(fila_eventos, al_get_timer_event_source(timer));

    ALLEGRO_BITMAP* background = al_load_bitmap("./assets/background.png");

    bool sair = false;
    bool desenha = false;

    ALLEGRO_EVENT evento;

    al_start_timer(timer);
    while (!sair) {
        al_wait_for_event(fila_eventos, &evento);

        switch (evento.type) {
            case ALLEGRO_EVENT_TIMER:
                desenha = true;
                break;
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                sair = true;
                break;
        }


        // desenhar na tela
        if (desenha && al_is_event_queue_empty(fila_eventos)) {
            al_clear_to_color(al_map_rgb(255, 255, 255));

            al_draw_scaled_bitmap(background, 0, 0, 2048, 1546, 0, 0, 800, 600, 0);

            al_flip_display();
            desenha = false;
        }
    }

    al_destroy_display(janela);
    al_destroy_timer(timer);
    al_destroy_event_queue(fila_eventos);
    al_destroy_bitmap(background);

    return 0;
}