float aumentaVelocidade(unsigned int pont); // Função para o aumento gradual de velocidade

typedef struct player {
    char nome[4];
    unsigned int pont;
} Jogador;

void salvaRanking(Jogador j); // Função para salvar o jogador no arquivo do ranking
Jogador* loadRanking(int* n); // Função para carregar os jogadores no ranking

int compareJogador(const void* j1, const void* j2); // Comparador para a função qsort