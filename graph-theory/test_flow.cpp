#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <cstring>

using namespace std;

const int MAXN = 500;
const int INF = INT_MAX;

vector<int> adj[MAXN + 1];  // adjacency list
int capacity[MAXN + 1][MAXN + 1];  // capacity of edges
int parent[MAXN + 1];  // to store path

// BFS to find an augmenting path
bool bfs(int source, int sink, int n) {
    memset(parent, -1, sizeof(parent));
    queue<pair<int, int>> q;
    q.push({source, INF});
    
    while (!q.empty()) {
        int cur = q.front().first;
        int flow = q.front().second;
        q.pop();
        
        for (int next : adj[cur]) {
            if (parent[next] == -1 && capacity[cur][next] > 0) {  // if not visited and has capacity
                parent[next] = cur;
                int new_flow = min(flow, capacity[cur][next]);
                if (next == sink)
                    return new_flow;  // found a path
                q.push({next, new_flow});
            }
        }
    }
    return 0;
}

// Edmonds-Karp: Max Flow
int edmonds_karp(int source, int sink, int n) {
    int flow = 0, new_flow;
    
    while (new_flow = bfs(source, sink, n)) {
        flow += new_flow;
        int cur = sink;
        while (cur != source) {
            int prev = parent[cur];
            capacity[prev][cur] -= new_flow;
            capacity[cur][prev] += new_flow;
            cur = prev;
        }
    }
    
    return flow;
}

void find_paths(int source, int sink, int n) {
    vector<vector<int>> paths;
    
    while (true) {
        vector<int> path;
        queue<int> q;
        q.push(source);
        vector<bool> visited(n + 1, false);
        visited[source] = true;
        
        while (!q.empty() && q.front() != sink) {
            int cur = q.front();
            q.pop();
            path.push_back(cur);
            for (int next : adj[cur]) {
                if (!visited[next] && capacity[cur][next] == 0) {  // path with no remaining capacity
                    visited[next] = true;
                    q.push(next);
                    path.push_back(next);
                    break;
                }
            }
        }
        
        if (q.empty()) break;  // no more paths
        
        paths.push_back(path);
    }
    
    // Output the paths
    cout << paths.size() << "\n";  // number of paths
    for (const auto& path : paths) {
        cout << path.size() << "\n";  // path length
        for (int room : path) {
            cout << room << " ";
        }
        cout << "\n";
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    
    // Input teleports and build capacity graph
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);  // for reverse edge in residual graph
        capacity[a][b] = 1;  // each teleporter can be used once
    }
    
    // Run Edmonds-Karp max flow algorithm
    int max_flow = edmonds_karp(1, n, n);
    
    // Output max flow
    cout << max_flow << "\n";
    
    // Find and output paths
    find_paths(1, n, n);
    
    return 0;
}

// g++ -std=c++11 test_flow.cpp -o a && ./a < a.in
