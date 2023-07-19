// Sea A una matriz de orden n*n y k un numero, podemos calcular A^k en O(log k * n^3)
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef long long ll;
const ll MOD = 1e9+7;

vvi matrixMultiplication(vvi &A, vvi &B) {  // O(n^3)
    int n = A.size(), m = A[0].size(), k = B[0].size();
    vvi C(n, vi(k, 0));

    for(int i=0; i<n; i++)
        for(int j=0; j<k; j++)
            for(int l=0; l<m; l++)
                C[i][j] = (C[i][j] % MOD + (A[i][l] % MOD * B[l][j] % MOD) % MOD) % MOD;

    return C;
}

vvi matrixExponentiation(vvi &A, ll k) {    // O(log k * n^3)
    int n = A.size();

    vvi ret(n, vi(n)), B = A;  // Matriz identidad
    for(int i=0; i<n; i++)
        ret[i][i] = 1;
        
    while (k) {
        if (k & 1)
            ret = matrixMultiplication(ret, B);
        k >>= 1;
        B = matrixMultiplication(B, B);
    }

    return ret;
}
// Si el problema es el tiempo, implementar struct Matrix

/*
Estrategia para calcular el n-esimo fibonacci en O(log n):
  Utilizar la matriz de fibonacci:
A = {1, 1} ^ n
    {1, 0}
Donde
A = {F[n+1], F[n]  }
    {F[n]  , F[n-1]}
Utilizar exponenciacion binaria de la matriz, con 4 variables para que sea veloz.
*/