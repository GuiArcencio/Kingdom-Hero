#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <stdlib.h>

typedef enum { Q = 0, W = 1, E = 2, R = 3 } LETRA;
typedef enum { VIVO, MORRENDO, MORTO } BUTTON_STATE;

// Fila de botões/monstros

typedef struct {
    // Elementos referentes ao botão a ser pressionado
    ALLEGRO_BITMAP* bBitmap;
    float bPosY;
    LETRA letra;
    unsigned int alpha;

    // Elementos referentes ao inimigo
    ALLEGRO_BITMAP* iBitmap;
    float iPosX;
    unsigned short contFrames, currentFrame;

} ButtonMonster;

typedef struct membro_fila {
    ButtonMonster elemento;
    struct membro_fila* prox;
} membro_fila;

typedef struct {
    ALLEGRO_BITMAP* qBmp, *wBmp, *eBmp, *rBmp, *inimBmp;
    membro_fila* head, *tail;
} button_queue;

button_queue create_queue(); 

void add_queue(button_queue* q);

void pop_queue(button_queue* q);

void queue_update_pos(button_queue* q, button_queue* mortos, float spd, bool* vidas);

void destroy_queue(button_queue* q);

void button_monster_draw(button_queue* q, button_queue* mortos);

short check_acerto(button_queue* q, button_queue* mortos, int key); // Verifica o tanto de pontos ganhos

float absolute(float x);

void kill(button_queue* q, button_queue* mortos);