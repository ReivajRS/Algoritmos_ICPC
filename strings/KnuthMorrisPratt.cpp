// Time complexity O(n + m)
typedef vector<int> vi;

vi kmpPreprocess(string &P) {   // Preprocesamiento
    int m = P.size();
    vi b(m + 1);                // b = Back table
    int i = 0, j = -1; b[0] = -1;
    while (i < m) {                                     // Preprocesamiento de P
        while ((j >= 0) && (P[i] != P[j])) j = b[j];    // Diferente, reset j
        ++i; ++j;                                       // Igual, avanzan ambos
        b[i] = j;
    }
    return b;
}

// T = Cadena donde se busca, P = Patron a buscar
int kmpSearch(string &T, string &P) {                   // Busqueda del patron en la cadena
    vi b = kmpPreprocess(P);
    int freq = 0;
    int i = 0, j = 0;
    int n = T.size(), m = P.size();
    while (i < n) {                                     // Buscar a traves de T
        while ((j >= 0) && (T[i] != P[j])) j = b[j];    // Diferente, reset j
        ++i; ++j;                                       // Igual, avanzan ambos
        if (j == m) {                                   // Una coincidencia es encontrada
            ++freq;
            // printf("P se encuentra en el indice %d de T\n", i-j);
            j = b[j];                                   // Prepara j para la siguiente
        }
    }
    return freq;
}

int main() {
    string T="I DO NOT LIKE SEVENTY SEV BUT SEVENTY SEVENTY SEVEN";
    string P="SEVENTY SEVEN";

    printf("Knuth-Morris-Pratt, #match = %d\n", kmpSearch(T, P));
    
    return 0;
}
