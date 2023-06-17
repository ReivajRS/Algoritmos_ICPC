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

//Problema Counting numbers - CSES
//Descripcion: El problema consiste en encontrar cuantos numeros en un rango L...R existen que no tengan 2 digitos adyacentes repetidos

ll dp[20][10][2][2];

ll solve(string& num, int pos, int prevDigit, bool leadz, bool tight){
    if(pos==0)  return 1;
    if(dp[pos][prevDigit][leadz][tight]!=-1)    return dp[pos][prevDigit][leadz][tight];

    int ub=tight ? (num[num.length()-pos]-'0') : 9;
    ll ans=0;

    for(int dig=0;dig<=ub;dig++){
        if(dig==prevDigit && !leadz) continue;
        ans+=solve(num,pos-1,dig,leadz & (dig==0), tight & (dig==ub));
    }

    return dp[pos][prevDigit][leadz][tight]=ans;
}

int main(){_
    ll ln,rn;
    cin>>ln>>rn;
    string l=to_string(ln-1),r=to_string(rn);
    memset(dp,-1,sizeof dp);
    ll lans=solve(l,l.length(),-1,1,1);
    memset(dp,-1,sizeof dp);
    ll rans=solve(r,r.length(),-1,1,1);
    cout<<rans-lans<<ENDL;
    return 0;
}