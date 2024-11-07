#define MAX 1000000

typedef struct No {
    int valor;
    struct Node *prox;
} No;

int numBusesToDestination(int** routes, int routesSize, int* routesColSize, int source, int target) {
    No **adj = calloc(MAX, sizeof(No *));

    for (int i = 0; i < routesSize; i++)
    {
        for (int j = 0; j < routesColSize[i]; j++) 
            insere_aresta(adj, routes[i][j], i);
    }

    return 0;
}