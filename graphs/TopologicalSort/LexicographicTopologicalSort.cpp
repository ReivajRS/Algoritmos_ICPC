// Time complexity O(V+E)
typedef vector<int> vi;

int V, E;           // Numero de nodos y aristas
vector<vi> AL;      // Lista de adyacencia
vi in_degree;       // Grado de entrada de cada nodo
vi sorted_nodes;    // Nodos ordenados

void topo_sort() {
    priority_queue<int, vector<int>, greater<int>> q;

    for(int i=0; i<V; i++)
        if (in_degree[i] == 0)
            q.push(i);

    while (!q.empty()) {
        int u = q.top();
        q.pop();
        sorted_nodes.push_back(u);
        for (int v : AL[u]) {
            in_degree[v]--;
            if (in_degree[v] == 0)
                q.push(v);
        }
    }
}

int main() {
    // Numero de nodos(V), numero de aristas(E)
    AL.assign(V, vi());
    in_degree.assign(V, 0);

    // Leer el grafo e incrementar los grados de entrada en cada nodo

    topo_sort();
    
    if (sorted_nodes.size() < V) {
        cout << "El grafo tiene un ciclo" << '\n';
    } else {
        cout << "Orden topologico lexicograficamente menor: ";
        for (int u : sorted_nodes)
            cout << u << " ";
    }

    return 0;
}
