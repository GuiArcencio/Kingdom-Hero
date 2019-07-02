#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

typedef enum { IDLE, ATTACK } KNIGHT_STATE;

typedef struct Knight{
    ALLEGRO_BITMAP* idleBitmap, *attackBitmap, *currentBitmap;
    unsigned short currentFrame, contFrame;
    KNIGHT_STATE state;
} Knight;

Knight* create_knight(); // Função para a criação do cavaleiro
void destroy_knight(Knight* k); // Função para eliminação do cavaleiro da memória

void knight_update_frame(Knight* p); // Atualizar o gráfico do cavaleiro

void knight_draw(Knight* p); // Desenhar o cavaleiro na tela
void knight_attack(Knight* p); // Mudar para animação de ataque