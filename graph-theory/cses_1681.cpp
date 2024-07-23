#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int MOD = 1e9 + 7;

void findWays(int n, int m, vector<pair<int, int>>& edges) {
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

    // Initialize the dp array
    vector<int> dp(n + 1, 0);
    dp[1] = 1;

    // Process nodes in topological order
    for (int u : topo_order) {
        for (int v : adj[u]) {
            dp[v] = (dp[v] + dp[u]) % MOD;
        }
    }

    // Output the number of ways to reach level n
    cout << dp[n] << endl;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> edges(m);
    for (int i = 0; i < m; i++) {
        cin >> edges[i].first >> edges[i].second;
    }
    findWays(n, m, edges);
    return 0;
}
