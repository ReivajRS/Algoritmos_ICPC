// Time complexity Hashing O(n), hashInterval O(1)
typedef long long ll;

// Operaciones con modulo
inline int add(int a, int b, int mod) { a += b; return a >= mod ? a - mod : a; }
inline int sub(int a, int b, int mod) { a -= b; return a < 0 ? a + mod : a; }
inline int mul(int a, int b, int mod) { return ((ll)a*b) % mod; }

const int MOD[] = {(int)1e9+7, (int)1e9+9};	// Modulos

struct H{
    int x, y;
    H(int _x = 0) : x(_x), y(_x) {}
    H(int _x, int _y) : x(_x), y(_y) {}
    inline H operator+(const H& o){ return {add(x, o.x, MOD[0]), add(y, o.y, MOD[1])}; }
    inline H operator-(const H& o){ return {sub(x, o.x, MOD[0]), sub(y, o.y, MOD[1])}; }
    inline H operator*(const H& o){ return {mul(x, o.x, MOD[0]), mul(y, o.y, MOD[1])}; }
    inline bool operator==(const H& o) { return x == o.x && y == o.y; }
};

const int MAXN = 2e5+5;     // Valor maximo de la longitud de un string
const H P = {257, 577};     // Bases primas
vector<H> pw;               // Vector con las potencias de las bases

void computePowers(){ pw.resize(MAXN + 1); pw[0] = {1, 1}; for(int i = 0; i < MAXN; i++) pw[i + 1] = pw[i] * P; }

struct Hash{
    vector<H> ha;
    Hash(string& s){    // O(n)
        if(pw.empty())  computePowers();
        int l = (int) s.size(); ha.resize(l + 1);
        for(int i = 0; i < l; i++) ha[i + 1] = ha[i] * P + s[i];
    }
    H hashInterval(int l, int r){ return ha[r] - ha[l] * pw[r - l]; }    // O(1), regresa el hash del intervalo [l, r)
};

H hashString(string& s){ H ret; for(char c : s) ret = ret * P + c; return ret; } // O(n)

// Para "concatenar" hashes, de tal manera que se pueda obtener el hash de la concatenacion de 2 substrings,
// se puede hacer de la siguiente manera: hashIzq * pw[len] + hashDer, en donde len = longitud de hashDer
H combineHash(H hI, H hD, int len){ return hI * pw[len] + hD; } // O(1)