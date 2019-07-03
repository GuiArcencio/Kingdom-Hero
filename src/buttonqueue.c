#include "header/buttonqueue.h"
#include <time.h>

// IMPLEMENTAÇÃO DE FILA PARA ARMAZENAR OS BOTÕES E INIMIGOS
// #menotadiego


button_queue create_queue() {
    srand(time(NULL));
    button_queue bq;
    bq.qBmp = al_load_bitmap("./assets/q.png");
    bq.wBmp = al_load_bitmap("./assets/w.png");
    bq.eBmp = al_load_bitmap("./assets/e.png");
    bq.rBmp = al_load_bitmap("./assets/r.png");
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

void queue_update_pos(button_queue* q, float spd) {
    membro_fila* p = q->head;
    if (p == NULL) return;
    if (p->elemento.bPosY <= -50) {
        pop_queue(q);
        p = q->head;
    }
    do {
        p->elemento.bPosY -= spd;
        p = p->prox;
    } while (p != NULL);

    if (q->tail->elemento.bPosY <= 450) add_queue(q);
}

void destroy_queue(button_queue* q) {
    al_destroy_bitmap(q->qBmp);
    al_destroy_bitmap(q->wBmp);
    al_destroy_bitmap(q->eBmp);
    al_destroy_bitmap(q->rBmp);
    membro_fila* p1 = q->head, *p2 = NULL;
    while (p1 != NULL) {
        p2 = p1->prox;
        free(p1);
        p1 = p2;
    }
}

void button_monster_draw(button_queue* q) {
    membro_fila* p = q->head;
    while (p != NULL) {
        al_draw_bitmap(p->elemento.bBitmap, 20 + 70*(p->elemento.letra), p->elemento.bPosY, 0);
        p = p->prox;
    }
}