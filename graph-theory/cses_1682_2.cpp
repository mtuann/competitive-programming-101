#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> graph, reverseGraph;
vector<bool> visited;

void dfs(int node, const vector<vector<int>> &adj) {
    visited[node] = true;
    for (int neighbor : adj[node]) {
        if (!visited[neighbor]) {
            dfs(neighbor, adj);
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;

    graph.resize(n + 1);
    reverseGraph.resize(n + 1);
    
    // Input the flight connections
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        reverseGraph[b].push_back(a);  // Reverse the direction of edges
    }

    // Step 1: Check if all nodes are reachable from node 1
    visited.assign(n + 1, false);
    dfs(1, graph);
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            cout << "NO\n" << "1 " << i << "\n";
            return 0;
        }
    }

    // Step 2: Check if all nodes can reach node 1 (reverse graph)
    visited.assign(n + 1, false);
    dfs(1, reverseGraph);
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            cout << "NO\n" << i << " 1\n";
            return 0;
        }
    }

    // If both checks pass, the graph is strongly connected
    cout << "YES\n";
    return 0;
}
