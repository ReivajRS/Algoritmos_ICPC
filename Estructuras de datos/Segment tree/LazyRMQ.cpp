// Implementacion de segment tree lazy para obtener una RMQ
typedef vector<int> vi;

class LazyRMQ {
  private:
    int n;
    vi A, st, lazy;

    int l(int p) { return p << 1; }       // ir al hijo izquierdo
    int r(int p) { return (p << 1) + 1; } // ir al hijo derecho

    int conquer(int a, int b) {
        if (a == -1)
            return b;
        if (b == -1)
            return a;
        return min(a, b); // RMQ - Cambiar esta linea para modificar la operacion del st
    }

    void build(int p, int L, int R) { // O(n)
        if (L == R)
            st[p] = A[L];
        else {
            int m = (L + R) / 2;
            build(l(p), L, m);
            build(r(p), m + 1, R);
            st[p] = conquer(st[l(p)], st[r(p)]);
        }
    }

    void propagate(int p, int L, int R) {
        if (lazy[p] != -1) {
            st[p] = lazy[p];
            if (L != R)                            // chechar que no es una hoja
                lazy[l(p)] = lazy[r(p)] = lazy[p]; // propagar hacia abajo
            else
                A[L] = lazy[p];
            lazy[p] = -1;
        }
    }

    int query(int p, int L, int R, int i, int j) { // O(log n)
        propagate(p, L, R);
        if (i > j)
            return -1;
        if ((L >= i) && (R <= j))
            return st[p];
        int m = (L + R) / 2;
        return conquer(query(l(p), L, m, i, min(m, j)),
                       query(r(p), m + 1, R, max(i, m + 1), j));
    }

    void update(int p, int L, int R, int i, int j, int val) { // O(log n)
        propagate(p, L, R);
        if (i > j)
            return;
        if ((L >= i) && (R <= j)) {
            lazy[p] = val;
            propagate(p, L, R);
        } else {
            int m = (L + R) / 2;
            update(l(p), L, m, i, min(m, j), val);
            update(r(p), m + 1, R, max(i, m + 1), j, val);
            int lsubtree = (lazy[l(p)] != -1) ? lazy[l(p)] : st[l(p)];
            int rsubtree = (lazy[r(p)] != -1) ? lazy[r(p)] : st[r(p)];
            st[p] = (lsubtree <= rsubtree) ? st[l(p)] : st[r(p)];
        }
    }

  public:
    LazyRMQ(int sz) : n(sz), st(4 * n), lazy(4 * n, -1) {} // Constructor de st sin valores

    LazyRMQ(const vi &initialA) : LazyRMQ((int)initialA.size()) { // Constructor de st con arreglo inicial
        A = initialA;
        build(1, 0, n - 1);
    }

    void update(int i, int j, int val) { update(1, 0, n - 1, i, j, val); }

    int query(int i, int j) { return query(1, 0, n - 1, i, j); }
};

int main(){
    // Implementacion
    vi A = {18, 17, 13, 19, 15, 11, 20, 99};
    LazyRMQ st(A);

    st.query(1, 3); // RMQ(1,3);

    st.update(5, 5, 77); // actualiza A[5] a 77

    st.update(0, 3, 30); // actualiza A[0..3] a 30
    return 0;
}