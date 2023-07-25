// Time complexity O(V+E)
typedef pair<int, int> ii;
typedef vector<int> vi;
enum { UNVISITED = -1, VISITED = -2 };

vector<vi> AL;
vi dfs_num, ts;

void toposort(int u) {
    dfs_num[u] = VISITED;
    for (auto &v : AL[u])
        if (dfs_num[v] == UNVISITED)
            toposort(v);
        ts.push_back(u);    // Este es el unico cambio con respecto a un DFS
}

int main() {
    // El grafo tiene que ser DAG
    // Numero de nodos(V), numero de aristas(E)
    AL.assign(V, vi());

    dfs_num.assign(V, UNVISITED);
    ts.clear();
    for (int u = 0; u < V; ++u)                    // Igual que para encontrar los CCs
        if (dfs_num[u] == UNVISITED)
        toposort(u);

    printf("Topological sort: \n");
    reverse(ts.begin(), ts.end());                 // Invertir ts o imprimir al reves
    for (auto &u : ts)
        printf(" %d", u);
    printf("\n");

    return 0;
}