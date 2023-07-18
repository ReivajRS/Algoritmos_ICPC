//Binomial Coefficient n choose k
//DP top down manner (memset initialization requiered)
ll comb[MAX][MAX];
 
ll nCk(ll n, ll k){
    if(k < 0 || k > n){
        return 0;
    }
 
    if(n == k || k == 0){
        return 1;
    }
 
    if(comb[n][k] != -1){
        return comb[n][k];
    }
 
    return comb[n][k] = (nCk(n - 1, k - 1) + nCk(n - 1, k)) % MOD;
}