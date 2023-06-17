// Implementacion de muchas funciones utiles respecto a primos
typedef long long ll;
typedef vector<ll> vll;

ll _sieve_size;
bitset<10000010> bs;                             	// 10^7 es el límite de tamaño
vll p;                                           	// Vector de primos

void sieve(ll upperbound) {                     	// Rango = [0..upperbound]
	_sieve_size = upperbound+1;                    	// Para incluir el upperbound
	bs.set();                                      	// Asigna 1 en todas las posiciones
	bs[0] = bs[1] = 0;                             	// Excepto indice 0 y 1
	for (ll i = 2; i < _sieve_size; ++i) if (bs[i]){
		// Tacha los multiplos de i a partir de i*i
		for (ll j = i*i; j < _sieve_size; j += i) bs[j] = 0;
		p.push_back(i);                              // Añade el primo i a la lista
  	}
}

bool isPrime(ll N) {                             	// Prueba de primalidad suficientemente buena
	if (N < _sieve_size) return bs[N];             	// O(1) para primos pequeños
	for (int i = 0; i < (int)p.size() && p[i]*p[i] <= N; ++i)
		if (N%p[i] == 0)
		return false;
	return true;                                   	// Lento si N es un primo grande
} // Nota: Solo se garantiza su funcionamiento para N <= (ultimo primo en vll p)^2 

vll primeFactors(ll N) {                         	// Pre-condicion, N >= 1
	vll factors;
	for (int i = 0; i < (int)p.size() && p[i]*p[i] <= N; ++i)
		while (N%p[i] == 0) {                     	// Se encontro un primo para N
			N /= p[i];                             	// Se remueve de N
			factors.push_back(p[i]);
		}
	if (N != 1) factors.push_back(N);              	// La N que queda es un primo
	return factors;
}

int numPF(ll N) {
	int ans = 0;
	for (int i = 0; i < (int)p.size() && p[i]*p[i] <= N; ++i)
		while (N%p[i] == 0) { N /= p[i]; ++ans; }
	return ans + (N != 1);
}

int numDiffPF(ll N) {
	int ans = 0;
	for (int i = 0; i < p.size() && p[i]*p[i] <= N; ++i) {
		if (N%p[i] == 0) ++ans;                 	// Cuenta este factor primo
		while (N%p[i] == 0) N /= p[i];            	// Solo una vez
	}
	if (N != 1) ++ans;
	return ans;
}

ll sumPF(ll N) {
	ll ans = 0;
	for (int i = 0; i < p.size() && p[i]*p[i] <= N; ++i)
		while (N%p[i] == 0) { N /= p[i]; ans += p[i]; }
	if (N != 1) ans += N;
	return ans;
}

int numDiv(ll N) {
	int ans = 1;                                 	// Inicia de ans = 1
	for (int i = 0; i < (int)p.size() && p[i]*p[i] <= N; ++i) {
		int power = 0;                             	// Cuenta la potencia
		while (N%p[i] == 0) { N /= p[i]; ++power; }
		ans *= power+1;                            	// Sigue la formula
	}
	return (N != 1) ? 2*ans : ans;                 	// Ultimo factor = N^1
}

ll sumDiv(ll N) {
	ll ans = 1;                                    	// Inicia de ans = 1
	for (int i = 0; i < (int)p.size() && p[i]*p[i] <= N; ++i) {
		ll multiplier = p[i], total = 1;
		while (N%p[i] == 0) {
			N /= p[i];
			total += multiplier;
			multiplier *= p[i];
		}                                          	// Total para
		ans *= total;                              	// este factor primo
	}
	if (N != 1) ans *= (N+1);                      // N^2-1/N-1 = N+1
	return ans;
}

ll EulerPhi(ll N) {
	ll ans = N;                                   	// Inicia de ans = N
	for (int i = 0; i < (int)p.size() && p[i]*p[i] <= N; ++i) {
		if (N%p[i] == 0) ans -= ans/p[i];         	// Cuenta los unicos
		while (N%p[i] == 0) N /= p[i];             	// Factor primo
	}
	if (N != 1) ans -= ans/N;                    	// Ultimo factor
	return ans;
}

int main() {
	// Sieve of Eratosthenes
	sieve(10000000);                              	// Hasta 10^7 (<1s)
	printf("%lld\n", p.back());						// primes.back() = 9999991
	for (int i = p.back()+1; ; ++i)
		if (isPrime(i)) {
			printf("The next prime beyond the last prime generated is %d\n", i);
			break;
		}
	printf("%d\n", isPrime((1LL<<31)-1));          // 8th Mersenne prime
	printf("%d\n", isPrime(136117223861LL));       // 104729*1299709
	printf("\n");
}
