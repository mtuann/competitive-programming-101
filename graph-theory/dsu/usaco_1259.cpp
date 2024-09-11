// https://usaco.org/index.php?page=viewproblem2&cpid=1259
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <cstring>
using namespace std;

const int MAXN = 1e5 + 5;  // Max number of cows
int parent[MAXN], sz[MAXN], friends_count[MAXN], min_friends[MAXN];
vector<int> adj[MAXN];

// Find function with path compression
int find(int u) {
    if (u == parent[u]) return u;
    return parent[u] = find(parent[u]);
}

// Union by sz and update the minimum number of friends in each component
void unionSets(int u, int v) {
    u = find(u);
    v = find(v);
    if (u != v) {
        if (sz[u] < sz[v]) swap(u, v);
        parent[v] = u;
        sz[u] += sz[v];
        // Update minimum friends in the new component
        min_friends[u] = min(min_friends[u], min_friends[v]);
    }
}

int main() {
    // Input
    int N, M;
    cin >> N >> M;

    // Initialize DSU structures
    for (int i = 1; i <= N; i++) {
        parent[i] = i;  // Each cow starts as its own parent
        sz[i] = 1;    // Initial sz of each component is 1
        friends_count[i] = 0; // Each cow initially has 0 friends
        min_friends[i] = INT_MAX; // We initialize with a large number
    }

    // Read the friendship pairs and build adjacency lists
    for (int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        friends_count[u]++;
        friends_count[v]++;
    }

    // Process each node and try to union the connected components
    for (int i = 1; i <= N; i++) {
        // Update min_friends with the number of friends each cow has
        min_friends[i] = friends_count[i];
        for (int v : adj[i]) {
            unionSets(i, v);
        }
    }

    // Compute the maximum strength
    int max_strength = 0;
    for (int i = 1; i <= N; i++) {
        if (find(i) == i) { // Root of the component
            max_strength = max(max_strength, sz[i] * min_friends[i]);
        }
    }

    // Output the result
    cout << max_strength << endl;
    
    return 0;
}


// g++ -std=c++17 -o a usaco_1259.cpp && ./a < a.in