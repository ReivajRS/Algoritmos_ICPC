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

//Problema: Little Elephant and T-Shirts  --  CodeChef
//Descripcion: Hay n personas que tienen ciertas playeras las cuales cuentan con un cierto ID desde 1 a 100
//En la entrada se dan cuantas personas hay y las playeras que tiene cada una de estas personas
//Se pide encontrar el numero de maneras en las que se pueden distribuir las personas y las playeras, de tal manera que, no haya 2 personas
//vistiendo la misma playera en ese conjunto. Al final imprimir modulo 1e9+7

//n, matriz para saber si una persona tiene una playera y matriz dp
int n;
bool tshirts[11][101];
ll dp[101][1<<11];

//Funcion para resolver el problema
ll solve(int shirt, int mask){
    //Si ya se le asigno a cada persona una playera, se retorna 1
    if(mask==((1<<n)-1))        return 1;

    //Si ya se recorrieron todas las playeras, se retorna 0
    if(shirt==100)              return 0;

    //Si ya se calculo anteriormente, se retorna lo almacenado en la dp
    if(dp[shirt][mask]!=-1)     return dp[shirt][mask];

    ll ans=0;

    //Para cada persona
    FOR(p,n){
        //Se verifica si esa persona aun no tiene una playera y si esta persona cuenta con la playera del parametro de la funcion
        if(!(mask&(1<<p))&&tshirts[p][shirt]){
            //Si cuenta con ella, se continua con la siguiente playera y se le asigna playera a la persona p
            ans=(ans+solve(shirt+1,mask|(1<<p)))%MOD;
        }
    }
    //Tambien se calcula para en caso de no asignar esta playera a la persona y asignarle posteriormente otra de con las que cuenta
    ans=(ans+solve(shirt+1,mask))%MOD;

    return dp[shirt][mask]=ans;
}

int main(){_
    int t;
    cin>>t;
    while(t--){
        memset(dp,-1,sizeof dp);
        memset(tshirts,0,sizeof tshirts);
        cin>>n;
        string s;
        cin.ignore();
        FOR(i,n){
            getline(cin,s);
            stringstream in(s);
            int ts;
            while(in>>ts){
                tshirts[i][--ts]=1;
            }
        }
        cout<<solve(0,0)<<ENDL;
    }
    return 0;
}