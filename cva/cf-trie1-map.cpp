#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;

struct TrieNode {
    unordered_map<char, TrieNode*> children;
    bool isEndOfWord;

    TrieNode() {
        isEndOfWord = false;
    }
};

class Trie {
public:
    TrieNode* root;

    Trie() {
        root = new TrieNode();
    }

    void insert(const string& key) {
        TrieNode* node = root;
        for (char c : key) {
            if (node->children.find(c) == node->children.end()) {
                node->children[c] = new TrieNode();
            }
            node = node->children[c];
        }
        node->isEndOfWord = true;
    }

    bool search(const string& key) {
        TrieNode* node = root;
        for (char c : key) {
            if (node->children.find(c) == node->children.end()) {
                return false;
            }
            node = node->children[c];
        }
        return node != nullptr && node->isEndOfWord;
    }
};

int main() {
    int N, M;
    cin >> N;
    Trie trie;

    for (int i = 0; i < N; i++) {
        string S;
        cin >> S;
        trie.insert(S);
    }

    cin >> M;
    for (int i = 0; i < M; i++) {
        string X;
        cin >> X;
        if (trie.search(X)) {
            cout << "1" << endl;
        } else {
            cout << "0" << endl;
        }
    }

    return 0;
}
