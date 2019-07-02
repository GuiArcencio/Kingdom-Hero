#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <stdlib.h>

typedef enum { Q = 0, W = 1, E = 2, R = 3 } LETRA;

// Fila de botões/monstros

typedef struct {
    // Elementos referentes ao botão a ser pressionado
    ALLEGRO_BITMAP* bBitmap;
    float bPosY;
    LETRA letra;

} ButtonMonster;

typedef struct membro_fila {
    ButtonMonster elemento;
    struct membro_fila* prox;
} membro_fila;

typedef struct {
    ALLEGRO_BITMAP* qBmp, *wBmp, *eBmp, *rBmp;
    membro_fila* head, *tail;
} button_queue;

button_queue create_queue(); 

void add_queue(button_queue* q);

void pop_queue(button_queue* q);

void queue_update_pos(button_queue* q, float spd);

void destroy_queue(button_queue* q);

void button_monster_draw(button_queue* q);