#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <queue>

using namespace std;

void findLongestPath(int n, int m, vector<pair<int, int>>& edges) {
    vector<vector<int>> adj(n + 1);
    vector<int> indegree(n + 1, 0);

    // Build the adjacency list and calculate indegrees
    for (auto edge : edges) {
        int a = edge.first, b = edge.second;
        adj[a].push_back(b);
        indegree[b]++;
    }

    // Topological sort using Kahn's algorithm
    queue<int> q;
    for (int i = 1; i <= n; i++) {
        if (indegree[i] == 0) {
            q.push(i);
        }
    }

    vector<int> topo_order;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        topo_order.push_back(u);

        for (int v : adj[u]) {
            indegree[v]--;
            if (indegree[v] == 0) {
                q.push(v);
            }
        }
    }

    // Initialize the dp and parent arrays
    vector<int> dp(n + 1, -1);
    vector<int> parent(n + 1, -1);
    dp[1] = 1;

    // Process nodes in topological order
    for (int u : topo_order) {
        if (dp[u] != -1) {
            for (int v : adj[u]) {
                if (dp[u] + 1 > dp[v]) {
                    dp[v] = dp[u] + 1;
                    parent[v] = u;
                }
            }
        }
    }

    // If there's no path to the last city
    if (dp[n] == -1) {
        cout << "IMPOSSIBLE" << endl;
        return;
    }

    // Reconstruct the path from Syrjälä to Lehmälä
    vector<int> path;
    for (int u = n; u != -1; u = parent[u]) {
        path.push_back(u);
    }
    reverse(path.begin(), path.end());

    // Output the result
    cout << dp[n] << endl;
    for (int city : path) {
        cout << city << " ";
    }
    cout << endl;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> edges(m);
    for (int i = 0; i < m; i++) {
        cin >> edges[i].first >> edges[i].second;
    }
    findLongestPath(n, m, edges);
    return 0;
}
