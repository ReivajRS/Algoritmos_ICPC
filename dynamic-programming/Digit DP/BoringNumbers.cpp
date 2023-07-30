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

//Problema
//Dado un intervalor de l a r, donde pueden ser hasta 10^18
//encontrar cuantos numeros "aburridos existen"
//Explicacion: Un numero "aburrido" es aquel en el que sus posiciones
//pares contienen numeros pares y las posiciones impares numeros impares

//Posiciones de la matriz dp
//1.- Posicion del digito en el numero
//2.- El numero es par o impar
//3.- Existen ceros a la izquierda
//4.- Condicion para ver si se tiene que cuidar el no superar el numero
ll dp[20][2][2][2];

vi evenNums={0,2,4,6,8}, oddNums={1,3,5,7,9};

ll solve(string& num, int pos, bool even, bool leading, bool tight){
    if(pos==0)
        return 1;
    if(dp[pos][even][leading][tight]!=-1)   return dp[pos][even][leading][tight];

    int ub= tight ? (num[num.length()-pos]-'0') : 9;
    ll ans=0;

    if(even){
        for(int dig:evenNums)
            if(dig<=ub)
                ans+=solve(num,pos-1,0,0,(tight & (dig==ub)));
    }else{
        if(leading)
            ans+=solve(num,pos-1,0,1,0);
        for(int dig:oddNums)
            if(dig<=ub)
                ans+=solve(num,pos-1,1,0,(tight & (dig==ub)));
    }
    
    return dp[pos][even][leading][tight]=ans;
}

int main(){_
    ll ln,rn;
    string l,r;
    cin>>ln>>rn;
    ln--;
    l=to_string(ln);
    r=to_string(rn);
    memset(dp,-1,sizeof dp);
    ll rans=solve(r,r.length(),0,1,1);
    memset(dp,-1,sizeof dp);
    ll lans=solve(l,l.length(),0,1,1);
    cout<<rans-lans<<ENDL;
    return 0;
}