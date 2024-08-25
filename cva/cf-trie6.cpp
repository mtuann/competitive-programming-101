#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <unordered_map>

using namespace std;

struct TrieNode {
    TrieNode* children[26] = {nullptr};
    bool isEndOfWord = false;
    string word;
};

class Trie {
public:
    TrieNode* root;

    Trie() {
        root = new TrieNode();
    }

    void insert(const string& word) {
        TrieNode* node = root;
        for (char ch : word) {
            int index = ch - 'a';
            if (node->children[index] == nullptr) {
                node->children[index] = new TrieNode();
            }
            node = node->children[index];
        }
        node->isEndOfWord = true;
        node->word = word;
    }

    void search(TrieNode* node, string& result, vector<int>& letterCount, string& currentWord) {

        // cout << "currentWord = " << currentWord << " " << (node == nullptr) << " " << node->isEndOfWord << endl;
        if (node == nullptr) return;

        if (node->isEndOfWord) {
            if (currentWord.length() > result.length() || 
               (currentWord.length() == result.length() && currentWord < result)) {
                result = currentWord;
            }
        }

        for (int i = 0; i < 26; ++i) {
            if (node->children[i] && letterCount[i] > 0) {
                currentWord.push_back('a' + i);
                letterCount[i] -= 1;
                search(node->children[i], result, letterCount, currentWord);
                letterCount[i] += 1;
                currentWord.pop_back();
            }
        }
    }

    string findBestWord(vector<int>& letterCount) {
        string result = "";
        string currentWord = "";
        search(root, result, letterCount, currentWord);
        if (result.empty()) {
            result = "IMPOSSIBLE";
        }
        return result;
    }
};

int main() {
    int n;
    cin >> n;

    Trie trie;
    vector<string> dictionary(n);

    for (int i = 0; i < n; ++i) {
        cin >> dictionary[i];
        trie.insert(dictionary[i]);
    }

    int t;
    cin >> t;
    vector<string> results(t);

    for (int i = 0; i < t; ++i) {
        string letters;
        cin >> letters;

        vector<int> letterCount(26, 0);
        for (char ch : letters) {
            letterCount[ch - 'a']++;
        }

        results[i] = trie.findBestWord(letterCount);
    }

    for (const string& result : results) {
        cout << result << endl;
    }

    return 0;
}
// g++ -std=c++14 -o a cf-trie6.cpp && ./a < a.in