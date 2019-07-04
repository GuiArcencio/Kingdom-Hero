#include "header/funcoes.h"

#include <stdio.h>
#include <math.h>

float aumentaVelocidade(unsigned int pont){ //pont == pontua��o
    return sqrt(pont/100.0) + 1;
}

void salvaRanking(Jogador j){ //Salva o nome e a pontua��o em um arquivo
    FILE *p = fopen("Ranking.txt", "rb");
}
/*void main(){
    int n;


    do{
        printf("Pontuacao = ");
        scanf("%i",&n);
        printf("Velocidade: %.7f\n\n\n\n", aumentaVelocidade(n));
    }while(n);
}*/
