#include <iostream>
#include <string>
using namespace std;

const int ALPHABET_SIZE = 26;

struct TrieNode {
    TrieNode* children[ALPHABET_SIZE];
    bool isEndOfWord;

    TrieNode() {
        isEndOfWord = false;
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            children[i] = nullptr;
        }
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
            int index = c - 'a';
            if (!node->children[index]) {
                node->children[index] = new TrieNode();
            }
            node = node->children[index];
        }
        node->isEndOfWord = true;
    }

    bool search(const string& key) {
        TrieNode* node = root;
        for (char c : key) {
            int index = c - 'a';
            if (!node->children[index]) {
                return false;
            }
            node = node->children[index];
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
// g++ -std=c++14 -o a cf-trie1.cpp && ./a < a.in