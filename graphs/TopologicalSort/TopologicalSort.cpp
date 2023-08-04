// Time complexity O(V+E)
typedef vector<int> vi;

vector<vi> AL;
vector<bool> visited;
vi ts;

void toposort(int u) {
    visited[u] = 1;
    for (auto &v : AL[u])
        if (!visited[v])
            toposort(v);
    ts.push_back(u);    // Este es el unico cambio con respecto a un DFS
}

int main() {
    // El grafo tiene que ser DAG
    // Numero de nodos(V), numero de aristas(E)
    AL.assign(V, vi());

    visited.assign(V, 0);
    ts.clear();
    for (int u = 0; u < V; ++u)                    // Igual que para encontrar los CCs
        if (!visited[u])
            toposort(u);

    printf("Topological sort: \n");
    reverse(ts.begin(), ts.end());                 // Invertir ts o imprimir al reves
    for (auto &u : ts)
        printf(" %d", u);
    printf("\n");

    return 0;
}
