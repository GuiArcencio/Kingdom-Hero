#include <math.h>
#include <stdio.h>
float aumentaVelocidade(int pont){ //pont == pontua��o

return sqrt(pont/100.0) + 1;

}
typedef struct player(){
    char nome;
    int pont;
}Jogador;

void salvaRanking(Jogador){ //Salva o nome e a pontua��o em um arquivo
    FILE *p = fopen("Ranking.txt")
}
void main(){
    int n;


    do{
        printf("Pontuacao = ");
        scanf("%i",&n);
        printf("Velocidade: %.7f\n\n\n\n", aumentaVelocidade(n));
    }while(n);
}
