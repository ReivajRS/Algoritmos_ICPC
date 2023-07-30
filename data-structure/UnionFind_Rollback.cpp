// Union-Find Disjoint-set con la operacion de deshacer una uniones previas y regresar a un tiempo "t"
// Si no es necesaria esta operacion, eliminar st, time() y rollback()
// Time complexity O(log n)
typedef vector<int> vi;
typedef pair<int, int> ii;

struct RollbackUF {
    vi e;
    vector<ii> st;
    RollbackUF(int n) : e(n, -1) {}
    int size(int x) { return -e[find(x)]; }
    int find(int x) { return e[x] < 0 ? x : find(e[x]); }
    int time() { return (int) st.size(); }
    void rollback(int t) {
        for (int i = time(); i-- > t;){
            e[st[i].first] = st[i].second;
        }
        st.resize(t);
    }
    bool join(int a, int b) {
        a = find(a), b = find(b);
        if (a == b) return false;
        if (e[a] > e[b]) swap(a, b);
        st.push_back({a, e[a]});
        st.push_back({b, e[b]});
        e[a] += e[b];
        e[b] = a;
        return true;
    }
};

int main(){
    // Ejemplo de uso
    RollbackUF UF(5);       // Creacion del DSU
    UF.join(0, 1);          // Union de los elementos 0 y 1
    cout<<UF.size(0)<<ENDL; // Ahora el tamanio del set del elemento 0 es 2
    UF.rollback(0);         // Regresar al tiempo 0
    cout<<UF.size(0)<<ENDL; // Ahora el tamanio del set del elemento 0 es 1 de nuevo, porque se deshizo el cambio
    return 0;
}