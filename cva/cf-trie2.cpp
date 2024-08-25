#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct TrieNode {
    TrieNode* children[26];  // Array of pointers to child nodes
    int count;  // To count how many strings pass through this node

    TrieNode() {
        count = 0;
        for (int i = 0; i < 26; i++) {
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
            if (node->children[index] == nullptr) {
                node->children[index] = new TrieNode();
            }
            node = node->children[index];
            node->count++;
        }
    }

    int countPrefixes(const string& prefix) {
        TrieNode* node = root;
        for (char c : prefix) {
            int index = c - 'a';
            if (node->children[index] == nullptr) {
                return 0;  // No strings with this prefix
            }
            node = node->children[index];
        }
        return node->count;  // Return the count of strings with this prefix
    }
};

int main() {
    int N, M;
    cin >> N;

    Trie trie;

    // Insert all strings into the Trie
    for (int i = 0; i < N; i++) {
        string S;
        cin >> S;
        trie.insert(S);
    }

    cin >> M;

    // Query the number of strings that have each query string as a prefix
    for (int i = 0; i < M; i++) {
        string X;
        cin >> X;
        cout << trie.countPrefixes(X) << endl;
    }

    return 0;
}
