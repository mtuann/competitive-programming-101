#include <iostream>
#include <vector>
#include <string>
#include <cstring>
using namespace std;

const int MOD = 1000000007;

struct TrieNode {
    TrieNode* children[26];
    bool isEndOfWord;

    TrieNode() {
        isEndOfWord = false;
        memset(children, 0, sizeof(children));
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
        for (int i = (int)key.size() - 1; i >= 0; i--) {
            char c = key[i];
            int index = c - 'a';
            if (node->children[index] == nullptr) {
                node->children[index] = new TrieNode();
            }
            node = node->children[index];
        }
        node->isEndOfWord = true;
    }

    TrieNode* getRoot() {
        return root;
    }
};
int max_length = 0;

int countWaysToSplit(const string& X, Trie& trie) {
    int n = X.size();
    vector<int> dp(n + 1, 0);
    dp[0] = 1;  // Base case: There's 1 way to split an empty string

    for (int i = 1; i <= n; i++) {
        TrieNode* node = trie.getRoot();
        for (int j = i; j > 0; j--) {
            if (i - j + 1 > max_length) break;
            int index = X[j - 1] - 'a';
            if (node->children[index] == nullptr) break;

            node = node->children[index];

            if (node->isEndOfWord) {
                dp[i] = (dp[i] + dp[j - 1]) % MOD;
            }
        }
    }

    return dp[n];
}

int main() {
    int n;
    cin >> n;
    Trie trie;

    // Insert all strings from the set into the Trie
    for (int i = 0; i < n; i++) {
        string Si;
        cin >> Si;
        max_length = max(max_length, (int)Si.size());
        trie.insert(Si);
    }

    string X;
    cin >> X;

    // Calculate the number of ways to split X
    int result = countWaysToSplit(X, trie);
    cout << result << endl;

    return 0;
}

// g++ -std=c++14 -o a cf-trie3.cpp && ./a < a.in