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
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
const ll MOD = 1e9+7, INF=1e18;

//Problema: O-Matching  AtCoder
//Descripcion: Te dan una matriz con las compatibilidades de parejas, donde i son los hombres y j son las mujeres,
//por lo tanto, a_ij indica si son compatibles con un 1, o si no lo son con un 0
//El problema pide el numero de parejas distintas que se pueden formar. Se aplica modulo 1e9+7 al resultado

int n;
vi adj[21];
ll dp[21][(1<<21)-1];

ll solve(int idx, int mask){
    //Si se llega a n, significa que todas las parejas han sido asignadas
    if(idx==n)              return 1;
    // if(mask==((1<<n)-1))    return 1;
    if(dp[idx][mask]!=-1)   return dp[idx][mask];

    ll ans=0;

    for(int i:adj[idx]){
        if(((mask&(1<<i))==0)){
            ans=(ans+solve(idx+1,mask|(1<<i)))%MOD;
        }
    }

    return dp[idx][mask]=ans;
}

int main(){_
    memset(dp,-1,sizeof dp);
    cin>>n;
    int match;
    FOR(i,n){
        FOR(j,n){
            cin>>match;
            if(match)
                adj[i].push_back(j);
        }
    }
    cout<<solve(0,0)<<ENDL;
    return 0;
}