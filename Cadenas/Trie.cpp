// Implementacion del arbol de prefijos usando mapa
struct TrieNode {
    map<char, TrieNode *> children;
    bool isEndOfWord;
    int numPrefix;

    TrieNode() : isEndOfWord(false), numPrefix(0) {}
};

class Trie {
   private:
    TrieNode *root;

   public:
    Trie() : root(new TrieNode()) {}

    void insert(string word) {  // Inserta una palabra en el trie
        TrieNode *curr = root;
        for (char c : word) {
            if (curr->children.find(c) == curr->children.end())
                curr->children[c] = new TrieNode();
            curr = curr->children[c];
            curr->numPrefix++;
        }
        curr->isEndOfWord = true;
    }

    bool search(string word) {  // Busca si una palabra esta en el trie
        TrieNode *curr = root;
        for (char c : word) {
            if (curr->children.find(c) == curr->children.end())
                return false;
            curr = curr->children[c];
        }
        return curr->isEndOfWord;
    }

    bool startsWith(string prefix) {    // Busca si alguna palabra del trie inicia con un prefijo
        TrieNode *curr = root;
        for (char c : prefix) {
            if (curr->children.find(c) == curr->children.end())
                return false;
            curr = curr->children[c];
        }
        return true;
    }

    int countPrefix(string prefix) {    // Cuenta la cantidad de palabras que inician con un prefijo
        TrieNode *curr = root;
        for (char c : prefix) {
            if (curr->children.find(c) == curr->children.end())
                return 0;
            curr = curr->children[c];
        }
        return curr->numPrefix;
    }
};