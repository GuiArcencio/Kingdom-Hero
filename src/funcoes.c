-#include "header/funcoes.h"

#include <stdio.h>
#include <math.h>
#include <string.h>

float aumentaVelocidade(unsigned int pont){ //pont == pontuação
    return sqrt(pont/100.0) + 1;
}

void salvaRanking(Jogador j){ //Salva o nome e a pontuação em um arquivo
    FILE *p = fopen("Ranking.bin", "rb+");
    int numJogadores;  //Registra o número de jogadores no ranking
    if (p == NULL){ //Cria um novo arquivo e salva os dados do jogador
        FILE *fp = fopen("Ranking.bin", "wb+");
        fwrite(1, sizeof(int), 1, fp);
        fwrite(j.nome,sizeof(char),3,fp);
        fwrite(j.pont,sizeof(int),1,fp);
        fclose(fp);
    }else{
        int num = fread(numJogadores, sizeof(int), 1, p); // num recebe a quantidade de dados lida
        if((numJogadores < 5) || (num == 0))
            fwrite(numJogadores + 1, sizeof(int), 1, p);
        int i;
        Jogador jRanking[5]; //Jogadores que já estão no ranking
        for(i = 0; i < numJogadores; i++){
            fread(jRanking[i].nome,sizeof(char),3,p);
            fread(jRanking[i].pont,sizeof(int), 1,p);
            if(jRanking[i].pont < j.pont){
                fseek(p, -1 * sizeof(int), SEEK_CUR);
                fseek(p, -3 * sizeof(char), SEEK_CUR);
                fwrite(j.nome,sizeof(char),3,p);
                fwrite(j.pont,sizeof(int),1,p);
                /*Atribuindo às variáveis o nome e a pontuação do jogador substituído no
                ranking para efetuar nova verificação com os outros jogadores no ranking*/
                strcpy(j.nome,jRanking[i].nome);
                j.pont = jRanking[i].pont;
            }
        }
        fclose(p);
    }
}
/*void main(){
    int n;


    do{
        printf("Pontuacao = ");
        scanf("%i",&n);
        printf("Velocidade: %.7f\n\n\n\n", aumentaVelocidade(n));
    }while(n);
}*/
