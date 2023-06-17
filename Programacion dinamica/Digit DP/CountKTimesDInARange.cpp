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

//Dado un rango l...r, contar en cuantos de esos numeros aparece k veces un digito d

ll dp[20][20][2];
int k,d;

ll solve(string& num, int pos, int count, bool tight){
    if(dp[pos][count][tight]!=-1)   return dp[pos][count][tight];
    if(pos==0)  return count==k;
    int ub=tight ? (num[num.length()-pos]-'0') : 9;
    ll ans=0;
    for(int dig=0;dig<=ub;dig++){
        ans+=solve(num,pos-1,count+(dig==d),(tight&(dig==ub)));
    }
    return dp[pos][count][tight]=ans;
}

int main(){_
    ll ln,rn;
    cin>>ln>>rn;
    cin>>k>>d;
    ln--;
    string l=to_string(ln),r=to_string(rn);
    memset(dp,-1,sizeof dp);
    ll lans=solve(l,l.length(),0,1);
    memset(dp,-1,sizeof dp);
    ll rans=solve(r,r.length(),0,1);
    cout<<rans-lans<<ENDL;
    return 0;
}