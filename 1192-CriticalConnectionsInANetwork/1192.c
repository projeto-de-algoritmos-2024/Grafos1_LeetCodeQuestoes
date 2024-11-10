#include <stdio.h>
#include <stdlib.h>


typedef struct {
    int *aresta;
    int tamanho;
    int capacidade;
} AdjList;


int timer;
int *ids;
int *low;
int *visited;
int **result;
int resultCount;


void adicionar_aresta(AdjList *graph, int a, int b) {
    if (graph[a].tamanho == graph[a].capacidade) {
        graph[a].capacidade *= 2;
        graph[a].aresta = realloc(graph[a].aresta, graph[a].capacidade * sizeof(int));
    }
    if (graph[b].tamanho == graph[b].capacidade) {
        graph[b].capacidade *= 2;
        graph[b].aresta = realloc(graph[b].aresta, graph[b].capacidade * sizeof(int));
    }
    graph[a].aresta[graph[a].tamanho++] = b;
    graph[b].aresta[graph[b].tamanho++] = a;
}


void dfs(AdjList *graph, int at, int parent) {
    visited[at] = 1;
    ids[at] = low[at] = timer++;
    
    for (int i = 0; i < graph[at].tamanho; i++) {
        int to = graph[at].aresta[i];
        
        if (to == parent) continue; 
        
        if (!visited[to]) {
            dfs(graph, to, at);
            low[at] = (low[at] < low[to]) ? low[at] : low[to];
            
            
            if (ids[at] < low[to]) {
                result[resultCount] = (int*)malloc(2 * sizeof(int));
                result[resultCount][0] = at;
                result[resultCount][1] = to;
                resultCount++;
            }
        } else {
            low[at] = (low[at] < ids[to]) ? low[at] : ids[to];
        }
    }
}


int** criticalConnections(int n, int** connections, int connectionsSize, int* connectionsColSize, int* returnSize, int** returnColumnSizes) {
    
    timer = 0;
    resultCount = 0;
    result = (int**) malloc(connectionsSize * sizeof(int*));
    ids = (int*) malloc(n * sizeof(int));
    low = (int*) malloc(n * sizeof(int));
    visited = (int*) malloc(n * sizeof(int));

   
    AdjList *graph = (AdjList*) malloc(n * sizeof(AdjList));
    for (int i = 0; i < n; i++) {
        graph[i].aresta = (int*) malloc(2 * sizeof(int));
        graph[i].tamanho = 0;
        graph[i].capacidade = 2;
        visited[i] = 0;
    }

    
    for (int i = 0; i < connectionsSize; i++) {
        adicionar_aresta(graph, connections[i][0], connections[i][1]);
    }

    
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            dfs(graph, i, -1);
        }
    }

    
    *returnSize = resultCount;
    *returnColumnSizes = (int*) malloc(resultCount * sizeof(int));
    for (int i = 0; i < resultCount; i++) {
        (*returnColumnSizes)[i] = 2;
    }

    
    for (int i = 0; i < n; i++) {
        free(graph[i].aresta);
    }
    free(graph);
    free(ids);
    free(low);
    free(visited);

    return result;
}