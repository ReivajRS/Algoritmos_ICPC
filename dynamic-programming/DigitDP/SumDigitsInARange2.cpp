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

//Dado un rango de l...r, contar la suma de los digitos de todos los numeros en ese rango

ll pows10[17];
void pow10(){
    pows10[0]=1;
    FORE(i,1,16){
        pows10[i]=pows10[i-1]*10LL;
    }
}

ll cntdp[16][2];

ll cnt (string& num, int pos, bool tight){
    if(tight==0)    return pows10[pos];
    if(pos==0)      return 1;
    if(cntdp[pos][tight]!=-1)   return cntdp[pos][tight];

    ll numbers=0;
    int ub=tight ? (num[num.length()-pos]-'0') : 9;
    for(int dig=0;dig<=ub;dig++)
        numbers+=cnt(num,pos-1,tight & (dig==ub));

    return cntdp[pos][tight]=numbers;
}

ll dp[16][2];

ll solve(string& num, int pos, bool tight){
    if(pos==0)  return 0;
    if(dp[pos][tight]!=-1)  return dp[pos][tight];

    int ub=tight ? (num[num.length()-pos]-'0') : 9;
    ll ans=0;
    for(int dig=0;dig<=ub;dig++){
        ans+=(dig * cnt(num,pos-1, tight & (dig==ub)));
        ans+=solve(num,pos-1, tight & (dig==ub));
    }

    return dp[pos][tight]=ans;
}

int main(){_
    pow10();
    int t;
    cin>>t;
    while(t--){
        ll ln,rn;
        cin>>ln>>rn;
        if(ln>0)
            ln--;
        string l=to_string(ln),r=to_string(rn);
        memset(dp,-1,sizeof dp);
        memset(cntdp,-1,sizeof cntdp);
        ll lans=solve(l,l.length(),1);
        memset(dp,-1,sizeof dp);
        memset(cntdp,-1,sizeof cntdp);
        ll rans=solve(r,r.length(),1);
        cout<<rans-lans<<ENDL;
    }
    return 0;
}