
#include <stdlib.h>
#include <string.h>

typedef struct celula {
    int valor;
    struct celula *prox;
} celula;

typedef struct {
    int node;
    int color;
    int dist;
} QueueNode;

celula** criar_lista(int n){
    celula **lista = (celula**)malloc(sizeof(celula*) * n);
    for (int i = 0; i < n; i++) {
        lista[i] = NULL;  // Inicializa cada lista como vazia
    }
    return lista;
}

void inserir_aresta(int v, int vizinho, celula **lista){
    
    celula *nova_celula = (celula*)malloc(sizeof(celula));
    nova_celula ->valor = vizinho;
    nova_celula ->prox = lista[v];
    lista[v] = nova_celula;
    
}

int* shortestAlternatingPaths(int n, int** redEdges, int redEdgesSize, int* redEdgesColSize, int** blueEdges, int blueEdgesSize, int* blueEdgesColSize, int* returnSize) {
    *returnSize = n;
    int *answer = malloc(sizeof(int)*n);
    for (int i = 0; i < n; i++) answer[i] = -1;
    
    celula **adjv = criar_lista(n);
    celula **adja = criar_lista(n);

    
    for (int i = 0; i < redEdgesSize; i++) {
        int from = redEdges[i][0];
        int to = redEdges[i][1];
        if (from >= 0 && from < n && to >= 0 && to < n) {
            inserir_aresta(from, to, adjv);
        }
    }

    for (int i = 0; i < blueEdgesSize; i++) {
        int from = blueEdges[i][0];
        int to = blueEdges[i][1];
        if (from >= 0 && from < n && to >= 0 && to < n) {
            inserir_aresta(from, to, adja);
        }
    }

    // BFS alternada

    QueueNode queue[2 * n];
    int primeiro = 0, ultimo =2; // aux para as operações de fila
   
    
    queue[ultimo-2] = (QueueNode){0, 0, 0};  // Começar com o nó 0 com aresta vermelha
    queue[ultimo-1] = (QueueNode){0, 1, 0};  // Começar com o nó 0 com aresta azul
    
    int visitados[n][2]; //matriz de vistados
    memset(visitados, 0, sizeof(visitados));
    
    visitados[0][0] = visitados[0][1] = 1;
    answer[0] = 0;

    while(primeiro < ultimo){
        QueueNode curr = queue[primeiro++];
        int proxCor = 1 - curr.color;
        celula *adjList = (proxCor == 0) ? adjv[curr.node] : adja[curr.node];

        while (adjList != NULL)
        {
            int vizinho = adjList->valor;
            if(!visitados[vizinho][proxCor]){
                visitados[vizinho][proxCor] = 1;
                queue[ultimo++] = (QueueNode){vizinho, proxCor, curr.dist + 1};
                if (answer[vizinho] == -1 || curr.dist + 1 < answer[vizinho]) {
                    answer[vizinho] = curr.dist + 1;
            }
        }
        adjList = adjList->prox;
               
           
        }
    }

    // Liberação da memória das listas de adjacência
    for (int i = 0; i < n; i++) {
        celula* temp = adjv[i];
        while (temp) {
            celula* next = temp->prox;
            free(temp);
            temp = next;
        }
    }
    free(adjv);
    free(adja);

    return answer;



}

