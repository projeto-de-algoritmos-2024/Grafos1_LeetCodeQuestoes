typedef struct No {
    int x;
    struct No *prox;
} No;

typedef struct Fila
{
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


bool possibleBipartition(int n, int** dislikes, int dislikesSize, int* dislikesColSize) {
    No **adj = calloc(n + 1, sizeof(No *));

    for (int i = 0; i < dislikesSize; i++)
    {
        No *novo = malloc(sizeof(No));
        novo->x = dislikes[i][1];
        novo->prox = NULL;

        if (adj[dislikes[i][0]] != NULL)
            novo->prox = adj[dislikes[i][0]];

        adj[dislikes[i][0]] = novo;
    }

}