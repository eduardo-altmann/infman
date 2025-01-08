#include "top5.h"
#include "raylib.h"
#include <stdio.h>

bool le_arquivo(char nome_arq[], JOGADOR top5[MAXSCORES]){
    FILE *arq = fopen(nome_arq, "rb");
    int i = 0;
    if (!arq) {
        printf("\nERRO NA ABERTURA DO ARQUIVO %s", nome_arq);
        return false;
    } else {
            if(fread(top5, sizeof(JOGADOR)*MAXSCORES, 1, arq) == 1){
                printf("\nArquivo carregado com sucesso para o array");
            } else{
                printf("\nErro no carregamento para o array. Abortar");
                return false;
            }
        }
        fclose(arq);
        return true;
}

bool salva_arquivo(char nome_arq[], JOGADOR top5[MAXSCORES]){
    FILE *arq = fopen(nome_arq, "wb");
    if(!arq){
        printf("\nErro na escrita! Abortar");
        return false;
    } else {
        if(fwrite(top5, sizeof(JOGADOR)*MAXSCORES, 1, arq) == 1){
            printf("\nArray escrito corretamente no arquivo");
        } else {
            printf("\nArray escrito incorretamente no arquivo");
            return false;
        }
        fclose(arq);
        return true;
    }
}

void troca_info_array(JOGADOR top5[], JOGADOR novoj, int posicao){
    top5[posicao] = novoj;
}

void imprime_top5(JOGADOR top5[]){
    for (int i = 0; i < MAXSCORES; i++){
        
        printf("\n%s: %d pontos", top5[i].nome, top5[i].pontos);
    }
}

//usando selection sort
void reorganizaArray(JOGADOR top5[]) {
    for (int i = 0; i < MAXSCORES - 1; i++) {
        int maxIdx = i;
        for (int j = i + 1; j < MAXSCORES; j++) {
            if (top5[j].pontos > top5[maxIdx].pontos) {
                maxIdx = j;
            }
        }

        if (maxIdx != i) {
            JOGADOR temp = top5[i];
            top5[i] = top5[maxIdx];
            top5[maxIdx] = temp;
        }
    }
}
