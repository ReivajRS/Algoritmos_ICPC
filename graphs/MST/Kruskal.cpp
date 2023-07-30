// Time complexity O(E log E)
typedef long long ll;
typedef vector<int> vi;
typedef tuple<int,int,int> iii;

// Union find utilizado para formar el MST
class UnionFind {
private:
    vi p, rank, setSize;
    int numSets;
public:
    UnionFind(int N) {
        p.assign(N, 0); for (int i = 0; i < N; ++i) p[i] = i;
        rank.assign(N, 0);
        setSize.assign(N, 1);
        numSets = N;
    }
    int findSet(int i) { return (p[i] == i) ? i : (p[i] = findSet(p[i])); }
    bool isSameSet(int i, int j) { return findSet(i) == findSet(j); }
    void unionSet(int i, int j) {
        if (isSameSet(i, j)) return;
        int x = findSet(i), y = findSet(j);
        if (rank[x] > rank[y]) swap(x, y);
        p[x] = y;
        if (rank[x] == rank[y]) ++rank[y];
        setSize[y] += setSize[x];
        --numSets;
    }
    int numDisjointSets() { return numSets; }
    int sizeOfSet(int i) { return setSize[findSet(i)]; }
};

int main() {
    int V, E;
    cin>>V>>E;
    vector<iii> EL(E);
    for (int i = 0; i < E; ++i) {
        int u, v, w;
        cin>>u>>v>>w;
        EL[i] = {w, u, v};
    }
    sort(EL.begin(), EL.end());
    ll mst_cost = 0, num_taken = 0;
    UnionFind UF(V+1);
    for (int i = 0; i < E; ++i) {
        auto [w, u, v] = EL[i];
        if (UF.isSameSet(u, v)) continue;
        mst_cost += w;
        UF.unionSet(u, v);
        ++num_taken;
        if (num_taken == V-1) break;
    }
    cout<<mst_cost<<" "<<num_taken;
    
  return 0;
}