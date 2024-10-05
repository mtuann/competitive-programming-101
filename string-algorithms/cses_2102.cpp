#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;

class AhoCorasick {
private:
    struct TrieNode {
        unordered_map<char, TrieNode*> children;
        TrieNode* failureLink;
        vector<int> output;

        TrieNode() : failureLink(nullptr) {}
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
            if (!current->children.count(ch)) {
                current->children[ch] = new TrieNode();
            }
            current = current->children[ch];
        }
        current->output.push_back(index);
    }

    // Function to build failure links using BFS
    void buildFailureLinks() {
        queue<TrieNode*> q;
        root->failureLink = root; // Failure link of the root points to itself

        // Initialize the queue with the children of the root
        for (const auto& pair : root->children) {
            pair.second->failureLink = root;
            q.push(pair.second);
        }

        while (!q.empty()) {
            TrieNode* current = q.front();
            q.pop();

            // For each child of the current node
            for (const auto& pair : current->children) {
                char ch = pair.first;
                TrieNode* child = pair.second;
                TrieNode* fallback = current->failureLink;

                // Follow failure links to find the right fallback node
                while (fallback != root && !fallback->children.count(ch)) {
                    fallback = fallback->failureLink;
                }
                if (fallback->children.count(ch)) {
                    child->failureLink = fallback->children[ch];
                } else {
                    child->failureLink = root; // No match found, fallback to root
                }

                // Merge output of the failure link into the current node's output
                child->output.insert(child->output.end(),
                                     child->failureLink->output.begin(),
                                     child->failureLink->output.end());

                q.push(child); // Push the child into the queue for further processing
            }
        }
    }

    // Function to search for patterns in the text
    vector<bool> search(const string& text, int k) {
        vector<bool> found(k, false);
        TrieNode* current = root;

        // Traverse the input text
        for (size_t i = 0; i < text.size(); ++i) {
            char ch = text[i];

            // Follow failure links until we find a match
            while (current != root && !current->children.count(ch)) {
                current = current->failureLink;
            }

            // If there is a match, move to the child node
            if (current->children.count(ch)) {
                current = current->children[ch];
            } else {
                current = root; // No match, return to root
            }

            // Check for patterns that end at the current position
            for (int index : current->output) {
                found[index] = true; // Mark pattern as found
            }
        }
        return found;
    }

    // Destructor to clean up the allocated memory
    ~AhoCorasick() {
        destroyTrie(root);
    }

private:
    void destroyTrie(TrieNode* node) {
        for (auto& pair : node->children) {
            destroyTrie(pair.second);
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

    // Insert all patterns into the Aho-Corasick structure
    vector<string> patterns(k);
    for (int i = 0; i < k; ++i) {
        cin >> patterns[i]; // Read each pattern
        ac.insert(patterns[i], i); // Insert pattern into the trie
    }

    // Build failure links for the trie
    ac.buildFailureLinks();

    // Search for patterns in the text
    vector<bool> results = ac.search(text, k);

    // Output results
    for (bool found : results) {
        cout << (found ? "YES" : "NO") << endl; // Print whether each pattern is found
    }

    return 0;
}
