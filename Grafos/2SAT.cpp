// Time complexity O(V + E), donde V es el numero de variables y E es el numero de clausulas
typedef vector<int> vi;

struct TwoSat{
    int n;                      // Número de variables
    vector<vi> adj, adj_t;      // Listas de adyacencia normal y traspuesta(aristas invertidas)
    vector<bool> used;          // Nodos visitados por el dfs para encontrar los SCCs
    vi order, comp;             // Vectores para el orden de visita de los nodos y el componente de cada uno
    vector<bool> assignment;    // Vector para los valores asiganados a cada variable

    TwoSat(int N) : n(2*N), adj(2*N, vi()), adj_t(2*N, vi()) {}

    void dfs1(int v) {          // Primer dfs del algoritmo de Kosaraju
        used[v] = true;
        for (int u : adj[v]) {
            if (!used[u])
                dfs1(u);
        }
        order.push_back(v);
    }

    void dfs2(int v, int cl) {  // Segundo dfs del algoritmo de Kosaraju
        comp[v] = cl;
        for (int u : adj_t[v]) {
            if (comp[u] == -1)
                dfs2(u, cl);
        }
    }

    bool solve_2SAT() {         // Método para resolver el 2SAT
        order.clear();
        used.assign(n, false);
        for (int i = 0; i < n; ++i) {
            if (!used[i])
                dfs1(i);
        }
        comp.assign(n, -1);
        for (int i = 0, j = 0; i < n; ++i) {
            int v = order[n - i - 1];
            if (comp[v] == -1)
                dfs2(v, j++);
        }
        assignment.assign(n / 2, false);                // Inicialmente se asignan todas las variables en false
        for (int i = 0; i < n; i += 2) {
            if (comp[i] == comp[i + 1])                 // Si el componente de una variable y su negacion es el mismo, no hay solucion
                return false;
            assignment[i / 2] = comp[i] > comp[i + 1];  // Dependiendo la condicion, se asigna true o false
        }
        return true;                                    // Si existe solucion del 2SAT, se retorna true
    }

    void add_disjunction(int a, int b) { // OR
        // Las variables negadas son representadas por inversiones de bits (~x)
        // Nota: La expresion (a ∨ b), es equivalente a la expresion (¬a -> b) ∧ (¬b -> a)
        // si una de las variables es false, la otra debe ser true
        a = max(2*a, -1-2*a), b = max(2*b, -1-2*b)
        int neg_a = a ^ 1, neg_b = b ^ 1;
        adj[neg_a].push_back(b), adj[neg_b].push_back(a);
        adj_t[b].push_back(neg_a), adj_t[a].push_back(neg_b);
    }

    void setValue(int x) { add_disjunction(x, x); }
    void XOR(int x, int y) { add_disjunction(x, y); add_disjunction(~x, ~y); }
    void XNOR(int x, int y) { add_disjunction(~x, y); add_disjunction(x, ~y); }
};