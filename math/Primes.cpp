// Implementacion de muchas funciones utiles respecto a primos
typedef long long ll;
typedef vector<ll> vll;

ll _sieve_size;
bitset<10000010> bs;
vll p;

void sieve(ll upperbound) { // Calcula la criba en O(N log(log N))
    _sieve_size = upperbound+1;
    bs.set();
    bs[0] = bs[1] = 0;
    for (ll i = 2; i < _sieve_size; ++i) if (bs[i]){
        // Tacha los multiplos de i a partir de i*i
        for (ll j = i*i; j < _sieve_size; j += i) bs[j] = 0;
        p.push_back(i);
    }
}

bool isPrime(ll N) {    // Regresa si N es primo. Solo se garantiza su funcionamiento para N <= (ultimo primo en vll p)^2
    if (N < _sieve_size) return bs[N];
    for (int i = 0; i < (int)p.size() && p[i]*p[i] <= N; ++i)
        if (N%p[i] == 0)
        return false;
    return true;
}

vll primeFactors(ll N) {    // Regresa un vector con los factores primos de N
    vll factors;
    for (int i = 0; i < (int)p.size() && p[i]*p[i] <= N; ++i)
        while (N%p[i] == 0) {
            N /= p[i];
            factors.push_back(p[i]);
    }
    if (N != 1) factors.push_back(N);
    return factors;
}

int numPF(ll N) {   // Regresa el numero de factores primos de N
    int ans = 0;
    for (int i = 0; i < (int)p.size() && p[i]*p[i] <= N; ++i)
        while (N%p[i] == 0) { N /= p[i]; ++ans; }
    return ans + (N != 1);
}

int numDiffPF(ll N) {   // Regresa el numero de factores primos diferentes de N
    int ans = 0;
    for (int i = 0; i < p.size() && p[i]*p[i] <= N; ++i) {
        if (N%p[i] == 0) ++ans;
        while (N%p[i] == 0) N /= p[i];
    }
    if (N != 1) ++ans;
    return ans;
}

ll sumPF(ll N) {    // Regresa la suma de los factores primos de N
    ll ans = 0;
    for (int i = 0; i < p.size() && p[i]*p[i] <= N; ++i)
        while (N%p[i] == 0) { N /= p[i]; ans += p[i]; }
    if (N != 1) ans += N;
    return ans;
}

int numDiv(ll N) {  // Regresa el numero de divisores de N
    int ans = 1;
    for (int i = 0; i < (int)p.size() && p[i]*p[i] <= N; ++i) {
        int power = 0;                              // Cuenta la potencia
        while (N%p[i] == 0) { N /= p[i]; ++power; }
        ans *= power+1;                             // Sigue la formula
    }
    return (N != 1) ? 2*ans : ans;                  // Ultimo factor = N^1
}

ll sumDiv(ll N) {   // Regresa la suma de los divisores de N
    ll ans = 1;
    for (int i = 0; i < (int)p.size() && p[i]*p[i] <= N; ++i) {
        ll multiplier = p[i], total = 1;
        while (N%p[i] == 0) {
            N /= p[i];
            total += multiplier;
            multiplier *= p[i];
        }                                           // Total para
        ans *= total;                               // este factor primo
    }
    if (N != 1) ans *= (N+1);                       // N^2-1/N-1 = N+1
    return ans;
}

ll EulerPhi(ll N) { // Regresa cuantos numeros menores a N son coprimos con N
    ll ans = N;
    for (int i = 0; i < (int)p.size() && p[i]*p[i] <= N; ++i) {
        if (N%p[i] == 0) ans -= ans/p[i];
        while (N%p[i] == 0) N /= p[i];
    }
    if (N != 1) ans -= ans/N;
    return ans;
}
