/**
 * Descripcion: Variante de la implementacion de Gabow para el algoritmo
 * de Edmonds-Blossom. Maximo emparejamiento sin peso para un grafo en
 * general, con 1-indexacion. Si despues de terminar la llamada a solve(),
 * white[v] = 0, v es parte de cada matching maximo.
 * Tiempo: O(NM), mas rapido en la practica.
 */
struct MaxMatching {
    int N;
    vector<vi> adj;
    vector<int> mate, first;
    vector<bool> white;
    vector<pi> label;

    MaxMatching(int _N) : N(_N), adj(vector<vi>(N + 1)), mate(vi(N + 1)), first(vi(N + 1)), label(vector<pi>(N + 1)), white(vector<bool>(N + 1)) {}

    void addEdge(int u, int v) { adj.at(u).pb(v), adj.at(v).pb(u); }

    int group(int x) {
        if (white[first[x]])
        first[x] = group(first[x]);
        return first[x];
    }
    void match(int p, int b) {
        swap(b, mate[p]);
        if (mate[b] != p)
            return;
        if (!label[p].second)
            mate[b] = label[p].first, match(label[p].first, b);  // vertex label
        else
            match(label[p].first, label[p].second), match(label[p].second, label[p].first);  // edge label
    }
    bool augment(int st) {
        assert(st);
        white[st] = 1;
        first[st] = 0;
        label[st] = {0, 0};

        queue<int> q;
        q.push(st);

        while (!q.empty()) {
        int a = q.front();
        q.pop();  // outer vertex
        for (auto& b : adj[a]) {
            assert(b);
            if (white[b]) {
                int x = group(a), y = group(b), lca = 0;
                while (x || y) {
                    if (y)
                    swap(x, y);
                    if (label[x] == pi{a, b}) {
                    lca = x;
                    break;
                    }
                    label[x] = {a, b};
                    x = group(label[mate[x]].first);
                }
                for (int v : {group(a), group(b)})
                    while (v != lca) {
                    assert(!white[v]);  // make everything along path white
                    q.push(v);
                    white[v] = true;
                    first[v] = lca;
                    v = group(label[mate[v]].first);
                    }
            } else if (!mate[b]) {
                mate[b] = a;
                match(a, b);
                white = vector<bool>(N + 1);  // reset
                return true;
            } else if (!white[mate[b]]) {
                white[mate[b]] = true;
                first[mate[b]] = b;
                label[b] = {0, 0};
                label[mate[b]] = pi{a, 0};
                q.push(mate[b]);
            }
        }
        }
        return false;
    }
    int solve() {
        int ans = 0;
        for(int st = 1; st < N +1; st++)
            if (!mate[st])
                ans += augment(st);
        for(int st = 1; st < N +1; st++)
            if (!mate[st] && !white[st])
                assert(!augment(st));
        return ans;
    }
};