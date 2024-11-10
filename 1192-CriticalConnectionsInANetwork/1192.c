#include <stdio.h>
#include <stdlib.h>

// Estrutura para armazenar as listas de adjacências
typedef struct {
    int *edges;
    int size;
    int capacity;
} AdjList;

// Variáveis globais
int timer;
int *ids;
int *low;
int *visited;
int **result;
int resultCount;

// Função para adicionar uma aresta em uma lista de adjacência
void adicionar_aresta(AdjList *graph, int a, int b) {
    if (graph[a].size == graph[a].capacity) {
        graph[a].capacity *= 2;
        graph[a].edges = realloc(graph[a].edges, graph[a].capacity * sizeof(int));
    }
    if (graph[b].size == graph[b].capacity) {
        graph[b].capacity *= 2;
        graph[b].edges = realloc(graph[b].edges, graph[b].capacity * sizeof(int));
    }
    graph[a].edges[graph[a].size++] = b;
    graph[b].edges[graph[b].size++] = a;
}

// Função DFS para encontrar pontes
void dfs(AdjList *graph, int at, int parent) {
    visited[at] = 1;
    ids[at] = low[at] = timer++;
    
    for (int i = 0; i < graph[at].size; i++) {
        int to = graph[at].edges[i];
        
        if (to == parent) continue; // Ignora a aresta para o nó pai
        
        if (!visited[to]) {
            dfs(graph, to, at);
            low[at] = (low[at] < low[to]) ? low[at] : low[to];
            
            // Se a aresta é uma ponte (conexão crítica)
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

// Função principal para encontrar todas as conexões críticas
int** criticalConnections(int n, int** connections, int connectionsSize, int* connectionsColSize, int* returnSize, int** returnColumnSizes) {
    
    timer = 0;
    resultCount = 0;
    result = (int**) malloc(connectionsSize * sizeof(int*));
    ids = (int*) malloc(n * sizeof(int));
    low = (int*) malloc(n * sizeof(int));
    visited = (int*) malloc(n * sizeof(int));

    // Inicializa a lista de adjacências
    AdjList *graph = (AdjList*) malloc(n * sizeof(AdjList));
    for (int i = 0; i < n; i++) {
        graph[i].edges = (int*) malloc(2 * sizeof(int));
        graph[i].size = 0;
        graph[i].capacity = 2;
        visited[i] = 0;
    }

    // Constroi o grafo adicionando as arestas por lista de adjacência
    for (int i = 0; i < connectionsSize; i++) {
        adicionar_aresta(graph, connections[i][0], connections[i][1]);
    }

    // Executa DFS para encontrar as pontes
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            dfs(graph, i, -1);
        }
    }

    // Configura o valor de retorno
    *returnSize = resultCount;
    *returnColumnSizes = (int*) malloc(resultCount * sizeof(int));
    for (int i = 0; i < resultCount; i++) {
        (*returnColumnSizes)[i] = 2;
    }

    // Libera memória alocada para o grafo
    for (int i = 0; i < n; i++) {
        free(graph[i].edges);
    }
    free(graph);
    free(ids);
    free(low);
    free(visited);

    return result;
}