#include <iostream>
#include <vector>
#include <queue>

using namespace std;

void bfs(int start, const vector<vector<int>>& adj, vector<bool>& visited) {
    queue<int> q;
    q.push(start);
    visited[start] = true;

    while (!q.empty()) {
        int node = q.front();
        q.pop();
        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj(n + 1);
    vector<bool> visited(n + 1, false);

    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    vector<int> component_representatives;

    for (int i = 1; i <= n; ++i) {
        if (!visited[i]) {
            component_representatives.push_back(i);
            bfs(i, adj, visited);
        }
    }

    int num_new_roads = component_representatives.size() - 1;
    cout << num_new_roads << endl;

    for (int i = 1; i < component_representatives.size(); ++i) {
        cout << component_representatives[i - 1] << " " << component_representatives[i] << endl;
    }

    return 0;
}
