/**
 * Dada un palo de madera de longitud de n unidades. El palo esta etiquetado desde 0 hasta n
 * Dado un arreglo de enteros cuts, donde cuts[i] denota una posicion donde debes hacer un corte
 * El orden de los cortes se puede cambiar, como se desee.
 * El coste de un corte es la longitud del palo a ser cortado, el coste total es la suma de todos los cortes.
 * Cuando cortas un palo, se divide en 2 palos mas pequenios.
 * Retornar el minimo coste de hacer todos los cortes.
*/

int dp[105][105];

int solve(int l, int r, vector<int>& cuts){
    if(l + 1 >= r)
        return 0;
    if(dp[l][r] != -1)
        return dp[l][r];
    
    int ans = 1e9+5;
    for(int i = l + 1; i < r; i++){
        ans = min(ans, cuts[r] - cuts[l] + solve(l, i, cuts) + solve(i, r, cuts));
        }
    return dp[l][r] = ans;
}

int minCost(int n, vector<int>& cuts) {
    memset(dp, -1, sizeof dp);
    cuts.insert(cuts.begin(), 0), cuts.push_back(n);
    sort(cuts.begin(), cuts.end());
    return solve(0, cuts.size() - 1, cuts);
}