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
    unsigned char alpha;

    // Elementos referentes ao inimigo
    ALLEGRO_BITMAP* iBitmap;
    float iPosX;
    unsigned short contFrames, currentFrame;

} ButtonMonster;

typedef struct membro_fila { // Membro da fila
    ButtonMonster elemento;
    struct membro_fila* prox;
} membro_fila;

typedef struct { // Estrutura contendo a fila em si
    ALLEGRO_BITMAP* qBmp, *wBmp, *eBmp, *rBmp, *inimBmp;
    membro_fila* head, *tail;
} button_queue;

button_queue create_queue(); // Criar a fila

void add_queue(button_queue* q); // Adicionar um botão à fila

void pop_queue(button_queue* q); // Retirar um botão da fila

void queue_update_pos(button_queue* q, button_queue* mortos, float spd);
// Atualizar a posição, frame dos botões e inimigos e verificar aqueles que passaram da tela

void destroy_queue(button_queue* q);
// Destruir a fila

void button_monster_draw(button_queue* q, button_queue* mortos);
// Desenhar os botões e inimigos na tela

short check_acerto(button_queue* q, button_queue* mortos, int key); // Verifica o tanto de pontos ganhos

float absolute(float x); // Função para cálculo de módulo

void empty_queue(button_queue* q); // Esvaziar a fila

void kill(button_queue* q, button_queue* mortos); // Sinaliza que um inimigo foi atacado e está morrendo