// Time complexity: Build O(n log n), Query O(1)
typedef vector<int> vi;

class SparseTable {
private:
    vi A, P2, L2;       // Vector base, potencias de 2 y logaritmos base 2
    vector<vi> SpT;     // La Sparse Table
public:
    SparseTable() {}    // Constructor default

    SparseTable(vi &initialA) : A(initialA){        // Rutina de preprocesamiento
        int n = (int)A.size(), L2_n = (int)log2(n)+1;
        P2.assign(L2_n, 0), L2.assign(1<<L2_n, 0);
        for (int i = 0; i <= L2_n; ++i) {
            P2[i] = (1<<i);                         // Para acelerar 2^i
            L2[(1<<i)] = i;                         // Para acelerar log_2(i)
        }
        for (int i = 2; i < P2[L2_n]; ++i)
            if (L2[i] == 0)
                L2[i] = L2[i-1];                    // Para llenar los vacios

        // Inicializacion
        SpT = vector<vi>(L2[n]+1, vi(n));
        for (int j = 0; j < n; ++j)
            SpT[0][j] = j;                          // RMQ del sub array [j..j]

        // Ciclos con complejidad total O(n log n)
        for (int i = 1; P2[i] <= n; ++i)            // Para toda i s.t. 2^i <= n
            for (int j = 0; j+P2[i]-1 < n; ++j) {   // Para toda j valida
                int x = SpT[i-1][j];                // [j..j+2^(i-1)-1]
                int y = SpT[i-1][j+P2[i-1]];        // [j+2^(i-1)..j+2^i-1]
                SpT[i][j] = A[x] <= A[y] ? x : y;   // Guarda el indice del elemento menor
            }
    }

    int RMQ(int i, int j) {
        int k = L2[j-i+1];              // 2^k <= (j-i+1)
        int x = SpT[k][i];              // Cubre [i..i+2^k-1]
        int y = SpT[k][j-P2[k]+1];      // Cubre [j-2^k+1..j]
        return A[x] <= A[y] ? x : y;    // Retorna el indice del elemento menor
    }
};