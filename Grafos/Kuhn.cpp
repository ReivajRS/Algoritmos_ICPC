// Time complexity O(n*m)
typedef vector<int> vi;

int n, k;           // #Nodos en la primera parte del grafo(n), #Nodos en la segunda parte del grafo(k)
vector<vi> adj;     // Lista de adyacencia del grafo
vi mt;              // Conexiones del bm, donde mt[i] es el nodo de la primera parte conectado al nodo i de la segunda parte
vector<bool> used;  // Vector de visitados para el dfs
int maxMatch = 0;   // Tamaño del max matching

bool try_kuhn(int v) {
    if (used[v])
        return false;
    used[v] = true;
    for (int to : adj[v]) {
        if (mt[to] == -1 || try_kuhn(mt[to])) {
            mt[to] = v;
            return true;    // Retorna true si encuentra un augmenting path
        }
    }
    return false;           // Retorna false en caso contrario
}

int main() {
    // Lectura del grafo

    // Heuristica que consiste en tomar inicialmente cualquier matching valido y ejecutar el algoritmo a partir de ahi
    mt.assign(k, -1);
    vector<bool> used1(n, false);
    for (int v = 0; v < n; ++v) {
        for (int to : adj[v]) {
            if (mt[to] == -1) {
                mt[to] = v;
                used1[v] = true;
                break;
            }
        }
    }

    // Ejecucion del algoritmo
    for (int v = 0; v < n; ++v) {
        if (used1[v])
            continue;
        used.assign(n, false);
        try_kuhn(v);
    }

    for (int i = 0; i < k; ++i)
        if (mt[i] != -1){
            printf("%d %d\n", mt[i] + 1, i + 1);
            maxMatch++;
        }

    printf("Max match = %d\n", maxMatch);
}