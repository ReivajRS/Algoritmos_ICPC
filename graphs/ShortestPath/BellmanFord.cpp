// Time complexity O(V*E)

typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
const int INF = 1e9;

int main() {
    // Numero de nodos(V), numero de aristas(E), nodo inicio(s)
    vector<vii> AL(V, vii());

    // Ruta del Bellman Ford, basicamente relaja las E aristas V-1 veces
    vi dist(V, INF); dist[s] = 0;                   // Inicializacion en distancias infinitas
    for (int i = 0; i < V-1; ++i) {                 // total O(V*E)
        bool modified = false;                      // Optimizacion
        for (int u = 0; u < V; ++u)                 // Estos 2 ciclos = O(E)
        if (dist[u] != INF)                         // Verificacion importante
            for (auto &[v, w] : AL[u]) {
                if (dist[u]+w >= dist[v]) continue; // No hay mejora, saltar
                dist[v] = dist[u]+w;                // Operacion de relajacion
                modified = true;                    // Optimizacion
            }
        if (!modified) break;                       // Optimizacion
    }

    bool hasNegativeCycle = false;
    for (int u = 0; u < V; ++u)                     // Una pasada mas para verificar
        if (dist[u] != INF)
            for (auto &[v, w] : AL[u])
                if (dist[v] > dist[u]+w)            // Debe ser falso
                    hasNegativeCycle = true;        // Si true => Existe ciclo negativo
    printf("Negative Cycle Exist? %s\n", hasNegativeCycle ? "Yes" : "No");

    if (!hasNegativeCycle)
        for (int u = 0; u < V; ++u)
            printf("SSSP(%d, %d) = %d\n", s, u, dist[u]);

    return 0;
}