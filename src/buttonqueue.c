#include "header/buttonqueue.h"
#include <time.h>

// IMPLEMENTAÇÃO DE FILA PARA ARMAZENAR OS BOTÕES E INIMIGOS


button_queue create_queue() {
    srand(time(NULL));
    button_queue bq;
    bq.qBmp = al_load_bitmap("./assets/q.png");
    bq.wBmp = al_load_bitmap("./assets/w.png");
    bq.eBmp = al_load_bitmap("./assets/e.png");
    bq.rBmp = al_load_bitmap("./assets/r.png");
    bq.inimBmp = al_load_bitmap("./assets/bandit.png");
    bq.head = NULL;
    bq.tail = NULL;
    return bq;
}

void add_queue(button_queue* q) {
    membro_fila* novoMembro = (membro_fila*) malloc(sizeof(membro_fila));
    if (novoMembro == NULL) exit(1);
    novoMembro->prox = NULL;
    LETRA l = rand() % 4;
    novoMembro->elemento.letra = l;
    novoMembro->elemento.bPosY = 600;
    novoMembro->elemento.alpha = 255;
    switch (l) {
        case Q:
            novoMembro->elemento.bBitmap = q->qBmp;
            break;
        case W:
            novoMembro->elemento.bBitmap = q->wBmp;
            break;
        case E:
            novoMembro->elemento.bBitmap = q->eBmp;
            break;
        case R:
            novoMembro->elemento.bBitmap = q->rBmp;
            break;
    }

    novoMembro->elemento.contFrames = novoMembro->elemento.contFrames = 0;
    novoMembro->elemento.iBitmap = q->inimBmp;
    novoMembro->elemento.iPosX = 800;

    if (q->head == NULL) {
        q->head = novoMembro;
        q->tail = novoMembro;
    }
    else { // Alterando o último elemento da fila
        q->tail->prox = novoMembro;
        q->tail = novoMembro;
    }
}

void pop_queue(button_queue* q) {
    if (q->head == q->tail) {
        free(q->head);
        q->head = q->tail = NULL;
    } else {
        membro_fila* proxHead = q->head->prox;
        free(q->head);
        q->head = proxHead;
    }
}

void queue_update_pos(button_queue* q, button_queue* mortos, float spd) {
    membro_fila* p = mortos->head;
    // Atualizando a transparência dos inimigos/botões apertados
    while (p != NULL) {
        if (p->elemento.alpha <= 0) pop_queue(mortos);
        else p->elemento.alpha -= 15;
        p = p->prox;
    }

    p = q->head;
    if (p == NULL) return;
    // Verificando se algum botão já saiu da tela
    if (p->elemento.bPosY <= -50) {
        kill(q, mortos);
        p = q->head;
    }
    do {
        // Atualiza a posição e a animação dos botões e inimigos
        if (p->elemento.contFrames >= 7) {
            p->elemento.currentFrame = (p->elemento.currentFrame + 1) % 7;
            p->elemento.contFrames = 0;
        } else p->elemento.contFrames++;


        p->elemento.bPosY -= spd;
        // Função de primeiro grau que relaciona a posição do botão e a posição do inimigo
        p->elemento.iPosX = (85.0 / 116.0) * p->elemento.bPosY + (10450.0 / 29.0);
        p = p->prox;
    } while (p != NULL);

    if (q->tail->elemento.bPosY <= 450) add_queue(q);
}

void destroy_queue(button_queue* q) {
    empty_queue(q);
    al_destroy_bitmap(q->qBmp);
    al_destroy_bitmap(q->wBmp);
    al_destroy_bitmap(q->eBmp);
    al_destroy_bitmap(q->rBmp);
    al_destroy_bitmap(q->inimBmp);
}

void empty_queue(button_queue* q) {
    membro_fila* p1 = q->head, *p2 = NULL;
    while (p1 != NULL) {
        p2 = p1->prox;
        free(p1);
        p1 = p2;
    }
    q->head = q->tail = NULL;
}

void button_monster_draw(button_queue* q, button_queue* mortos) {
    membro_fila* p = q->head;
    // Desenha os inimigos morrendo
    while (p != NULL) {
        al_draw_bitmap(p->elemento.bBitmap, 20 + 70*(p->elemento.letra), p->elemento.bPosY, 0);
        al_draw_scaled_bitmap(p->elemento.iBitmap, 48*(p->elemento.currentFrame), 48, 48, 48, p->elemento.iPosX, 340, 120, 120, 0);
        p = p->prox;
    }
    p = mortos->head;
    // Desenha os inimigos vivos
    while (p != NULL) {
        al_draw_tinted_bitmap(p->elemento.bBitmap, al_map_rgba(255, 255, 255, p->elemento.alpha), 20 + 70*(p->elemento.letra), p->elemento.bPosY, 0);
        al_draw_tinted_scaled_bitmap(p->elemento.iBitmap, al_map_rgba(255, 255, 255, p->elemento.alpha), 48*(p->elemento.currentFrame), 48, 48, 48, p->elemento.iPosX, 340, 120, 120, 0);
        p = p->prox;
    }
}

short check_acerto(button_queue* q, button_queue* mortos, int key) {
    membro_fila* botao = q->head;
    LETRA pressionada;
    if (botao == NULL) return 0;

    switch (key) {
        case ALLEGRO_KEY_Q:
            pressionada = Q;
            break;
        case ALLEGRO_KEY_W:
            pressionada = W;
            break;
        case ALLEGRO_KEY_E:
            pressionada = E;
            break;
        case ALLEGRO_KEY_R:
            pressionada = R;
            break;
    }

    if (pressionada == botao->elemento.letra) {
        if (absolute(botao->elemento.bPosY - 20) <= 5) { // Margem de erro de +-5 pixels
            kill(q, mortos);
            return 15;
        }
        else if (absolute(botao->elemento.bPosY - 20) <= 20) { // Margem de erro de +=20 pixels
            kill(q, mortos);
            return 5;
        }
        else return 0; // Retorna 0 (falso) se errou
    } else return 0;
}

float absolute(float x) {
    return (x >= 0 ? x : -x);
}


void kill(button_queue* q, button_queue* mortos) {
    if (q->head != NULL) {
        membro_fila* mortoMembro = (membro_fila*) malloc(sizeof(membro_fila));
        if (mortoMembro == NULL) exit(1);
        mortoMembro->prox = NULL;
        // Copiando o membro da fila a ser morto
        mortoMembro->elemento = q->head->elemento;
        pop_queue(q);

        // Atualizando as duas filas
        if (mortos->head == NULL) {
            mortos->head = mortoMembro;
            mortos->tail = mortoMembro;
        }
        else {
            mortos->tail->prox = mortoMembro;
            mortos->tail = mortoMembro;
        }
    }
}