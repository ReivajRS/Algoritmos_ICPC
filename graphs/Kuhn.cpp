// Time complexity O(n*m)
// Source: CP algorithms
typedef vector<int> vi;

struct Kuhn{
    int n, k;           // #Nodos en la primera parte del grafo(n), #Nodos en la segunda parte del grafo(k)_
    vector<vi> adj;     // Lista de adyacencia del grafo
    vi mt;              // Conexiones del bpm, donde mt[i] es el nodo de la primera parte conectado al nodo i de la segunda parte
    vector<bool> used;  // Vector de visitados para el dfs

    Kuhn(int _n, int _k) : n(_n), k(_k), adj(max(_n, _k) + 1), mt(_k, -1) {}

    void add_edge(int u, int v) { adj[u].push_back(v); }

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

    int mcbm(){
        for (int v = 0; v < n; ++v) {
            used.assign(n, false);
            try_kuhn(v);
        }

        int maxMatch = 0;

        for (int i = 0; i < k; ++i)
            if (mt[i] != -1){
                // printf("%d %d\n", mt[i] + 1, i + 1);
                maxMatch++;
            }
        return maxMatch;
    }
};
