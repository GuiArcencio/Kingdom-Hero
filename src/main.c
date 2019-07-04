#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include <stdio.h>

#include "header/knight.h"
#include "header/buttonqueue.h"
#include "header/funcoes.h"

#define SCREEN_W 800 // largura da tela
#define SCREEN_H 600 // altura da tela

int main(void) {
    al_init();
    al_install_keyboard();
    al_init_image_addon();
    al_init_font_addon();
    al_init_ttf_addon();

    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0); // timer
    ALLEGRO_EVENT_QUEUE* fila_eventos = al_create_event_queue(); // fila de eventos
    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST); // opções para melhorar os gráficos
    al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);

    ALLEGRO_DISPLAY* janela = al_create_display(SCREEN_W, SCREEN_H); // janela
    al_set_window_title(janela, "Kingdom Hero");
    al_set_blender(ALLEGRO_ADD, ALLEGRO_ALPHA, ALLEGRO_INVERSE_ALPHA);

    ALLEGRO_FONT* fonte1 = al_load_font("./fonts/OpenSans-Bold.ttf", 28, ALLEGRO_ALIGN_CENTER);

    al_register_event_source(fila_eventos, al_get_keyboard_event_source()); // registra as fontes de eventos na fila de eventos
    al_register_event_source(fila_eventos, al_get_display_event_source(janela));
    al_register_event_source(fila_eventos, al_get_timer_event_source(timer));

    ALLEGRO_BITMAP* background = al_load_bitmap("./assets/background2.png");
    ALLEGRO_BITMAP* q0 = al_load_bitmap("./assets/qa.png");
    ALLEGRO_BITMAP* w0 = al_load_bitmap("./assets/wa.png");
    ALLEGRO_BITMAP* e0 = al_load_bitmap("./assets/ea.png");
    ALLEGRO_BITMAP* r0 = al_load_bitmap("./assets/ra.png");
    ALLEGRO_BITMAP* heart = al_load_bitmap("./assets/heart.png");

    bool sair = false;
    bool desenha = false;

    ALLEGRO_EVENT evento;
    
    bool vidas[3] = {true, true, true};
    short i, lucro = 0;
    unsigned int pontos = 0;
    float velocidade = 1;

    Knight* jogador = create_knight();
    AudioHandler* audio = audio_load();
    button_queue fila_botao = create_queue();
    button_queue fila_mortos = create_queue();
    add_queue(&fila_botao);

    al_start_timer(timer);
    while (!sair) {
        al_wait_for_event(fila_eventos, &evento);

        switch (evento.type) {
            case ALLEGRO_EVENT_TIMER:
                knight_update_frame(jogador);
                queue_update_pos(&fila_botao, &fila_mortos, velocidade, vidas);
                
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
                        knight_attack(jogador, audio);
                        lucro = check_acerto(&fila_botao, &fila_mortos, evento.keyboard.keycode);
                        pontos += lucro;
                        velocidade = aumentaVelocidade(pontos);
                        if (!lucro) 
                            for (i = 2; i >= 0; i--)
                                if (vidas[i])  {
                                    vidas[i] = false; // tira uma vida
                                    break;
                                }
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

            al_draw_scaled_bitmap(background, 0, 0, 1067, 1080, 0, 0, SCREEN_W, SCREEN_H, 0);
            al_draw_bitmap(q0, 20, 20, 0);
            al_draw_bitmap(w0, 90, 20, 0);
            al_draw_bitmap(e0, 160, 20, 0);
            al_draw_bitmap(r0, 230, 20, 0);
            al_draw_textf(fonte1, al_map_rgb(0, 0, 0), 500, 560, 0, "Pontos: %u", pontos);

            button_monster_draw(&fila_botao, &fila_mortos);

            for (i = 0; i < 3; i++) {
                if (vidas[i]) al_draw_scaled_bitmap(heart, 0, 0, 254, 254, 700 + i*30, 20, 25, 25, 0);
            }

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
    al_destroy_bitmap(heart);
    destroy_knight(jogador);
    destroy_audio(audio);
    destroy_queue(&fila_botao);
    destroy_queue(&fila_mortos);
    al_destroy_font(fonte1);

    return 0;
}
