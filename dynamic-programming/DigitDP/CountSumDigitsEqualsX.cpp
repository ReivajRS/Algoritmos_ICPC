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

//DP de digitos
//El problema consiste en encontrar cuantos numeros en un rango de l-r, existen que la suma de sus digitos es igual a sum

//pos posicion en la que se va del digito
//sum suma de digitos objetivo
//tight condicion de si se puede poner el numero que se quiera o hay que verificar que el numero no sea mayor al del limite r
//     pos  sum  tight
int dp[100][200][2];

int solve(string &num, int pos, int sum, bool tight){
    if(sum<0)   return 0;
    if(pos==0){
        if(sum==0)  return 1;
        else        return 0;
    }
    if(dp[pos][sum][tight]!=-1)     return dp[pos][sum][tight];
    
    int ans=0;
    //upper bound
    int ub=tight ? (num[num.length()-pos]-'0') : 9;
    for(int dig=0;dig<=ub;dig++){
        ans+=solve(num,pos-1,sum-dig,(tight&(dig==ub)));
    }
    return dp[pos][sum][tight]=ans;
}

int main(){_
    memset(dp,-1,sizeof dp);
    //Rango en el que se buscan los numeros
    string l,r;
    cin>>l>>r;
    // cin>>r;
    ll ln=stoi(l);
    ln--;
    l=to_string(ln);
    //Suma de digitos objetivo
    int sum;
    cin>>sum;
    cout<<solve(r,r.length(),sum,1)-solve(l,l.length(),sum,1)<<ENDL;
    return 0;
}