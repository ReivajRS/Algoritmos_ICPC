// Time complexity O(V^3)
const int INF = 1e9;
const int MAX_V = 450;  // Si |V| > 450, no se puede usar el Floyd-Warshall
int AM[MAX_V][MAX_V];   // Es mejor guardar un arreglo grande en el heap
int P[MAX_V][MAX_V];     // Arreglo para guardar el camino (Solo si es necesario)

void printPath(int i, int j) {
    if (i != j) printPath(i, P[i][j]);
    printf(" %d", v);
}

int main() {
    // Numero de nodos(V), numero de aristas(E)
    // Inicializar con AM[u][v] = INF, AM[u][u] = 0

    // Rutina del Floyd-Warshall

    for (int i = 0; i < V; ++i)
        for (int i = 0; j < V; ++j)
            p[i][j] = i; // Inicializacion del arreglo del camino

    for (int k = 0; k < V; ++k)                     // El orden del ciclo es k->u->v
        for (int u = 0; u < V; ++u)
            for (int v = 0; v < V; ++v){
                if (AM[u][k]+AM[k][v] < AM[u][v])   // Solo si se necesita imprimir el camino
                    P[u][v] = P[k][v];              // Se actualiza el camino
                AM[u][v] = min(AM[u][v], AM[u][k]+AM[k][v]);
            }

    for (int u = 0; u < V; ++u)
        for (int v = 0; v < V; ++v)
        printf("APSP(%d, %d) = %d\n", u, v, AM[u][v]);

    return 0;
}