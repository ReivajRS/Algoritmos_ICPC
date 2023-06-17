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

//Problema: Encoding-CodeChef
//Descripcion: Encontrar la suma de las funciones f(x), donde x son los numeros en un rango de L...R. Donde R puede ser hasta 10^100000
//El resultado de la f(x) se calcula dividiendo un numero en partes donde los numeros contiguos sean los mismos y se agrega el valor del numero
//multiplicado por 10^pos, donde pos es la posicion más a la izquierda de los numeros contiguos. Se suman todos los valores de estos numeros contiguos.
//Se calcula f(x) para todos los numeros en el rango L...R, aplicando modulo 10^9+7

const int MAXN=100001;
ll pows10[MAXN];

void pow10(){
    pows10[0]=1;
    for(int i=1;i<=100000;i++){
        pows10[i]=(pows10[i-1]*10LL)%MOD;
    }
}

//Funcion para contar cuantos numeros de una cierta longitud existen, tienen que ser menores o iguales a cierto numero
ll cntdp[MAXN][2];

ll cnt(string& num, int pos, bool tight){
    if(!tight)  return pows10[pos];
    if(pos==0)  return 1;
    if(cntdp[pos][tight]!=-1)   return cntdp[pos][tight];

    int ub=tight ? (num[num.length()-pos]-'0') : 9;
    ll ans=0;

    for(int dig=0;dig<=ub;dig++){
        ans=(ans+cnt(num,pos-1,tight & (dig==ub)))%MOD;
    }

    return cntdp[pos][tight]=ans%MOD;
}

int dp[MAXN][10][2];

ll solve(string& num,int pos,int prevDigit,bool tight){
    if(pos==0)  return 0;
    if(dp[pos][prevDigit][tight]!=-1)   return dp[pos][prevDigit][tight];

    int ub=tight ? num[num.length()-pos]-'0' : 9;
    ll ans=0;

    for(int dig=0;dig<=ub;dig++){
        //Si el digito que se coloca en la posicion actual es diferente del de la posicion anterior, se multiplica por la potencia de 10
        //correspondiente a la posicion en la que se coloca y se multiplica por el total de numeros que tienen ese digito en esa posicion
        //y tienen una longitud de un digito menos, ya que el que se encuentra en esa posicion es el colocado
        //Se calcula el modulo de la misma manera para mantenerse dentro de los limites
        if(dig!=prevDigit){
            ll contribution=(dig*pows10[pos-1]*cnt(num, pos-1, tight & (dig==ub)))%MOD;
            ans=(ans+contribution)%MOD;
        }
        ans=(ans+solve(num, pos-1,dig, tight & (dig==ub)))%MOD;
    }

    return dp[pos][prevDigit][tight]=ans%MOD;
}

//Funcion de fuerza bruta para calcular f(x) para un numero especifico
ll bruteForce(string& num){
    int prevDigit=-1;
    ll ans=0;

    for(int i=0;i<num.length();i++){
        if(num[i]-'0'!=prevDigit)
            ans=(ans+(num[i]-'0')*pows10[num.length()-i-1])%MOD;
        prevDigit=num[i]-'0';
    }

    return ans%MOD;
}

int main(){_
    //Precalcular las potencias de 10 que se usaran
    pow10();
    int t;
    cin>>t;
    while(t--){
        string l,r;
        int nl,nr;
        cin>>nl>>l;
        cin>>nr>>r;
        memset(dp,-1,sizeof dp);
        memset(cntdp,-1,sizeof cntdp);
        ll lans=solve(l,l.length(),-1,1);
        memset(dp,-1,sizeof dp);
        memset(cntdp,-1,sizeof cntdp);
        ll rans=solve(r,r.length(),-1,1);
        cout<<(rans+(MOD-lans)+bruteForce(l))%MOD<<ENDL;
    }
    return 0;
}