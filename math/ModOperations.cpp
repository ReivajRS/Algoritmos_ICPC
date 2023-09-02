// Retorna a % m, asegurando siempre una respuesta positiva
ll mod(ll a, ll m) { return (a % m + m) % m; }

ll modPow(ll b, ll p, ll m){                // O(log n)
    b %= m;
    ll ans = 1;
    while(p){
        if(p & 1) ans = mod(ans * b, m);
        b = mod(b * b, m);
        p >>= 1;
    }
    return ans;
}

int extEuclid(int a, int b, int &x, int &y) {
    int xx = y = 0;
    int yy = x = 1;
    while (b) {
        int q = a/b;
        tie(a, b) = tuple(b, a%b);
        tie(x, xx) = tuple(xx, x-q*xx);
        tie(y, yy) = tuple(yy, y-q*yy);
    }
    return a;                                   // Retorna gcd(a, b)
}

int modInverse(int b, int m) {                  // Retorna b^(-1) (mod m)
    int x, y;
    int d = extEuclid(b, m, x, y);              // Para obtener b*x + m*y == d
    if (d != 1) return -1;                      // Para indicar fallo
    // b*x + m*y == 1, ahora se aplica (mod m) para obtener b*x == 1 (mod m)
    return mod(x, m);
}

// Solo cuando m es primo
int modInverse(int b, int m){ return modPow(b, m - 2, m) % m; }

// Calcula a*b mod m, para cualquier 0 <= a, b <= c <= 7.2 * 10^18
ull modmul(ull a, ull b, ull m) {
    ll ret = a * b - m * ull(1.L / m * a * b);
    return ret + m * (ret < 0) - m * (ret >= (ll)m);
}

// Precalculo de modulos inversos para toda x <= LIM. Se asume que LIM <= MOD y MOD es primo
constexpr LIM = 1e5 + 5;
ll inv[LIM + 1];
void precalc_inv() {
    inv[1] = 1;
    for(int i = 2; i < LIM; i++)
        inv[i] = MOD - (MOD / i) * inv[MOD % i] % MOD;
}
