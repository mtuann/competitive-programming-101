#include <iostream>
#include <vector>
#include <stack>

using namespace std;

bool dfs(int node, int parent, const vector<vector<int>>& adj, vector<int>& visited, vector<int>& parent_track, int& cycle_start, int& cycle_end) {
    visited[node] = 1; // Mark node as visited
    for (int neighbor : adj[node]) {
        if (neighbor == parent) continue; // Ignore the edge to the parent node
        if (visited[neighbor]) {
            // Cycle found
            cycle_start = neighbor;
            cycle_end = node;
            return true;
        }
        parent_track[neighbor] = node;
        if (dfs(neighbor, node, adj, visited, parent_track, cycle_start, cycle_end)) {
            return true;
        }
    }
    return false;
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    vector<int> visited(n + 1, 0);
    vector<int> parent_track(n + 1, -1);
    int cycle_start = -1, cycle_end = -1;

    for (int i = 1; i <= n; ++i) {
        if (!visited[i]) {
            if (dfs(i, -1, adj, visited, parent_track, cycle_start, cycle_end)) {
                break;
            }
        }
    }

    if (cycle_start == -1) {
        cout << "IMPOSSIBLE" << endl;
    } else {
        vector<int> cycle;
        cycle.push_back(cycle_start);
        for (int v = cycle_end; v != cycle_start; v = parent_track[v]) {
            cycle.push_back(v);
        }
        cycle.push_back(cycle_start);
        reverse(cycle.begin(), cycle.end());

        cout << cycle.size() << endl;
        for (int v : cycle) {
            cout << v << " ";
        }
        cout << endl;
    }

    return 0;
}
// g++ -std=c++17 cses_1669.cpp -o a && ./a < a.in