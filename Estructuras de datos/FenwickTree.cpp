#define LSOne(S) ((S) & -(S))                    // La operacion clave (Bit menos significativo)
typedef long long ll;
typedef vector<ll> vll;
typedef vector<int> vi;

class FenwickTree {                              // El indice 0 no se usa
private:
  vll ft;                                        // Internamente el FT es un vector
public:
  FenwickTree(int m) { ft.assign(m+1, 0); }      // Crea un FT vacio

  void build(const vll &f) {
    int m = (int)f.size()-1;                     // Nota: f[0] siempre es 0
    ft.assign(m+1, 0);
    for (int i = 1; i <= m; ++i) {               // O(m)
      ft[i] += f[i];                             // Añade este valor
      if (i+LSOne(i) <= m)                       // i tiene padre
        ft[i+LSOne(i)] += ft[i];                 // Se añade al padre
    }
  }

  FenwickTree(const vll &f) { build(f); }        // Crea un FT basado en f

  FenwickTree(int m, const vi &s) {              // Crea un FT basado en s
    vll f(m+1, 0);
    for (int i = 0; i < (int)s.size(); ++i)      // Se hace la conversión primero
      ++f[s[i]];                                 // En O(n)
    build(f);                                    // En O(m)
  }

  ll rsq(int j) {                                // returns RSQ(1, j)
    ll sum = 0;
    for (; j; j -= LSOne(j))
      sum += ft[j];
    return sum;
  }

  ll rsq(int i, int j) { return rsq(j) - rsq(i-1); } // inc/exclusion

  // Actualiza el valor del i-esimo elemento por v (v+ = inc / v- = dec)
  void update(int i, ll v) {
    for (; i < (int)ft.size(); i += LSOne(i))
      ft[i] += v;
  }

  int select(ll k) {                             // O(log m)
    int p = 1;
    while (p*2 < (int)ft.size()) p *= 2;
    int i = 0;
    while (p) {
      if (k > ft[i+p]) {
        k -= ft[i+p];
        i += p;
      }
      p /= 2;
    }
    return i+1;
  }
};

class RUPQ {                                     // Variante RUPQ
private:
  FenwickTree ft;                                // Internamente usa un FT PURQ
public:
  RUPQ(int m) : ft(FenwickTree(m)) {}
  void range_update(int ui, int uj, ll v) {
    ft.update(ui, v);                            // [ui, ui+1, .., m] +v
    ft.update(uj+1, -v);                         // [uj+1, uj+2, .., m] -v
  }                                              // [ui, ui+1, .., uj] +v
  ll point_query(int i) { return ft.rsq(i); }    // rsq(i) es suficiente
};

class RURQ  {                                    // Variante RURQ
private:                                         // Necesita dos FTs de ayuda
  RUPQ rupq;                                     // Un RUPQ y
  FenwickTree purq;                              // un PURQ
public:
  RURQ(int m) : rupq(RUPQ(m)), purq(FenwickTree(m)) {} // Inicializacion
  void range_update(int ui, int uj, ll v) {
    rupq.range_update(ui, uj, v);                // [ui, ui+1, .., uj] +v
    purq.update(ui, v*(ui-1));                   // -(ui-1)*v antes de ui
    purq.update(uj+1, -v*uj);                    // +(uj-ui+1)*v despues de uj
  }
  ll rsq(int j) {
    return rupq.point_query(j)*j -               // Calculo optimista
           purq.rsq(j);                          // factor de cancelacion
  }
  ll rsq(int i, int j) { return rsq(j) - rsq(i-1); } // standard
};

int main() {
  vll f = {0,0,1,0,1,2,3,2,1,1,0};               // index 0 is always 0
  FenwickTree ft(f);
  printf("%lld\n", ft.rsq(1, 6)); // 7 => ft[6]+ft[4] = 5+2 = 7
  printf("%d\n", ft.select(7)); // index 6, rsq(1, 6) == 7, which is >= 7
  ft.update(5, 1); // update demo
  printf("%lld\n", ft.rsq(1, 10)); // now 12
  printf("=====\n");
  RUPQ rupq(10);
  RURQ rurq(10);
  rupq.range_update(2, 9, 7); // indices in [2, 3, .., 9] updated by +7
  rurq.range_update(2, 9, 7); // same as rupq above
  rupq.range_update(6, 7, 3); // indices 6&7 are further updated by +3 (10)
  rurq.range_update(6, 7, 3); // same as rupq above
  // idx = 0 (unused) | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |10
  // val = -          | 0 | 7 | 7 | 7 | 7 |10 |10 | 7 | 7 | 0
  for (int i = 1; i <= 10; i++)
    printf("%d -> %lld\n", i, rupq.point_query(i));
  printf("RSQ(1, 10) = %lld\n", rurq.rsq(1, 10)); // 62
  printf("RSQ(6, 7) = %lld\n", rurq.rsq(6, 7)); // 20
  return 0;
}