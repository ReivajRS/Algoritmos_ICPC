/*
    Algoritmo para encontrar la suma maxima de un rectangulo en una matriz 2D.
    Se utiliza el algoritmo de Kadane que permite encontrar la maxima suma de un sub arreglo.
    Time complexity: O(n^3)
*/
typedef long long ll;

ll kadane(vector<ll>& rowSum, int& start, int& end, int& n){
    ll maxSum = LLONG_MIN, maxTillNow = 0;
    int tempStart = 0;

    for(int i = 0; i < n; i++){
        maxTillNow += rowSum[i];
        if(maxTillNow > maxSum)
            maxSum = maxTillNow, start = tempStart, end = i;
        if(maxTillNow < 0)
            maxTillNow = 0, tempStart = i + 1;
    }
    
    return maxSum;
}

int main(){
    int n, m;
    cin>>n>>m;
    
    vector<vector<ll>> mat(n, vector<ll>(m));
    
    // Lectura de la matriz

    ll maxSum = LLONG_MIN;
    int top, bottom, left, right, start, end;

    for(int l = 0; l < m; l++){
        vector<ll> rowSum(n, 0);
        for(int r = l; r < m; r++){
            for(int i = 0; i < n; i++)
                rowSum[i] += mat[i][r];
            ll sum = kadane(rowSum, start, end, n);
            if(sum > maxSum)
                maxSum = sum, left = l, right = r, top = start, bottom = end;
        }
    }

    printf("Top - left (%d, %d)\nBottom - right (%d, %d)\n", top, left, bottom, right);
    printf("Max sum = %lld\n", maxSum);

    return 0;
}