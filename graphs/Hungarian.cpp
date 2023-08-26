/*
    Descripcion: Dado un grafo bipartito con pesos, empareja cada nodo de la izquieda
    con un nodo de la derecha, de tal manera que no hay un nodo en 2 emparejamientos y
    la suma de los pesos de las aristas es minima.
    Toma coste[N][M], donde coste[i][j] = coste de L[i] para ser emparejado con R[j] y
    retorna (min cost, match), donde L[i] esta emparejado con R[match[i]].
    Negar los costos para el costo maximo.
    Time complexity: O(N^2 * M)
    Source: Kactl
*/

pair<int, vi> hungarian(const vector<vi> &a) {
    if (a.empty()) return {0, {}};
    int n = sz(a) + 1, m = sz(a[0]) + 1;
    vi u(n), v(m), p(m), ans(n - 1);
    for(int i = 1; i < n; i++){
        p[0] = i;
        int j0 = 0; // add "dummy" worker 0
        vi dist(m, INT_MAX), pre(m, -1);
        vector<bool> done(m + 1);
        do { // dijkstra
            done[j0] = true;
            int i0 = p[j0], j1, delta = INT_MAX;
            for(int j = 1; j < n; j++) if (!done[j]) {
                auto cur = a[i0 - 1][j - 1] - u[i0] - v[j];
                if (cur < dist[j]) dist[j] = cur, pre[j] = j0;
                if (dist[j] < delta) delta = dist[j], j1 = j;
            }
            for(int j = 0; j < m; j++){
                if (done[j]) u[p[j]] += delta, v[j] -= delta;
                else dist[j] -= delta;
            }
            j0 = j1;
        } while (p[j0]);
        while (j0) { // update alternating path
            int j1 = pre[j0];
            p[j0] = p[j1], j0 = j1;
        }
    }
    for(int j = 1; j < m; j++)
        if (p[j]) ans[p[j] - 1] = j - 1;
    return {-v[0], ans}; // min cost
}