// Time complexity: Build O(n log n), Query O(1)
typedef vector<int> vi;
inline int L2(int x) { return 31-__builtin_clz(x); }
inline int P2(int x) { return 1<<x; }

struct SparseTable {
    vi A;
    vector<vi> SpT;
    
    SparseTable(vi &initialA) : A(initialA){        // O(n log n)
        int n = (int)A.size(), L2_n = L2(n)+1;
        SpT = vector<vi>(L2(n)+1, vi(n));
        for (int j = 0; j < n; ++j)
            SpT[0][j] = j;
        for (int i = 1; P2(i) <= n; ++i)
            for (int j = 0; j+P2(i)-1 < n; ++j) {
                int x = SpT[i-1][j];
                int y = SpT[i-1][j+P2(i-1)];
                SpT[i][j] = A[x] <= A[y] ? x : y;   // Guarda el indice del elemento menor
            }
    }

    int RMQ(int i, int j) {                 // O(1) [i, r]
        int k = L2(j-i+1);
        int x = SpT[k][i];
        int y = SpT[k][j-P2(k)+1];
        return A[x] <= A[y] ? x : y;        // Retorna el indice del elemento menor
    }
};
