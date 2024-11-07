
#include <stdio.h>
#include <stdlib.h>

typedef struct celula{
    int valor;
    celula **prox;
}celula;

celula* criar_lista(int n){
    celula **lista;
    lista = (int*)malloc(sizeof(int)*n);
    int valor = n;
    for(int i = 0; i<=n;i++){
        lista[i]->valor = i;
    }
    return lista;
}

void inserir_aresta(int v, int num, celula **lista, int n){
    
    celula *nova_celula;
    

    // loop para inserir vizinho
    for(int i = 0; i <= n;i++){
        if(lista[i] == num){
            while(lista[i]->prox != NULL){
                nova_celula->prox= NULL;
                nova_celula->valor = num;
                lista[i]->prox = nova_celula;
                
            }
        }
    }
}

int* shortestAlternatingPaths(int n, int** redEdges, int redEdgesSize, int* redEdgesColSize, int** blueEdges, int blueEdgesSize, int* blueEdgesColSize, int* returnSize) {
    celula *adjv = criar_lista(n);
    celula *adja = criar_lista(n);
    int status = 0; // 0 - red  1 - azul

    for(int i = 0; i <= redEdgesSize; i++){
        inserir_aresta(redEdges[i],redEdges[i], adjv,redEdgesSize );
    }
    for(int i = 0; i <= blueEdgesSize; i++){
        inserir_aresta(blueEdges[i],blueEdges[i], adja,blueEdgesSize );
    }

    

}