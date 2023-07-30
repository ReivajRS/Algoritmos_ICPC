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

ll dp[1000001][3];

ll solve(string& num, int pos, int res){
    if(pos==0)  return 0;
    if(dp[pos][res]!=-1)    return dp[pos][res];

    ll ans=0;
    char dig=num[num.length()-pos];
    if(isdigit(dig)){
        int newRes=(res+(dig-'0'))%3;
        ans+=(newRes==0)+solve(num,pos-1,newRes);
    }

    return dp[pos][res]=ans;
}

int main(){_
    string num;
    while(cin>>num){
        memset(dp,-1,sizeof dp);
        ll ans=0;
        FOR(i,num.length()){
            if(!isdigit(num[i]))    continue;
            ans+=solve(num,num.length()-i,0);
        }
        cout<<ans<<ENDL;
    }
    return 0;
}