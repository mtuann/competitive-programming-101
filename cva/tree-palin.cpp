#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

const int MAXN = 500000; // Maximum number of vertices
vector<int> graph[MAXN + 1]; // Adjacency list for the tree
unordered_map<int, int> edges; // Edges between nodes (parent, child)
int result[MAXN + 1]; // Result array for storing the longest path for each vertex

void dfs(int u, int parent, int mask, int depth, unordered_map<int, int>& masks) {
    // Update the mask for the current character on the edge to the parent
    if (parent != -1) {
        char c = edges[(parent << 20) + u]; // Get the character from parent to u
        mask ^= (1 << (c - 'a'));
    }
    
    // Store the depth where each mask occurs for the first time
    if (masks.find(mask) != masks.end()) {
        result[u] = max(result[u], depth - masks[mask]);
    }

    // Check for masks that differ by exactly one bit (single character having odd count)
    for (int i = 0; i < 22; ++i) {
        int toggle_mask = mask ^ (1 << i);
        if (masks.find(toggle_mask) != masks.end()) {
            result[u] = max(result[u], depth - masks[toggle_mask]);
        }
    }

    // Store the current depth for this mask if it is the first time we encounter it
    int previous_mask_depth = masks.count(mask) ? masks[mask] : -1;
    if (previous_mask_depth == -1) {
        masks[mask] = depth;
    }

    // DFS through the children
    for (int v : graph[u]) {
        if (v != parent) {
            dfs(v, u, mask, depth + 1, masks);
        }
    }

    // Backtrack (restore the previous state of the mask)
    if (previous_mask_depth == -1) {
        masks.erase(mask);
    }
}

int main() {
    int N;
    cin >> N;

    for (int i = 2; i <= N; ++i) {
        int p;
        char c;
        cin >> p >> c;
        graph[p].push_back(i);
        graph[i].push_back(p);
        edges[(p << 20) + i] = c; // Store the character on the edge (parent to child)
        edges[(i << 20) + p] = c; // Store the reverse edge (child to parent)
    }

    // Initial mask and masks dictionary to store the first occurrence of each mask
    int initial_mask = 0;
    unordered_map<int, int> masks;
    masks[0] = 0; // Mask 0 at depth 0

    // Run DFS starting from node 1 (the root)
    dfs(1, -1, initial_mask, 0, masks);

    // Output the result for each vertex
    for (int i = 1; i <= N; ++i) {
        cout << result[i] << " ";
    }
    cout << endl;

    return 0;
}
// g++ -std=c++11 -O2 -Wall tree-palin.cpp -o a && ./a < a.in