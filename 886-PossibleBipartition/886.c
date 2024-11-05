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

int eh_bipartido(No **adj, int V)
{
    Fila *fila = criar_fila(V);
    int *cor = malloc(V * sizeof(int));

    for (int i = 0; i < V; i++)
        cor[i] = -1;

    for (int i = 0; i < V; i++)
    {
        if (cor[i] == -1)
        {
            enfileira(fila, i);
            cor[i] = 0;

            while (!vazia(fila))
            {
                int u = desenfileira(fila);

                No *curr = adj[u];

                while (curr != NULL)
                {
                    if (cor[curr->x] == -1)
                    {
                        cor[curr->x] = 1 - cor[u];
                        enfileira(fila, curr->x);
                    }
                    else if (cor[curr->x] == cor[u])
                        return 0;

                    curr = curr->prox;
                }
            }
        }
    }

    return 1;
}

bool possibleBipartition(int n, int** dislikes, int dislikesSize, int* dislikesColSize) {
    No **adj = calloc(n + 1, sizeof(No *));

    for (int i = 0; i < dislikesSize; i++)
    {
        No *novo = malloc(sizeof(No));
        novo->x = dislikes[i][1];
        novo->prox = adj[dislikes[i][0]];
        adj[dislikes[i][0]] = novo;

        novo = malloc(sizeof(No));
        novo->x = dislikes[i][0];
        novo->prox = adj[dislikes[i][1]];
        adj[dislikes[i][1]] = novo;
    }

    return eh_bipartido(adj, n + 1);
}