#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

struct TrieNode {
    unordered_map<char, TrieNode*> children;
    bool isEndOfWord;
    TrieNode() : isEndOfWord(false) {}
};

class Trie {
public:
    Trie() {
        root = new TrieNode();
    }

    void insert(const string &word) {
        TrieNode* node = root;
        for (char c : word) {
            if (node->children.find(c) == node->children.end()) {
                node->children[c] = new TrieNode();
            }
            node = node->children[c];
        }
        node->isEndOfWord = true;
    }

    int search(const string &query) {
        TrieNode* node = root;
        int operations = 0;
        for (char c : query) {
            operations++; // 1 operation for comparing the characters
            if (node->children.find(c) == node->children.end()) {
                return operations; // No common prefix found
            }
            node = node->children[c];
            operations++; // Add the length of the longest common prefix
        }
        return operations;
    }

private:
    TrieNode* root;
};

int main() {
    int N;
    cin >> N;
    Trie trie;

    for (int i = 0; i < N; ++i) {
        string word;
        cin >> word;
        trie.insert(word);
    }

    int Q;
    cin >> Q;
    while (Q--) {
        string query;
        cin >> query;
        int operations = trie.search(query);
        cout << operations << endl;
    }

    return 0;
}


// #include <iostream>
// #include <vector>
// #include <string>
// #include <algorithm>

// using namespace std;

// // Function to calculate the longest common prefix length between two strings
// int longest_common_prefix(const string &a, const string &b) {
//     int len = min(a.length(), b.length());
//     for (int i = 0; i < len; ++i) {
//         if (a[i] != b[i]) {
//             return i;
//         }
//     }
//     return len;
// }

// int main() {
//     int N;
//     cin >> N;
//     vector<string> dictionary(N);

//     for (int i = 0; i < N; ++i) {
//         cin >> dictionary[i];
//     }

//     int Q;
//     cin >> Q;
//     while (Q--) {
//         string query;
//         cin >> query;
//         int operations = 0;

//         for (const auto &word : dictionary) {
//             operations++; // 1 operation for comparing the words
//             int lcp = longest_common_prefix(word, query);
//             operations += lcp; // Add the length of the longest common prefix

//             if (word == query) {
//                 break; // Stop when the word is found
//             }
//         }

//         cout << operations << endl;
//     }

//     return 0;
// }


// #include <iostream>
// #include <vector>
// #include <string>
// using namespace std;

// struct TrieNode {
//     TrieNode* children[26];
//     int count;
//     bool isEndOfWord;

//     TrieNode() : count(0), isEndOfWord(false) {
//         for (int i = 0; i < 26; i++) {
//             children[i] = nullptr;
//         }
//     }
// };

// class Trie {
// private:
//     TrieNode* root;

// public:
//     Trie() : root(new TrieNode()) {}

//     void insert(const string& word) {
//         TrieNode* node = root;
//         for (char ch : word) {
//             int index = ch - 'a';
//             if (!node->children[index]) {
//                 node->children[index] = new TrieNode();
//             }
//             node = node->children[index];
//             node->count++;
//         }
//         node->isEndOfWord = true;
//     }

//     int searchOperations(const string& word) {
//         TrieNode* node = root;
//         int operations = 0;
//         for (char ch : word) {
//             int index = ch - 'a';
//             if (!node->children[index]) {
//                 operations += 1;
//                 break;
//             }
//             node = node->children[index];
//             operations += node->count;
//         }
//         return operations;
//     }
// };

// int main() {
//     int N, Q;
//     cin >> N;

//     Trie trie;
//     vector<string> dictionary(N);
//     for (int i = 0; i < N; i++) {
//         cin >> dictionary[i];
//         trie.insert(dictionary[i]);
//         int value = trie.searchOperations(dictionary[i]);
//         cout << value << endl;
//     }

//     cin >> Q;
//     vector<int> results(Q);
//     for (int i = 0; i < Q; i++) {
//         string query;
//         cin >> query;
//         results[i] = trie.searchOperations(query);
//     }

//     for (int res : results) {
//         cout << res << endl;
//     }

//     return 0;
// }
// // g++ -std=c++14 -o a cf-trie5.cpp && ./a < a.in
