#define MAX 1000000

typedef struct No {
    int valor;
    struct No *prox;
} No;

typedef struct Fila {
    int *v;
    int p, u;
} Fila;

Fila *criar_fila(int n)
{
    Fila *f = malloc(sizeof(Fila));
    f->v = malloc(n * sizeof(int));
    f->p = f->u = 0;
    return f;
}

void enfileira(Fila *f, int x)
{
    f->v[f->u++] = x;
}

int desenfileira(Fila *f)
{
    return f->v[f->p++];
}

int vazia(Fila *f)
{
    return f->p == f->u;
}

void insere_aresta(No **adj, int u, int v)
{
    No *novo = malloc(sizeof(No));
    novo->valor = v;
    novo->prox = adj[u];
    adj[u] = novo;
}

int numBusesToDestination(int** routes, int routesSize, int* routesColSize, int source, int target) {
    if (source == target)
        return 0;
        
    No **adj = calloc(MAX, sizeof(No *));
    
    // Vetores para marcar as paradas e as rotas que já foram visitadas
    int *visitados_parada = calloc(MAX, sizeof(int));
    int *visitados_onibus = calloc(routesSize, sizeof(int));

    // Lista de adjacência com as rotas que passam pelas paradas
    for (int i = 0; i < routesSize; i++)
    {
        for (int j = 0; j < routesColSize[i]; j++)
            insere_aresta(adj, routes[i][j], i);
    }

    Fila *fila_rotas = criar_fila(MAX);
    Fila *fila_trocas = criar_fila(MAX);

    No *curr = adj[source];

    while (curr != NULL)
    {
        enfileira(fila_rotas, curr->valor);
        enfileira(fila_trocas, 1);
        visitados_onibus[curr->valor] = 1;
        curr = curr->prox;
    }

    // BFS
    while (!vazia(fila_rotas))
    {
        int rota = desenfileira(fila_rotas);
        int trocas = desenfileira(fila_trocas);

        // Explora todas as paradas da rota atual
        for (int j = 0; j < routesColSize[rota]; j++)
        {
            int parada = routes[rota][j];

            if (parada == target)
                return trocas;

            if (!visitados_parada[parada])
            {
                visitados_parada[parada] = 1;
                curr = adj[parada];

                // Explora todas as rotas que passam pela parada atual
                while (curr != NULL)
                {
                    if (!visitados_onibus[curr->valor])
                    {
                        enfileira(fila_rotas, curr->valor);
                        enfileira(fila_trocas, trocas + 1);
                        visitados_onibus[curr->valor] = 1;
                    }
                    curr = curr->prox;
                }
            }
        }
    }

    return -1;
}
