// https://cses.fi/problemset/task/1668

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

bool bfs(int start, vector<vector<int>>& adj, vector<int>& team) {
    queue<int> q;
    q.push(start);
    team[start] = 1;  // Assign team 1 to the start node

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v : adj[u]) {
            if (team[v] == 0) {
                // Assign the opposite team to the adjacent node
                team[v] = 3 - team[u];
                q.push(v);
            } else if (team[v] == team[u]) {
                // If the adjacent node has the same team, the graph is not bipartite
                return false;
            }
        }
    }

    return true;
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj(n + 1); // Adjacency list for the graph
    vector<int> team(n + 1, 0); // Team assignment for each pupil, 0 means unassigned

    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    // Try to color the graph using BFS
    for (int i = 1; i <= n; ++i) {
        if (team[i] == 0) { // If the node is unassigned, perform BFS
            if (!bfs(i, adj, team)) {
                cout << "IMPOSSIBLE" << endl;
                return 0;
            }
        }
    }

    // If the graph is bipartite, print the team assignment
    for (int i = 1; i <= n; ++i) {
        cout << team[i] << " \n"[i == n];
    }

    return 0;
}
