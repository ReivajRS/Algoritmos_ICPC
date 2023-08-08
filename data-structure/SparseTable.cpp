// Time complexity: Build O(n log n), Query O(1)
typedef vector<int> vi;
inline int L2(int x) { return 31-__builtin_clz(x); }
inline int P2(int x) { return 1<<x; }

struct SparseTable {
    vi A;           // Vector inicial
    vector<vi> SpT; // Sparse table
    
    SparseTable() {}
    SparseTable(vi &initialA) : A(initialA){        // O(n log n)
        int n = (int)A.size(), L2_n = L2(n)+1;
        SpT = vector<vi>(L2(n)+1, vi(n));           // Inicializacion
        for (int j = 0; j < n; ++j)
            SpT[0][j] = j;                          // RMQ del sub array [j..j]
        for (int i = 1; P2(i) <= n; ++i)            // Para toda i s.t. 2^i <= n
            for (int j = 0; j+P2(i)-1 < n; ++j) {   // Para toda j valida
                int x = SpT[i-1][j];                // [j..j+2^(i-1)-1]
                int y = SpT[i-1][j+P2(i-1)];        // [j+2^(i-1)..j+2^i-1]
                SpT[i][j] = A[x] <= A[y] ? x : y;   // Guarda el indice del elemento menor
            }
    }

    int RMQ(int i, int j) {                 // O(1)
        int k = L2(j-i+1);                  // 2^k <= (j-i+1)
        int x = SpT[k][i];                  // Cubre [i..i+2^k-1]
        int y = SpT[k][j-P2(k)+1];          // Cubre [j-2^k+1..j]
        return A[x] <= A[y] ? x : y;        // Retorna el indice del elemento menor
    }
};
