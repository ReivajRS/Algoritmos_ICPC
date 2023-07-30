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
int n;
int dp[1001][1001];

bool solve(int pos, int res){
    if(pos==0)              return res==0;
    if(dp[pos][res]!=-1)    return dp[pos][res];

    bool ans=false;

    if(num[num.length()-pos]!='?'){
        int dig=num[num.length()-pos]-'0';
        ans|=solve(pos-1,(res*10+dig)%n);
    }else{
        for(int dig=0;dig<=9;dig++){
            if(pos==0&&dig==0)  continue;
            ans|=solve(pos-1,(res*10+dig)%n);
        }   
    }
    return dp[pos][res]=ans;
}

int main(){_
    memset(dp,-1,sizeof dp);
    cin>>num>>n;
    bool posible=solve(num.length(),0);
    if(!posible){
        cout<<'*'<<ENDL;
        return 0;
    }
    int mod=0;
    FOR(i,num.length()){
        if(num[i]!='?'){
            cout<<num[i];
            mod=(mod*10+(num[i]-'0'))%n;
            continue;
        }
        FORE(j,i==0,9){
            if(solve(num.length()-i-1,(mod*10+j)%n)){
                mod=(mod*10+j)%n;
                cout<<j;
                break;
            }
        }
    }
    cout<<ENDL;
    return 0;
}