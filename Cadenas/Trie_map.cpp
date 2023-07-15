// Implementacion del arbol de prefijos usando mapa
struct TrieNode {
    map<char, TrieNode *> children;
    bool isEndOfWord;
    int numPrefix;

    TrieNode() {
        isEndOfWord = false;
        numPrefix = 0;
    }
};

class Trie {
   private:
    TrieNode *root;

   public:
    Trie() {
        root = new TrieNode();
    }

    void insert(string word) {
        TrieNode *curr = root;
        for (char c : word) {
            if (curr->children.find(c) == curr->children.end()) {
                curr->children[c] = new TrieNode();
            }
            curr = curr->children[c];
            curr->numPrefix++;
        }
        curr->isEndOfWord = true;
    }

    bool search(string word) {
        TrieNode *curr = root;
        for (char c : word) {
            if (curr->children.find(c) == curr->children.end()) {
                return false;
            }
            curr = curr->children[c];
        }
        return curr->isEndOfWord;
    }

    bool startsWith(string prefix) {
        TrieNode *curr = root;
        for (char c : prefix) {
            if (curr->children.find(c) == curr->children.end()) {
                return false;
            }
            curr = curr->children[c];
        }
        return true;
    }

    int countPrefix(string prefix) {
        TrieNode *curr = root;
        for (char c : prefix) {
            if (curr->children.find(c) == curr->children.end()) {
                return 0;
            }
            curr = curr->children[c];
        }
        return curr->numPrefix;
    }
};

int main(){_
    Trie T;
	int n,m;
    string s;
	cin>>n;
	FOR(i,n){
		cin>>s;
		T.insert(s);
	}
	cin>>m;
	FOR(i,m){
		cin>>s;
		cout<<T.countPrefix(s)<<endl;
	}
    return 0;
}

int main(){
    Trie T;
    T.insert("harshita");
    T.insert("harsh");
    T.insert("sharma");
    T.insert("harry");
    string p = "har";
    cout << T.countPrefix(p) << '\n';
    return 0;
}