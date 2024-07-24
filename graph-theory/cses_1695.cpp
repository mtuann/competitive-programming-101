#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

const int MAXN = 500;
const int INF = 1e9;

vector<int> adj[MAXN + 1];
int capacity[MAXN + 1][MAXN + 1];
int parent[MAXN + 1];

bool bfs(int source, int sink) {
    memset(parent, -1, sizeof(parent));
    queue<pair<int, int>> q;
    q.push({source, INF});
    
    while (!q.empty()) {
        int curr = q.front().first;
        int flow = q.front().second;
        q.pop();
        
        for (int next : adj[curr]) {
            if (parent[next] == -1 && capacity[curr][next]) {
                parent[next] = curr;
                int new_flow = min(flow, capacity[curr][next]);
                if (next == sink) return true;
                q.push({next, new_flow});
            }
        }
    }
    return false;
}

int edmonds_karp(int source, int sink) {
    int max_flow = 0;
    while (bfs(source, sink)) {
        int flow = INF;
        for (int curr = sink; curr != source; curr = parent[curr]) {
            int prev = parent[curr];
            flow = min(flow, capacity[prev][curr]);
        }
        for (int curr = sink; curr != source; curr = parent[curr]) {
            int prev = parent[curr];
            capacity[prev][curr] -= flow;
            capacity[curr][prev] += flow;
        }
        max_flow += flow;
    }
    return max_flow;
}

void dfs(int u, vector<bool>& visited) {
    visited[u] = true;
    for (int v : adj[u]) {
        if (!visited[v] && capacity[u][v] > 0) {
            dfs(v, visited);
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
        capacity[a][b] = 1;  // Unit capacity for each edge
        capacity[b][a] = 1;  // Since the streets are two-way
    }
    
    int source = 1;
    int sink = n;
    
    int max_flow = edmonds_karp(source, sink);
    
    vector<bool> visited(n + 1, false);
    dfs(source, visited);
    
    vector<pair<int, int>> min_cut_edges;
    for (int u = 1; u <= n; u++) {
        if (visited[u]) {
            for (int v : adj[u]) {
                if (!visited[v] && capacity[u][v] == 0) {
                    min_cut_edges.push_back({u, v});
                }
            }
        }
    }
    
    cout << min_cut_edges.size() << endl;
    for (auto edge : min_cut_edges) {
        cout << edge.first << " " << edge.second << endl;
    }
    
    return 0;
}
