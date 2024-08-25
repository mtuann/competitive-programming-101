#include <iostream>
using namespace std;

struct TrieNode {
    TrieNode* children[2];
    int count;  // Number of elements passing through this node

    TrieNode() : count(0) {
        children[0] = children[1] = nullptr;
    }
};

class BinaryTrie {
private:
    TrieNode* root;
    const int MAX_BITS = 30;  // Because 2^30 > 10^9

public:
    BinaryTrie() : root(new TrieNode()) {}

    void insert(int num) {
        TrieNode* node = root;
        for (int i = MAX_BITS; i >= 0; i--) {
            int bit = (num >> i) & 1;
            if (!node->children[bit]) {
                node->children[bit] = new TrieNode();
            }
            node = node->children[bit];
            node->count++;
        }
    }

    int kthSmallest(int k) {
        TrieNode* node = root;
        int result = 0;

        for (int i = MAX_BITS; i >= 0; i--) {
            int leftCount = node->children[0] ? node->children[0]->count : 0;

            if (k <= leftCount) {
                node = node->children[0];
            } else {
                result |= (1 << i);
                k -= leftCount;
                node = node->children[1];
            }
        }
        return result;
    }
};

int main() {
    int N;
    cin >> N;
    BinaryTrie trie;

    for (int i = 0; i < N; i++) {
        int type, value;
        cin >> type >> value;

        if (type == 1) {
            trie.insert(value);
        } else if (type == 2) {
            cout << trie.kthSmallest(value) << endl;
        }
    }

    return 0;
}
// g++ -std=c++14 -o a cf-trie4.cpp && ./a < a.in