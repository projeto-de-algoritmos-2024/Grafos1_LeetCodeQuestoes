
#include <stdio.h>
#include <stdlib.h>

typedef struct celula{
    int valor;
    celula **prox;
}celula;

celula* criar_lista(int n){
    celula *lista;
    lista = (int*)malloc(sizeof(int)*n);
    return lista;
}

void inserir_aresta(int v, int num, celula **lista, int n){
    
    celula *nova_celula;
    

    // loop para inserir vizinho
    for(int i = 0; i <= n;i++){
        if(lista[i] == num){
            while(lista[i]->prox != NULL){
                lista[i]->prox = nova_celula;
                nova_celula ->prox = NULL;
            }
        }
    }
}

int* shortestAlternatingPaths(int n, int** redEdges, int redEdgesSize, int* redEdgesColSize, int** blueEdges, int blueEdgesSize, int* blueEdgesColSize, int* returnSize) {
    
}