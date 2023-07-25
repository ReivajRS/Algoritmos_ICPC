// Union-Find Disjoint Sets escrito en POO, usando las heuristicas de compresion de camino y union por rango
typedef vector<int> vi;

class UnionFind {                                		// Estilo POO
    private:
        vi p, rank, setSize;                           	// vi p es la parte clave
        int numSets;
	public:
        UnionFind(int N) {
            p.assign(N, 0); for (int i = 0; i < N; ++i) p[i] = i;
            rank.assign(N, 0);                           // Aceleracion opcional
            setSize.assign(N, 1);                        // Caracteristica opcional
            numSets = N;                                 // Caracteristica opcional
        }
        int findSet(int i) { return (p[i] == i) ? i : (p[i] = findSet(p[i])); }
        bool isSameSet(int i, int j) { return findSet(i) == findSet(j); }
        int numDisjointSets() { return numSets; }      			// Opcional
        int sizeOfSet(int i) { return setSize[findSet(i)]; } 	// Opcional
        void unionSet(int i, int j) {
            if (isSameSet(i, j)) return;                 // i y j estan en el mismo set
            int x = findSet(i), y = findSet(j);          // Encuentra los representantes de ambos
            if (rank[x] > rank[y]) swap(x, y);           // Para mantener x más pequeño que y
            p[x] = y;                                    // Set x bajo y
            if (rank[x] == rank[y]) ++rank[y];           // Acelaracion opcional
            setSize[y] += setSize[x];                    // Combina los tamaños de los sets en y
            --numSets;                                   // Una union reduce el numSets
        }
};