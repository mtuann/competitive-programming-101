#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <cstring>

using namespace std;

const int MAXN = 1000;
const int INF = INT_MAX;

struct Edge {
    int to, capacity, flow, reverse_index;
};

vector<Edge> adj[MAXN + 1];
int level[MAXN + 1];
int start[MAXN + 1];

// Add edge to the graph
void add_edge(int u, int v, int capacity) {
    adj[u].push_back({v, capacity, 0, (int)adj[v].size()});
    adj[v].push_back({u, 0, 0, (int)adj[u].size() - 1});
}

// BFS to build level graph
bool bfs(int source, int sink) {
    memset(level, -1, sizeof(level));
    level[source] = 0;
    queue<int> q;
    q.push(source);
    
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        
        for (const auto& edge : adj[u]) {
            if (level[edge.to] < 0 && edge.flow < edge.capacity) {
                level[edge.to] = level[u] + 1;
                q.push(edge.to);
            }
        }
    }
    return level[sink] >= 0;
}

// DFS to send flow along augmenting paths
int dfs(int u, int sink, int flow) {
    if (u == sink) return flow;
    
    for (; start[u] < (int)adj[u].size(); start[u]++) {
        Edge& edge = adj[u][start[u]];
        
        if (level[edge.to] == level[u] + 1 && edge.flow < edge.capacity) {
            int curr_flow = min(flow, edge.capacity - edge.flow);
            int temp_flow = dfs(edge.to, sink, curr_flow);
            
            if (temp_flow > 0) {
                edge.flow += temp_flow;
                adj[edge.to][edge.reverse_index].flow -= temp_flow;
                return temp_flow;
            }
        }
    }
    return 0;
}

// Dinic's algorithm to find maximum flow
long long dinic(int source, int sink) {
    long long max_flow = 0;
    
    while (bfs(source, sink)) {
        memset(start, 0, sizeof(start));
        
        while (int flow = dfs(source, sink, INF)) {
            max_flow += flow;
        }
    }
    return max_flow;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, s, t;
    cin >> n >> m >> s >> t;
    
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        add_edge(a, b, c);
    }
    
    cout << dinic(s, t) << endl;
    
    return 0;
}

// g++ -std=c++11 -O2 -Wall nkflow.cpp -o a && ./a < a.in