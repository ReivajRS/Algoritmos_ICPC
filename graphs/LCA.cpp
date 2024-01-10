// Time complexity Preprocessing = O(n log n), Query = (log n)

typedef vector<int> vi;

int LOG;
vi depth;
vector<vi> g, up;

void dfs(int u, int p = -1) {
    for (auto &v : g[u]) {
        if (v == p)
            continue;
        depth[v] = depth[u] + 1;
        up[v][0] = u;
        for (int i = 1; i < LOG; i++)
            up[v][i] = up[up[v][i - 1]][i - 1];
        dfs(v, u);
    }
}

void build(int root, int n) {
    LOG = ceil(log2(n)) + 1;
    depth.resize(n);
    up.assign(n, vi(LOG));
    depth[root] = 0;
    dfs(root);
}

int lca(int a, int b) {
    if (depth[a] < depth[b])
        swap(a, b);
    int dif = depth[a] - depth[b];
    for (int i = LOG - 1; i >= 0; i--) {
        if (dif & (1 << i))
            a = up[a][i];
    }
    if (a == b)
        return a;
    for (int i = LOG - 1; i >= 0; i--) {
        if (up[a][i] != up[b][i]) {
            a = up[a][i];
            b = up[b][i];
        }
    }

    return up[a][0];
}
