// Time complexity: Build O(n log n), Query O(1)

template <typename T>
struct SparseTable {
    vector<vector<T>> SpT;
    inline int L2(int x) { return 31-__builtin_clz(x); }
    inline int P2(int x) { return 1<<x; }
    
    SparseTable(vector<T> &initialA) {  // O(n log n)
        int n = SZ(initialA), LOG = L2(n) + 1;
        SpT.assign(LOG, vi(n));
        for (int j = 0; j < n; ++j)
            SpT[0][j] = initialA[j];
        for (int i = 1; i <= LOG; ++i)
            for (int j = 0; j+P2(i)-1 < n; ++j)
                SpT[i][j] = min(SpT[i-1][j], SpT[i-1][j + P2(i-1)]);
    }

    T RMQ(int i, int j) {   // O(1) [i, r]
        int k = L2(j-i+1);
        return min(SpT[k][i], SpT[k][j-P2(k)+1]);
    }
};
