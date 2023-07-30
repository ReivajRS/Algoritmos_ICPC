// Time complexity O(V + E)
typedef vector<int> vi;

int dfsNumberCounter, numSCC;                           // Variables globales
vector<vi> AL;
vi dfs_num, dfs_low, visited;
stack<int> St;

void tarjanSCC(int u) {
    dfs_low[u] = dfs_num[u] = dfsNumberCounter;         // dfs_low[u]<=dfs_num[u]
    dfsNumberCounter++;                                 // Incrementa el contador
    St.push(u);                                         // Para recordar el orden
    visited[u] = 1;

    for (auto v : AL[u]) {
        if (dfs_num[v] == -1)                           // No visitado
            tarjanSCC(v);
        if (visited[v])                                 // Condicion de actualizacion
            dfs_low[u] = min(dfs_low[u], dfs_low[v]);
    }

    if (dfs_low[u] == dfs_num[u]) {                     // Raiz o inicio de un SCC
        ++numSCC;                                       // Se aumenta el numero de SCC
        while (1) {
            int v = St.top(); St.pop(); visited[v] = 0;
            if (u == v) break;
        }
    }
}

int main() {
    // Num_Nodos (V), Num_Aristas (E)
    AL.assign(V,vi());
    // Lectura del grafo (Dirigido)

    // Ejecucion del algoritmo de Tarjan
    dfs_num.assign(V, -1); dfs_low.assign(V, 0); visited.assign(V, 0);
    while (!St.empty()) St.pop();
    dfsNumberCounter = numSCC = 0;

    for (int u = 0; u < V; ++u)
        if (dfs_num[u] == -1)   // No visitado
            tarjanSCC(u);

    // Imprime cuantos SCC tiene el grafo
    printf("Number of SCC: %d\n", numSCC);

    return 0;
}