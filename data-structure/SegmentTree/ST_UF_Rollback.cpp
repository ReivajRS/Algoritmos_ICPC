// Union find rollback y segment tree para poder responder queries del numero de componentes que hay en cada instante de tiempo
typedef vector<int> vi;

struct dsu_save {   // Struct de los datos de cada set
    int v, rnkv, u, rnku;
    dsu_save(int _v, int _rnkv, int _u, int _rnku) : v(_v), rnkv(_rnkv), u(_u), rnku(_rnku) {}
};

struct dsu_with_rollbacks { // Dsu con rollback
    vi p, rnk;              // Vectores de padres y rangos
    int comps;              // Numero de componentes
    stack<dsu_save> op;

    dsu_with_rollbacks(int n) {     // Constructor donde n es el numero inicial de sets
        p.resize(n), rnk.resize(n);
        for (int i = 0; i < n; i++) {
            p[i] = i;
            rnk[i] = 0;
        }
        comps = n;
    }

    int find_set(int v) { return (v == p[v]) ? v : find_set(p[v]); }    // Regresa si estan en el mismo set

    bool unite(int v, int u) {  // Une 2 sets
        v = find_set(v), u = find_set(u);
        if (v == u) return false;
        comps--;
        if (rnk[v] > rnk[u])    swap(v, u);
        op.push(dsu_save(v, rnk[v], u, rnk[u]));
        p[v] = u;
        if (rnk[u] == rnk[v])   rnk[u]++;
        return true;
    }

    void rollback() {   // Revierte la ultima union hecha
        if (op.empty()) return;
        dsu_save x = op.top(); op.pop();
        comps++;
        p[x.v] = x.v, rnk[x.v] = x.rnkv;
        p[x.u] = x.u, rnk[x.u] = x.rnku;
    }
};

struct query {      // Struct para las queries
    int v, u;       // v= primer elemento, u= segundo elemento
    bool united;    // Para saber si estan unidos
    query(int _v, int _u) : v(_v), u(_u) { }
};

// Time complexity build O(T(n)), delete (T(n) log n). T(n)= time
struct QueryTree {              // Struct de un segment tree para resolver las queries
    vector<vector<query>> t;    // Vector para almacenar las queries
    dsu_with_rollbacks dsu;     // DSU
    int T;                      // Tiempo

    QueryTree(int _T, int n) : T(_T) {  // Constructor donde _T es el rango de tiempo y n es el numero inicial de sets
        dsu = dsu_with_rollbacks(n);
        t.resize(4 * T + 4);
    }

    void add_to_tree(int v, int l, int r, int ul, int ur, query& q) {   // Metodo para agregar una query al tree
        if (ul > ur)
            return;
        if (l == ul && r == ur) {
            t[v].push_back(q);
            return;
        }
        int mid = (l + r) / 2;
        add_to_tree(2 * v, l, mid, ul, min(ur, mid), q);
        add_to_tree(2 * v + 1, mid + 1, r, max(ul, mid + 1), ur, q);
    }

    // Las queries se agregan de la manera UF.add_query(query(v, u), l, r)
    // Donde v y u son los elementos a unir, mientras que l y r representan el rango de tiempo en el que estan unidos
    void add_query(query q, int l, int r) {
        add_to_tree(1, 0, T - 1, l, r, q);
    }

    void dfs(int v, int l, int r, vi& ans) {    // DFS para recorrer las queries
        for (query& q : t[v])
            q.united = dsu.unite(q.v, q.u);
        if (l == r)
            ans[l] = dsu.comps;
        else {
            int mid = (l + r) / 2;
            dfs(2 * v, l, mid, ans);
            dfs(2 * v + 1, mid + 1, r, ans);
        }
        for (query q : t[v])
            if (q.united)
                dsu.rollback();
    }

    vi solve() {   // Retorna un vector con el numero de componentes en cada instante de tiempo
        vi ans(T);
        dfs(1, 0, T - 1, ans);
        return ans;
    }
};

int main(){
    // Ejemplo de uso
    QueryTree UF(5,5);                  // Se crea el segment tree para resolver las queries
    UF.add_query(query(0, 1), 2, 3);    // Se agrega una querie indicando que los elementos v=0 y u=1 estan unidos desde t=2 hasta t=3
    UF.add_query(query(2, 3), 1, 4);    // Se agrega una querie indicando que los elementos v=2 y u=3 estan unidos desde t=1 hasta t=4
    vi res = UF.solve();                // Se llama el metodo para resolver las queries
    for(auto u : res)
        cout<<u<<" ";  // Se imprime 5 4 3 3 4, representando el numero de disjoint sets en cada instante de tiempo
    return 0;
}