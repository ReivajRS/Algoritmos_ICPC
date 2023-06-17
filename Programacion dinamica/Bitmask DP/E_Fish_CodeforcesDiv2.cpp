#include <bits/stdc++.h>
//Pura gente del coach moy
using namespace std;
#define ENDL '\n'
#define all(s) begin(s), end(s)
#define rall(n) n.rbegin(), n.rend()
#define FOR(x, b) for(int x = 0; x <b; x++)
#define FORE(x, a, b) for(int x = a; x <= b; x++)
#define FORR(x, a, b) for(int x = a; x >= b; x--)
#define deb(x)      cerr << #x << " = " << x << '\n';
#define deb2(x, y)  cerr << #x << " = " << x << ", " << #y << " = " << y << '\n';
#define _ ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define printDouble(x) cout<<fixed<<setprecision(6)<<x
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
const ll MOD = 1e9+7, INF=1e18;

//Problema: E. Fish - CodeForces Beta Round 16 Div 2
//Descripcion: Hay n peces en un lago y se te pide imprimir la probabilidad de que cada uno de los peces sea el ultimo vivo en el lago
//Se te da la matriz de probabilidades donde a_ij es la probabilidad del que el pez i se coma al pez j. Tambien a_ji = 1-a_ij
//Las probabilidades van de 0 a 1. Al final hay que imprimir con 6 decimales de precision

int n;
double prob[19][19];
double dp[1<<19];

double pMove(int prevMask, int jFish){
    int k=__builtin_popcount(prevMask);
    ll den=(k*(k-1))/2;
    double moveProb=0;
    
    FOR(fish,n)
        if(prevMask&(1<<fish))
            moveProb+=prob[fish][jFish];

    return moveProb/den;
}

double solve(int mask){
    int alive=__builtin_popcount(mask);

    if(alive==n)        return 1;
    if(dp[mask]>-1)     return dp[mask];

    double ans=0;
    
    FOR(fish,n){
        if(!(mask&(1<<fish))){
            int prevMask=mask^(1<<fish);
            double prev_day=solve(prevMask);
            ans+=prev_day*pMove(prevMask,fish);
        }
    }

    return dp[mask]=ans;
}

int main(){_
    memset(dp,-1,sizeof dp);
    cin>>n;
    FOR(i,n)
        FOR(j,n)
            cin>>prob[i][j];
    FOR(i,n)
        printDouble(solve(1<<i))<<' ';
    return 0;
}