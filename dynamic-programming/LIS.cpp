// Time complexity O(n log k)
typedef vector<int> vi;

int n;
vi A;
vi p;   // Vector de predecesor

void print_LIS(int i) {
    if (p[i] == -1) { printf("%d", A[i]); return; }
    print_LIS(p[i]);
    printf(" %d", A[i]);
}

int main() {
    // Solucion O(n log k), n <= 200K
    int k = 0, lis_end = 0;
    vi L(n, 0), L_id(n, 0);
    p.assign(n, -1);

    for (int i = 0; i < n; ++i) {                  	// O(n)
        int pos = lower_bound(L.begin(), L.begin()+k, A[i]) - L.begin();
        L[pos] = A[i];
        L_id[pos] = i;
        p[i] = pos ? L_id[pos-1] : -1;
        if (pos == k) {
            k = pos+1;
            lis_end = i;
        }
    }

    printf("Final LIS is of length %d: ", k);
    print_LIS(lis_end); printf("\n");

    return 0;
}
