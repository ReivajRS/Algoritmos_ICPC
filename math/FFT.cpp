/*
 * Descripcion: Este algoritmo permite multiplicar dos polinomios de longitud n
 * Tiempo: O(n log n)
 */

typedef long long ll;
typedef double ld;
typedef complex<ld> C;
typedef vector<ld> vd;
typedef vector<ll> vl;

const ld PI = acos(-1.0L);
const ld one = 1;

void fft(vector<C> &a) {
    int n = sz(a), L = 31 - __builtin_clz(n);
    static vector<complex<ld>> R(2, 1);
    static vector<C> rt(2, 1);  // (^ 10% faster if double)
    for (static int k = 2; k < n; k *= 2) {
        R.resize(n);
        rt.resize(n);
        auto x = polar(one, PI / k);
        for(int i = k; i < 2*k; i++)
            rt[i] = R[i] = i & 1 ? R[i / 2] * x : R[i / 2];
    }
    vi rev(n);
    for(int i = 0; i < n; i++)
        rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
    for(int i = 0; i < n; i++)
        if (i < rev[i]) swap(a[i], a[rev[i]]);
    for (int k = 1; k < n; k *= 2)
        for (int i = 0; i < n; i += 2 * k) for(int j = 0; j < k; j++) {
            // C z = rt[j+k] * a[i+j+k]; // (25% faster if hand-rolled)     /// include-line
            auto x = (ld *)&rt[j + k], y = (ld *)&a[i + j + k];             /// exclude-line
            C z(x[0] * y[0] - x[1] * y[1], x[0] * y[1] + x[1] * y[0]);      /// exclude-line
            a[i + j + k] = a[i + j] - z;
            a[i + j] += z;
        }
}

typedef vector<ll> vl;

vl conv(const vl &a, const vl &b) {
    if (a.empty() || b.empty()) return {};
    vl res(sz(a) + sz(b) - 1);
    int L = 32 - __builtin_clz(sz(res)), n = 1 << L;
    vector<C> in(n), out(n);
    copy(all(a), begin(in));
    for(int i = 0; i < sz(b); i++)
        in[i].imag(b[i]);
    fft(in);
    for (C &x : in) x *= x;
    for(int i = 0; i < n; i++)
        out[i] = in[-i & (n - 1)] - conj(in[i]);
    fft(out);
    for(int i = 0; i < sz(res); i++)
        res[i] = floor(imag(out[i]) / (4 * n) + 0.5);
    return res;
}

vl convMod(const vl &a, const vl &b, const int &M) {
    if (a.empty() || b.empty()) return {};
    vl res(sz(a) + sz(b) - 1);
    int B = 32 - __builtin_clz(sz(res)), n = 1 << B, cut = int(sqrt(M));
    vector<C> L(n), R(n), outs(n), outl(n);
    for(int i = 0; i < sz(a); i++)
        L[i] = C((int)a[i] / cut, (int)a[i] % cut);
    for(int i = 0; i < sz(b); i++)
        R[i] = C((int)b[i] / cut, (int)b[i] % cut);
    fft(L), fft(R);
    for(int i = 0; i < n; i++) {
        int j = -i & (n - 1);
        outl[j] = (L[i] + conj(L[j])) * R[i] / (2.0 * n);
        outs[j] = (L[i] - conj(L[j])) * R[i] / (2.0 * n) / 1i;
    }
    fft(outl), fft(outs);
    for(int i = 0; i < sz(res); i++) {
        ll av = ll(real(outl[i]) + .5), cv = ll(imag(outs[i]) + .5);
        ll bv = ll(imag(outl[i]) + .5) + ll(real(outs[i]) + .5);
        res[i] = ((av % M * cut + bv) % M * cut + cv) % M;
    }
    return res;
}