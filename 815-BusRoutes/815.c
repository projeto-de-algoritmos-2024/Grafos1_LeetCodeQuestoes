#define MAX 1000000

typedef struct No {
    int valor;
    struct Node *prox;
} No;

int numBusesToDestination(int** routes, int routesSize, int* routesColSize, int source, int target) {
    No **adj = calloc(MAX, sizeof(No *));
}