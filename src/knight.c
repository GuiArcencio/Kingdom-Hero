#include "header/knight.h"
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

Knight* create_knight() {
    Knight* jogador = (Knight*) malloc(sizeof(Knight));
    if (jogador == NULL) exit(1);
    jogador->currentFrame = jogador->contFrame = 0;
    jogador->idleBitmap = al_load_bitmap("./assets/knightidle.png");
    jogador->attackBitmap = al_load_bitmap("./assets/knightattack.png");
    jogador->currentBitmap = jogador->idleBitmap;
    jogador->state = IDLE;
    jogador->alpha = 255;

    return jogador;
}

void destroy_knight(Knight* k) {
    al_destroy_bitmap(k->attackBitmap);
    al_destroy_bitmap(k->idleBitmap);
    free(k);
}

void knight_update_frame(Knight* p) {
    switch (p->state) {
        case IDLE:
            if (p->contFrame >= 12) {
                p->currentFrame = (p->currentFrame + 1) % 4;
                p->contFrame = 0;
            } else {
                p->contFrame++;
            }
            break;
        case ATTACK:
            if (p->contFrame >= 6) {
                if (p->currentFrame < 5) {
                    p->currentFrame = (p->currentFrame + 1) % 6;
                    p->contFrame = 0;
                } else {
                    p->state = IDLE;
                    p->currentBitmap = p->idleBitmap;
                    p->currentFrame = p->contFrame = 0;
                }
            } else {
                p->contFrame++;
            }
    }
}

void knight_draw(Knight* p) {
    al_draw_tinted_scaled_bitmap(p->currentBitmap, al_map_rgba(255, 255, 255, p->alpha),p->currentFrame * 180, 0, 180, 160, 300, 300, 180, 160, 0);
}

void knight_attack(Knight* p, AudioHandler* a) {
    if (p->state != ATTACK || p->currentFrame > 2) {
        p->state = ATTACK;
        p->currentBitmap = p->attackBitmap;
        p->contFrame = p->currentFrame = 0;
        audio_espada(a);
    }
}

char knight_die(Knight* p) {
    if (p->alpha > 0) p->alpha -= 3;
    return p->alpha;
}