// Time complexity Preprocessing = O(n log n), Query = (log n)

typedef vector<int> vi;

int l;          // Logaritmo base 2 del numero de nodos del arbol, redondeado hacia arriba
vector<vi> adj; // Lista de adyacencia para representar el arbol
int timer;      // Tiempo en el que se visita cada nodo
vi tin, tout;   // Arreglos de tiempos de entrada y salida de cada nodo
vector<vi> up;  // Vector de los ancestros de cada nodo, donde up[i][j] es el ancestro 2^j del nodo i

void dfs(int v, int p){
    tin[v] = ++timer;
    up[v][0] = p;
    for (int i = 1; i <= l; ++i)
        up[v][i] = up[up[v][i-1]][i-1];

    for (int u : adj[v]) {
        if (u != p)
            dfs(u, v);
    }

    tout[v] = ++timer;
}

bool is_ancestor(int u, int v){ return tin[u] <= tin[v] && tout[u] >= tout[v]; }

int lca(int u, int v){
    if (is_ancestor(u, v))  return u;   // Si u es ancestro de v LCA(u,v)=u
    if (is_ancestor(v, u))  return v;   // Si v es ancestro de u LCA(u,v)=v

    for (int i = l; i >= 0; --i) {      // Se recorren los ancestros con saltos binarios
        if (!is_ancestor(up[u][i], v))
            u = up[u][i];
    }

    return up[u][0];                    // Se retorna el LCA
}

void preprocess(int root, int sz) {
    tin.resize(sz);
    tout.resize(sz);
    timer = 0;
    l = ceil(log2(sz));
    up.assign(sz, vector<int>(l + 1));
    dfs(root, root);
}