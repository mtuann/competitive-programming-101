#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

class AhoCorasick {
private:
    struct TrieNode {
        TrieNode* children[26]; // Fixed size array for 26 letters a-z
        TrieNode* failureLink;
        vector<int> output; // Stores indices of patterns ending at this node

        TrieNode() : failureLink(nullptr) {
            memset(children, 0, sizeof(children)); // Initialize children to nullptr
        }
    };

    TrieNode* root;

public:
    AhoCorasick() {
        root = new TrieNode();
    }

    // Function to insert a pattern into the trie
    void insert(const string& pattern, int index) {
        TrieNode* current = root;
        for (char ch : pattern) {
            int idx = ch - 'a'; // Get the index (0-25) for the character
            if (!current->children[idx]) {
                current->children[idx] = new TrieNode();
            }
            current = current->children[idx];
        }
        current->output.push_back(index); // Store pattern index at the end of the pattern
    }

    // Function to build failure links using BFS
    void buildFailureLinks() {
        queue<TrieNode*> q;
        root->failureLink = root; // Failure link of the root points to itself

        // Initialize the queue with the children of the root
        for (int i = 0; i < 26; ++i) {
            if (root->children[i]) {
                root->children[i]->failureLink = root;
                q.push(root->children[i]);
            }
        }

        while (!q.empty()) {
            TrieNode* current = q.front();
            q.pop();

            // For each child of the current node
            for (int i = 0; i < 26; ++i) {
                TrieNode* node = current->children[i];
                if (node) {
                    // Follow failure links to find the right fallback node
                    TrieNode* fallback = current->failureLink;
                    while (fallback != root) {
                        if (fallback->children[i]) {
                            node->failureLink = fallback->children[i];
                            break;
                        }
                        fallback = fallback->failureLink;
                    }
                    if (fallback == root) {
                        node->failureLink = root; // No match found, fallback to root
                    }

                    // Merge output of the failure link into the current node's output
                    node->output.insert(node->output.end(),
                                        node->failureLink->output.begin(),
                                        node->failureLink->output.end());

                    q.push(node); // Push the child into the queue for further processing
                }
            }
        }
    }

    // Function to search for patterns in the text and find the first position of each
    vector<int> search(const string& text, int k) {
        vector<int> firstPositions(k, -1); // Initialize positions to -1 (not found)
        TrieNode* current = root;

        // Traverse the input text
        for (size_t i = 0; i < text.size(); ++i) {
            char ch = text[i];
            int idx = ch - 'a'; // Get the index for the character

            // Follow failure links until we find a match
            while (current != root) {
                if (current->children[idx]) {
                    current = current->children[idx];
                    break;
                }
                current = current->failureLink;
            }

            // If there is a match, move to the child node
            if (!current->children[idx]) {
                current = root; // No match, return to root
            } else {
                current = current->children[idx];
            }

            // For each pattern found at the current node, update its first position
            for (int index : current->output) {
                if (firstPositions[index] == -1) {
                    firstPositions[index] = i - patterns[index].size() + 2; // 1-indexed position
                }
            }
        }
        return firstPositions;
    }

    // Destructor to clean up the allocated memory
    ~AhoCorasick() {
        destroyTrie(root);
    }

private:
    void destroyTrie(TrieNode* node) {
        for (int i = 0; i < 26; ++i) {
            if (node->children[i]) {
                destroyTrie(node->children[i]);
            }
        }
        delete node; // Delete the node to prevent memory leaks
    }
};

int main() {
    string text;
    cin >> text; // Read the input string
    int k;
    cin >> k; // Read the number of patterns

    AhoCorasick ac;

    // Vector to hold patterns
    vector<string> patterns(k);

    // Insert all patterns into the Aho-Corasick structure
    for (int i = 0; i < k; ++i) {
        cin >> patterns[i]; // Read each pattern
        ac.insert(patterns[i], i); // Insert pattern into the trie
    }

    // Build failure links for the trie
    ac.buildFailureLinks();

    // Search for patterns in the text and get first positions
    vector<int> results = ac.search(text, k);

    // Output results
    for (int position : results) {
        cout << position << endl; // Print the first position for each pattern
    }

    return 0;
}
