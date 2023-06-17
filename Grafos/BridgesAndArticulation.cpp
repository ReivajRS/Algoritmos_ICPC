// Time complexity O(V+E)

typedef vector<int> vi;
enum {UNVISITED = -1};

vector<vi> AL;
vi dfs_num, dfs_low, dfs_parent;
vector<bool> articulation_vertex;
int dfsNumberCounter, dfsRoot, rootChildren;

void articulationPointAndBridge(int u){
    dfs_low[u] = dfs_num[u] = dfsNumberCounter++;              // dfs_low[u]<=dfs_num[u]
    for (auto v : AL[u]){
        if (dfs_num[v] == UNVISITED){                          // a tree edge
            dfs_parent[v] = u;
            if (u == dfsRoot)
                ++rootChildren;                                // Caso especial, raiz
            articulationPointAndBridge(v);
            if (dfs_low[v] >= dfs_num[u])                      // Es un punto de articulacion
                articulation_vertex[u] = 1;
            if (dfs_low[v] > dfs_num[u])                       // Es un puente
                printf(" Edge (%d, %d) is a bridge\n", u, v);
            dfs_low[u] = min(dfs_low[u], dfs_low[v]);          // Actualizacion
        }
        else if (v != dfs_parent[u])                           // Evitar ciclo trivial
            dfs_low[u] = min(dfs_low[u], dfs_num[v]);          // Actualizacion
    }
}

int main(){
    // Num_Nodos (V), Num_Aristas (E)
    AL.assign(V, vi());
    // Lectura del grafo (NO dirigido)
    
    dfs_num.assign(V, UNVISITED);
    dfs_low.assign(V, 0);
    dfs_parent.assign(V, -1);
    articulation_vertex.assign(V, 0);
    dfsNumberCounter = 0;

    printf("Bridges:\n");
    for (int u = 0; u < V; ++u)
        if (dfs_num[u] == UNVISITED){
            dfsRoot = u;
            rootChildren = 0;
            articulationPointAndBridge(u);
            articulation_vertex[dfsRoot] = (rootChildren > 1); // Caso especial
        }

    printf("Articulation Points:\n");
    for (int u = 0; u < V; ++u)
        if (articulation_vertex[u])
            printf(" Vertex %d\n", u);

    return 0;
}