#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

const int MAXN = 1002;  // Max nodes, including source and sink
const int INF = 1e9;

int capacity[MAXN][MAXN];  // capacity of the edges
vector<int> adj[MAXN];     // adjacency list for the graph
int parent[MAXN];          // to store the augmenting path

// BFS to find an augmenting path in the residual graph
bool bfs(int source, int sink) {
    memset(parent, -1, sizeof(parent));
    parent[source] = -2;  // Mark the source as visited
    queue<pair<int, int>> q;
    q.push({source, INF});
    
    while (!q.empty()) {
        int cur = q.front().first;
        int flow = q.front().second;
        q.pop();
        
        for (int next : adj[cur]) {
            if (parent[next] == -1 && capacity[cur][next] > 0) {  // Not visited and has capacity
                parent[next] = cur;
                int new_flow = min(flow, capacity[cur][next]);
                if (next == sink) {
                    return new_flow;  // Return the flow when we reach the sink
                }
                q.push({next, new_flow});
            }
        }
    }
    return 0;
}

// Edmonds-Karp algorithm to calculate max flow
int edmonds_karp(int source, int sink) {
    int flow = 0, new_flow;
    
    while (new_flow = bfs(source, sink)) {
        flow += new_flow;
        int cur = sink;
        // Update the capacities in the residual graph
        while (cur != source) {
            int prev = parent[cur];
            capacity[prev][cur] -= new_flow;
            capacity[cur][prev] += new_flow;  // Add reverse edge
            cur = prev;
        }
    }
    
    return flow;
}

int main() {
    int n, m, k;
    cin >> n >> m >> k;
    
    int source = 0, sink = n + m + 1;  // Source is node 0, sink is node n + m + 1

    // Input potential pairs and build the graph
    for (int i = 0; i < k; ++i) {
        int a, b;
        cin >> a >> b;
        b += n;  // Shift girl's index to avoid conflict with boy indices
        adj[a].push_back(b);
        adj[b].push_back(a);
        capacity[a][b] = 1;  // Capacity of the pair is 1
    }
    
    // Connect source to all boys
    for (int i = 1; i <= n; ++i) {
        adj[source].push_back(i);
        adj[i].push_back(source);
        capacity[source][i] = 1;
    }
    
    // Connect all girls to the sink
    for (int i = n + 1; i <= n + m; ++i) {
        adj[i].push_back(sink);
        adj[sink].push_back(i);
        capacity[i][sink] = 1;
    }
    
    // Calculate maximum flow (i.e., maximum number of pairs)
    int max_pairs = edmonds_karp(source, sink);
    cout << max_pairs << endl;
    
    // Output the pairs
    for (int boy = 1; boy <= n; ++boy) {
        for (int girl = n + 1; girl <= n + m; ++girl) {
            if (capacity[girl][boy] == 1) {  // A pair is formed if reverse edge has flow
                cout << boy << " " << girl - n << endl;
            }
        }
    }
    
    return 0;
}
