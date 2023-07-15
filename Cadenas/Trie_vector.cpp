// Implementacion del arbol de prefijos usando vector de vertices
struct vertex {
    char alphabet;
    bool exist;
    vector<vertex*> child;
    int num;
    vertex(char a): alphabet(a), exist(false), num(0) { child.assign(26, NULL); }
};

class Trie {
	private:
		vertex* root;
	public:
	Trie() { root = new vertex('!'); }

	void insert(string word) {                          // Inserta una palabra en el trie
		vertex* cur = root;
		for (int i = 0; i < (int)word.size(); ++i){     // O(n)
            int alphaNum = word[i]-'a';
            if (cur->child[alphaNum] == NULL)           // Añade una nueva rama si es NULL
                cur->child[alphaNum] = new vertex(word[i]);
            cur = cur->child[alphaNum];
            cur->num++;
		}
		cur->exist = true;
	}

	bool search(string word) {                          // true si la palabra están en el trie
		vertex* cur = root;
		for (int i = 0; i < (int)word.size(); ++i){     // O(m)
            int alphaNum = word[i]-'a';
            if (cur->child[alphaNum] == NULL)           // No encontrada
                return false;
            cur = cur->child[alphaNum];
		}
		return cur->exist;  // Verificar la flag de existencia
	}

	bool startsWith(string prefix) {                    // true si coincide el prefijo
		vertex* cur = root;
		for (int i = 0; i < (int)prefix.size(); ++i) {
            int alphaNum = prefix[i]-'a';
            if (cur->child[alphaNum] == NULL)          	// No encontrada
                return false;
            cur = cur->child[alphaNum];
		}
		return true;        // Llegando aqui, return true
	}

	int count(string prefix) {                      // true si coincide el prefijo
		vertex* cur = root;
		for (int i = 0; i < (int)prefix.size(); ++i) {
            int alphaNum = prefix[i]-'a';
            if (cur->child[alphaNum] == NULL)       // No encontrada
                return 0;
            cur = cur->child[alphaNum];
		}
		return cur->num;                            // Llegando aqui, return num
	}
};

int main() {
	Trie T;
	set<string> S = {"CAR", "CAT", "RAT"};

	for (auto &str : S)
		T.insert(str);

	printf("'CAR' exist? %d\n", T.search("CAR"));  // 1 (true)
	printf("'DOG' exist? %d\n", T.search("DOG"));  // 0 (false)
	printf("Starts with 'CA' exist? %d\n", T.startsWith("CA")); // 1 (true)
	printf("Starts with 'Z' exist? %d\n", T.startsWith("Z")); // 0 (false)
	printf("Starts with 'AT' exist? %d\n", T.startsWith("AT")); // 0 (false) for this Trie, but in a Suffix Trie, we have a suffix "AT" (from "CAT" or "RAT") that starts with "AT"
	return 0;
}
