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
 
string num;
int d;
 
ll dp[10001][100][2];
 
ll solve(int pos, int sum, bool tight){
    if(pos==0)  return sum==0;
    if(dp[pos][sum][tight]!=-1) return dp[pos][sum][tight];
 
    int ub=tight ? (num[num.length()-pos]-'0') : 9;
    ll ans=0;
 
    for(int dig=0;dig<=ub;dig++){
        ans=(ans+solve(pos-1, (sum+dig)%d, tight & (dig==ub)))%MOD;
    }
 
    return dp[pos][sum][tight]=ans;
}
 
int main(){_
    memset(dp,-1,sizeof dp);
    cin>>num>>d;
    ll ans=solve(num.length(),0,1);
    cout<<(ans==0 ? MOD-1 : ans-1)<<ENDL;
    return 0;
}