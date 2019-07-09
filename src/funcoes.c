#include "header/funcoes.h"
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

float aumentaVelocidade(unsigned int pont){ //pont == pontuação
    return sqrt(pont/100.0) + 1;
}

void salvaRanking(Jogador j){ //Salva o nome e a pontuação em um arquivo
    FILE *p = fopen("ranking.bin", "rb+");
    int numJogadores;  //Registra o número de jogadores no ranking
    if (p == NULL){ //Cria um novo arquivo e salva os dados do jogador
        p = fopen("ranking.bin", "wb");
        const int num = 1;
        fwrite(&num, sizeof(int), 1, p);
        fwrite(&j, sizeof(Jogador), 1, p);
        fclose(p);
    }else{
        fread(&numJogadores, sizeof(int), 1, p); // numJogadores recebe a quantidade de dados lida
        numJogadores++;
        Jogador* jRanking = (Jogador*) malloc(numJogadores*sizeof(Jogador)); //Jogadores que já estão no ranking
        if (jRanking == NULL) exit(1);
        int i;
        _Bool igual = 0;
        for(i = 0; i < numJogadores-1; i++){
             fread(jRanking, sizeof(Jogador), 1, p);
             if(strcmp(jRanking[i].nome,j.nome) == 0){
                igual = 1;
                if(j.pont > jRanking[i].pont){
                    jRanking[i] = j;
                    numJogadores--;
                }
             }
        }
        if(igual == 0){
        jRanking[numJogadores-1] = j; // Copia o novo jogador para o array
        qsort(jRanking, numJogadores, sizeof(Jogador), compareJogador); // Ordenando o vetor
        rewind(p);
        numJogadores = (numJogadores > 5 ? 5 : numJogadores); // Escrevendo, no máximo, 5 jogadores do ranking no arquivo
        fwrite(&numJogadores, sizeof(int), 1, p);
        fwrite(jRanking, sizeof(Jogador), numJogadores, p);
        fclose(p);

        free(jRanking);
        }else{
        qsort(jRanking, numJogadores, sizeof(Jogador), compareJogador); // Ordenando o vetor
        rewind(p);
        numJogadores = (numJogadores > 5 ? 5 : numJogadores); // Escrevendo, no máximo, 5 jogadores do ranking no arquivo
        fwrite(&numJogadores, sizeof(int), 1, p);
        fwrite(jRanking, sizeof(Jogador), numJogadores, p);
        fclose(p);

        free(jRanking);
        }
    }
}

Jogador* loadRanking(int* n) {
    *n = 0;
    FILE *p = fopen("ranking.bin", "rb");
    if (p == NULL) return NULL;
    fread(n, sizeof(int), 1, p);
    Jogador* v = (Jogador*) malloc((*n)*sizeof(Jogador));
    fread(v, sizeof(Jogador), *n, p);
    return v;
}

int compareJogador(const void* jogador1, const void* jogador2) { // Compara a pontuação de dois jogadores
    const Jogador* j1 = (Jogador*) jogador1, *j2 = (Jogador*) jogador2;
    return ( j2->pont - j1->pont );
}
