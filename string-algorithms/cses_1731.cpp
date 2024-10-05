#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

const int MOD = 1e9 + 7;

// Trie Node
struct TrieNode {
    unordered_map<char, TrieNode*> children;
    bool isEndOfWord = false;
};

// Trie Class
class Trie {
public:
    TrieNode* root;

    Trie() {
        root = new TrieNode();
    }

    // Insert a word into the Trie
    void insert(const string& word) {
        TrieNode* node = root;
        for (char c : word) {
            if (!node->children.count(c)) {
                node->children[c] = new TrieNode();
            }
            node = node->children[c];
        }
        node->isEndOfWord = true; // Mark the end of a word
    }
};

// Function to count the number of ways to form the string using the dictionary
int countWays(const string& s, const vector<string>& dictionary) {
    int n = s.length();
    vector<int> dp(n + 1, 0);
    dp[0] = 1; // Base case: one way to form the empty string

    // Create and populate the Trie
    Trie trie;
    for (const string& word : dictionary) {
        // insert reversed word into the Trie
        string reversedWord = word;
        reverse(reversedWord.begin(), reversedWord.end());
        trie.insert(reversedWord);
    }

    // Dynamic programming to fill dp array
    for (int i = 1; i <= n; ++i) {
        TrieNode* node = trie.root; // Start from the root of the Trie
        for (int j = i; j >= 1; --j) {
            char c = s[j - 1]; // Get the current character
            if (!node->children.count(c)) {
                break; // No further matching
            }
            node = node->children[c]; // Move down the Trie

            if (node->isEndOfWord) {
                dp[i] = (dp[i] + dp[j - 1]) % MOD; // Add ways to form the previous substring
            }
        }
    }

    return dp[n]; // The number of ways to form the entire string
}

int main() {
    string s;
    int k;
    cin >> s >> k;

    vector<string> dictionary(k);
    for (int i = 0; i < k; ++i) {
        cin >> dictionary[i];
    }

    // Output the number of ways to form the string
    cout << countWays(s, dictionary) << endl;

    return 0;
}
