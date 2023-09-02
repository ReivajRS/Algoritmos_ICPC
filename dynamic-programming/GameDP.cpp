/**
 * Descripcion:
 * Hay un set A = {a1, a2, ..., an} que consiste de n enteros positivos, Taro y Jiro jugaran el siguiente juego.
 * Inicialmente la pila tiene k piedras. Los 2 jugadores realizaran la siguiente
 * operacion alternandose, iniciando Taro:
 * - Elegir un elemento x en A, y remover exactamente x piedras de la pila.
 * Un jugador pierde si ya no puede hacer movimiento. Ambos juegan optimamente.
*/

constexpr int MAXN = 1e5 + 1;
vi moves;
int dp[MAXN];

int solve(int stones){
    if(stones == 0)         return 0;
    if(dp[stones] != -1)    return dp[stones];
    
    int ans = 0;

    for(auto &x : moves)
        if(stones >= x && !solve(stones - x)){
            ans = 1;
            break;
        }
    
    return dp[stones] = ans;
}

int main(){_
    int n, k;
    cin>>n>>k;

    moves.resize(n);
    
    for(int i = 0; i < n; i++)
        cin>>moves[i];

    memset(dp, -1, sizeof dp);

    cout<<(solve(k) ? "First" : "Second")<<'\n';

    return 0;
}