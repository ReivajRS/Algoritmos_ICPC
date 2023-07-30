// Time complexity O(n log k)
typedef vector<int> vi;

int n;  // Tamaño del vector
vi A;   // Vector original
vi p;   // Vector de predecesor

void print_LIS(int i) {                          	// Rutina de backtracking
    if (p[i] == -1) { printf("%d", A[i]); return; }	// Caso base
    print_LIS(p[i]);                               	// backtrack
    printf(" %d", A[i]);
}

int main() {
    // Solucion O(n log k), n <= 200K
    int k = 0, lis_end = 0;
    vi L(n, 0), L_id(n, 0);
    p.assign(n, -1);

    for (int i = 0; i < n; ++i) {                  	// O(n)
        int pos = lower_bound(L.begin(), L.begin()+k, A[i]) - L.begin();	// Busqueda binaria
        L[pos] = A[i];                             	// greedily overwrite this
        L_id[pos] = i;                              // remember the index too
        p[i] = pos ? L_id[pos-1] : -1;              // predecessor info
        if (pos == k) {                             // can extend LIS?
        k = pos+1;                                 	// k = longer LIS by +1
        lis_end = i;                               	// keep best ending i
        }
    }

    printf("Final LIS is of length %d: ", k);
    print_LIS(lis_end); printf("\n");

    return 0;
}