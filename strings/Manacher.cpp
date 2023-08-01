// Time complexity O(n), donde n es la longitud del string
typedef vector<int> vi;

struct Manacher{
    vi p;                           // Vector para guardar cual es el palindromo mas grande con centro en esa posicion
    string w;                       // String original
    int lpL, lpR;                   // Posicion de inicio y fin del palindromo mas grande
    Manacher(string& str) : w(str) {
        string s;                   // String a la que se aplicara el Manacher
        for(char c : str)           // Se agregan caracteres "no validos" entre medio para unificar longitudes pares e impares
            s += string("#") + c;
        s += "#";
        int n = s.size(), l = 1, r = 1, longestP = -1; p.assign(n, 1);
        for(int i = 0; i < n; i++){
            p[i] = max(0, min(r - i, p[max(0, l + r - i)]));
            while(i - p[i] >= 0 && i + p[i] < n && s[i - p[i]] == s[i + p[i]])
                p[i]++;
            if(i + p[i] > r)
                l = i - p[i], r = i + p[i];
            if(p[i] > longestP)
                longestP = p[i], lpL = l + 1, lpR = r;
        }
    }
    int getLongestAt(int center, bool odd){             // Regresa la longitud del palindromo mas grande con ese centro
        return p[2 * center + 1 + !odd] - 1;
    }
    string getPalindromeAt(int center, bool odd){       // Regresa el palindromo mas grande con ese centro
        int len = getLongestAt(center, odd);
        return w.substr(center + !odd - len / 2, len);
    }
    string getLongestPalindrome(){                      // Regresa el palindromo mas grande en toda el string
        return w.substr(lpL / 2, (lpR - lpL) / 2);
    }
    bool checkPalindrome(int l, int r){                 // Verifica si un rango del string original es palindromo
        return (r - l + 1) <= getLongestAt((l + r) / 2, r % 2 == l % 2);
    }
};