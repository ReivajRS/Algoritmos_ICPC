// Time complexity O(n + m)
const int MAX_N = 200010;
string T,P;
int n, m;                                           // n = |T|, m = |P|
int b[MAX_N];                                       // b = back table

void kmpPreprocess() {                              // Se llama esto primero
    int i = 0, j = -1; b[0] = -1;                   // Valores iniciales
    while (i < m) {                                 // Preprocesamiento de P
        while ((j >= 0) && (P[i] != P[j])) j = b[j];// Diferente, reset j
        ++i; ++j;                                   // Igual, avanzan ambos
        b[i] = j;
    }
}

int kmpSearch() {                                   // Similar a lo de arriba
    int freq = 0;
    int i = 0, j = 0;                               // Valores iniciales
    while (i < n) {                                 // Buscar a traves de T
        while ((j >= 0) && (T[i] != P[j])) j = b[j];// Diferente, reset j
        ++i; ++j;                                   // Igual, avanzan ambos
        if (j == m) {                               // Una coincidencia es encontrada
        ++freq;
        // printf("P is found at index %d in T\n", i-j);
        j = b[j];                                   // Prepara j para la siguiente
        }
    }
    return freq;
}

int main() {
    T="I DO NOT LIKE SEVENTY SEV BUT SEVENTY SEVENTY SEVEN";
    P="SEVENTY SEVEN";
    n=T.length();
    m=P.length();

    // Si el caracter de fin de la linea tambien se lee, descomentar
    // T[n-1] = 0; n--; P[m-1] = 0; m--;

    cout<<T<<'\n';
    cout<<P<<'\n';
    cout<<'\n';

    printf("Knuth-Morris-Pratt, #match = ");
    kmpPreprocess();
    printf("%d\n", kmpSearch());
    
    return 0;
}