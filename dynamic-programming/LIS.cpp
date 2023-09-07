// Time complexity O(n log k), donde k es la longitud de la LIS
typedef vector<int> vi;

int n;
vi nums, prev;

void print_LIS(int i) {
    if (prev[i] == -1) { printf("%d", nums[i]); return; }
    print_LIS(prev[i]);
    printf(" %d", nums[i]);
}

int main() {
    int lis_sz = 0, lis_end = 0;
    vi L(n, 0), L_id(n, 0);
    prev.assign(n, -1);

    for (int i = 0; i < n; ++i) {
        int pos = lower_bound(L.begin(), L.begin() + lis_sz, nums[i]) - L.begin();
        L[pos] = nums[i], L_id[pos] = i, prev[i] = pos ? L_id[pos-1] : -1;
        if (pos == lis_sz)
            lis_sz = pos+1, lis_end = i;
    }

    printf("LIS length: %d\n", lis_sz);
    print_LIS(lis_end); printf("\n");

    return 0;
}
