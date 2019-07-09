#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include <stdio.h>

#include "header/knight.h"
#include "header/buttonqueue.h"
#include "header/funcoes.h"
#include "header/menu.h"
#include "header/comojogar.h"

#define SCREEN_W 800 // largura da tela
#define SCREEN_H 600 // altura da tela

typedef enum { MENU, JOGANDO, PERDENDO, OVER, RANKING, COMOJOGAR } GAME_STATE;

void escreverNome(char str[4], int letra);

int main(void) {
    al_init();
    al_install_keyboard();
    al_install_mouse();
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
    al_set_system_mouse_cursor(janela, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);

    ALLEGRO_FONT* fonte1 = al_load_font("./fonts/OpenSans-Bold.ttf", 28, 0);
    ALLEGRO_FONT* fonte2 = al_load_font("./fonts/OpenSans-Bold.ttf", 48, 0);
    ALLEGRO_FONT* fonte3 = al_load_font("./fonts/OpenSans-Bold.ttf", 90, 0);

    al_register_event_source(fila_eventos, al_get_keyboard_event_source()); // registra as fontes de eventos na fila de eventos
    al_register_event_source(fila_eventos, al_get_display_event_source(janela));
    al_register_event_source(fila_eventos, al_get_timer_event_source(timer));
    al_register_event_source(fila_eventos, al_get_mouse_event_source());

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
    char jNome[4] = "___";

    GAME_STATE estado = MENU;
    Jogador* jRanking = NULL;
    int nRanking;

    Menu* menu = menu_create();
    ComoJogar* como = como_jogar_create();

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
                if (estado == JOGANDO) {
                    knight_update_frame(jogador);
                    queue_update_pos(&fila_botao, &fila_mortos, velocidade);
                } else if (estado == PERDENDO) {
                    if (!knight_die(jogador)) estado = OVER;
                    queue_update_pos(&fila_botao, &fila_mortos, velocidade);
                } 
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
                        if (estado == JOGANDO) {
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
                            if (!vidas[0]) estado = PERDENDO;
                        }
                        break;
                    case ALLEGRO_KEY_ENTER:
                        if (estado == OVER && jNome[2] != '_') {
                            Jogador j;
                            strcpy(j.nome, jNome);
                            j.pont = pontos;
                            salvaRanking(j);
                            estado = RANKING;
                            jRanking = loadRanking(&nRanking);
                        } else if (estado == RANKING) {
                            empty_queue(&fila_botao);
                            empty_queue(&fila_mortos);
                            add_queue(&fila_botao);
                            pontos = 0;
                            strcpy(jNome, "___");
                            vidas[0] = vidas[1] = vidas[2] = true;
                            velocidade = 1;
                            jogador->alpha = 255;
                            jogador->state = IDLE;
                            jogador->currentBitmap = jogador->idleBitmap;
                            jogador->contFrame = jogador->currentFrame = 0;
                            estado = MENU;
                        }
                        break;
                    default: break;
                }
                break;
            case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
                switch (estado) {
                    case MENU:
                        if (evento.mouse.button == 1)
                            if (clique_iniciar(evento.mouse.x, evento.mouse.y))
                                estado = JOGANDO;
                            else if (clique_como_jogar(evento.mouse.x, evento.mouse.y))
                                estado = COMOJOGAR;
                        break;
                    case COMOJOGAR:
                        if (evento.mouse.button == 1) 
                            if (clique_iniciar2(evento.mouse.x, evento.mouse.y))
                                estado = JOGANDO;
                            else if (clique_menu(evento.mouse.x, evento.mouse.y))
                                estado = MENU;
                    default: break;
                }
                break;
            case ALLEGRO_EVENT_KEY_CHAR:
                if (estado == OVER) escreverNome(jNome, evento.keyboard.keycode);
                    break;
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                sair = true;
                break;
        }

        
        // desenhar na tela
        if (desenha && al_is_event_queue_empty(fila_eventos)) {
            al_clear_to_color(al_map_rgb(25, 39, 61));
             
            switch (estado) {
                case JOGANDO:
                case PERDENDO:
                    al_draw_scaled_bitmap(background, 0, 0, 1067, 1080, 0, 0, SCREEN_W, SCREEN_H, 0);
                    al_draw_bitmap(q0, 20, 20, 0);
                    al_draw_bitmap(w0, 90, 20, 0);
                    al_draw_bitmap(e0, 160, 20, 0);
                    al_draw_bitmap(r0, 230, 20, 0);
                    al_draw_textf(fonte1, al_map_rgb(0, 0, 0), 500, 560, ALLEGRO_ALIGN_CENTRE, "Pontos: %u", pontos);

                    button_monster_draw(&fila_botao, &fila_mortos);

                    for (i = 0; i < 3; i++) {
                        if (vidas[i]) al_draw_scaled_bitmap(heart, 0, 0, 254, 254, 700 + i*30, 20, 25, 25, 0);
                    }

                    knight_draw(jogador);
                    break;
                case MENU:
                    menu_draw(menu);
                    break;
                case COMOJOGAR:
                    como_jogar_draw(como);
                    break;
                case OVER:
                    al_draw_multiline_text(fonte2, al_map_rgb(255, 255, 255), 400, 50, 600, 70, ALLEGRO_ALIGN_CENTRE, "Você perdeu! Digite seu nome e pressione enter para entrar no ranking:");
                    al_draw_text(fonte3, al_map_rgb(255, 255, 255), 400, 350, ALLEGRO_ALIGN_CENTRE, jNome);
                    break;
                case RANKING:
                    al_draw_text(fonte2, al_map_rgb(255, 255, 255), 50, 50, 0, "Ranking");
                    al_draw_text(fonte1, al_map_rgb(255, 255, 255), 590, 550, ALLEGRO_ALIGN_CENTRE, "(pressione enter para voltar)");
                    short i;
                    for (i = 0; i < 5; i++) {
                        if (i < nRanking) 
                            al_draw_textf(fonte2, al_map_rgb(255, 255, 255), 200, 150 + i*50, 0, "%i: %s - %u", i+1, jRanking[i].nome, jRanking[i].pont);
                        else
                            al_draw_textf(fonte2, al_map_rgb(255, 255, 255), 200, 150 + i*50, 0, "%i:", i+1);
                    }
                    break;
            }
            al_flip_display();
            desenha = false;
        }
    }
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
    destroy_menu(menu);
    destroy_como_jogar(como);

    al_destroy_display(janela);

    return 0;
}

void escreverNome(char str[4], int letra) {
    short i;
    if (letra >= ALLEGRO_KEY_A && letra <= ALLEGRO_KEY_Z) {
        for (i = 0; i < 3; i++)
            if (str[i] == '_') {
                str[i] = al_keycode_to_name(letra)[0] - 32;
                break;
            }
    } else if (letra >= ALLEGRO_KEY_0 && letra <= ALLEGRO_KEY_9) {
        for (i = 0; i < 3; i++)
            if (str[i] == '_') {
                str[i] = al_keycode_to_name(letra)[0];
                break;
            }
    } else if (letra == ALLEGRO_KEY_BACKSPACE) {
        for (i = 2; i >= 0; i--)
            if (str[i] != '_') {
                str[i] = '_';
                break;
            }   
    }
}