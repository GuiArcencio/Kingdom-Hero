float aumentaVelocidade(unsigned int pont);


typedef struct player {
    char nome[4];
    unsigned int pont;
} Jogador;

void salvaRanking(Jogador j);
Jogador* loadRanking(int* n);

int compareJogador(const void* j1, const void* j2);