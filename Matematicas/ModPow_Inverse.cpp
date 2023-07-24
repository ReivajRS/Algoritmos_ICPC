// Retorna a % m, asegurando siempre una respuesta positiva
ll mod(ll a, ll m) { return (a % m + m) % m; }

ll modPow(ll b, ll p, ll m){                // O(log n)
    b %= m;                                 // Primero se aplica modulo a la base
    ll ans = 1;                             // Caso base p = 0
    while(p){
        if(p & 1) ans = mod(ans * b, m);    // (ans * b) % m, si p es impar
        b = mod(b * b, m);                  // (b ^ 2) % m
        p >>= 1;                            // p /= 2
    }
    return ans;                             // Retorna el resultado
}

int extEuclid(int a, int b, int &x, int &y) {   // Pasa x e y por referencia
	int xx = y = 0;
	int yy = x = 1;
	while (b) {                                 // Repetir hasta que b == 0
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