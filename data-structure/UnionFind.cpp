// Union-Find Disjoint Set usando las heuristicas de compresion de camino y union por rango
typedef vector<int> vi;

class UnionFind {
 private:
    vi p, rank, setSize;
    int numSets;
 public:
    UnionFind(int N) : p(N, 0), rank(N, 0), setSize(N, 1), numSets(N) {
        for (int i = 0; i < N; ++i) p[i] = i;
    }
    int findSet(int i) { return (p[i] == i) ? i : (p[i] = findSet(p[i])); }
    bool isSameSet(int i, int j) { return findSet(i) == findSet(j); }
    int numDisjointSets() { return numSets; }
    int sizeOfSet(int i) { return setSize[findSet(i)]; }
    void unionSet(int i, int j) {
        if (isSameSet(i, j)) return;
        int x = findSet(i), y = findSet(j);
        if (rank[x] > rank[y]) swap(x, y);          // Para mantener x mas pequenio que y
        p[x] = y;
        if (rank[x] == rank[y]) ++rank[y];          // Acelaracion por rango
        setSize[y] += setSize[x];
        --numSets;
    }
};
