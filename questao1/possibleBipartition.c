typedef struct No {
    int x;
    struct No *prox;
} No;

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