#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <stack>

using namespace std;

const int MAXN = 500;
const int INF = 1e9;

struct Edge {
    int to, rev, cap, flow;
};

vector<Edge> adj[MAXN + 1];
int level[MAXN + 1], ptr[MAXN + 1];

void add_edge(int u, int v, int cap) {
    adj[u].push_back({v, (int)adj[v].size(), cap, 0});
    adj[v].push_back({u, (int)adj[u].size() - 1, 0, 0});  // reverse edge
}

bool bfs(int source, int sink) {
    memset(level, -1, sizeof(level));
    queue<int> q;
    q.push(source);
    level[source] = 0;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (Edge &e : adj[u]) {
            if (level[e.to] == -1 && e.flow < e.cap) {
                level[e.to] = level[u] + 1;
                q.push(e.to);
            }
        }
    }
    return level[sink] != -1;
}

int dfs(int u, int sink, int pushed) {
    if (pushed == 0) return 0;
    if (u == sink) return pushed;

    for (int &cid = ptr[u]; cid < (int)adj[u].size(); ++cid) {
        Edge &e = adj[u][cid];
        if (level[u] + 1 != level[e.to] || e.flow == e.cap) continue;
        int tr = dfs(e.to, sink, min(pushed, e.cap - e.flow));
        if (tr == 0) continue;
        e.flow += tr;
        adj[e.to][e.rev].flow -= tr;
        return tr;
    }
    return 0;
}

int dinic(int source, int sink) {
    int flow = 0;
    while (bfs(source, sink)) {
        memset(ptr, 0, sizeof(ptr));
        while (int pushed = dfs(source, sink, INF)) {
            flow += pushed;
        }
    }
    return flow;
}

void find_paths(int u, int sink, vector<int>& path, vector<vector<int>>& paths) {
    if (u == sink) {
        paths.push_back(path);
        return;
    }
    for (Edge &e : adj[u]) {
        if (e.flow > 0) {  // use the edge if it's part of the flow
            path.push_back(e.to);
            e.flow = 0;  // mark edge as used
            find_paths(e.to, sink, path, paths);
            path.pop_back();
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        add_edge(a, b, 1);  // Unit capacity for each teleporter
    }

    int source = 1;
    int sink = n;

    int max_days = dinic(source, sink);
    cout << max_days << endl;

    vector<vector<int>> paths;
    vector<int> path = {source};
    find_paths(source, sink, path, paths);

    for (const auto& p : paths) {
        cout << p.size() << endl;
        for (int room : p) {
            cout << room << " ";
        }
        cout << endl;
    }

    return 0;
}


// #include <iostream>
// #include <vector>
// #include <queue>
// #include <algorithm>
// #include <cstring>

// using namespace std;

// const int MAXN = 500;
// const int INF = 1e9;

// struct Edge {
//     int to, rev, cap, flow;
// };

// vector<Edge> adj[MAXN + 1];
// int level[MAXN + 1], ptr[MAXN + 1];

// void add_edge(int u, int v, int cap) {
//     adj[u].push_back({v, (int)adj[v].size(), cap, 0});
//     adj[v].push_back({u, (int)adj[u].size() - 1, 0, 0});  // reverse edge
// }

// bool bfs(int source, int sink) {
//     memset(level, -1, sizeof(level));
//     queue<int> q;
//     q.push(source);
//     level[source] = 0;

//     while (!q.empty()) {
//         int u = q.front();
//         q.pop();
//         for (Edge &e : adj[u]) {
//             if (level[e.to] == -1 && e.flow < e.cap) {
//                 level[e.to] = level[u] + 1;
//                 q.push(e.to);
//             }
//         }
//     }
//     return level[sink] != -1;
// }

// int dfs(int u, int sink, int pushed) {
//     if (pushed == 0) return 0;
//     if (u == sink) return pushed;

//     for (int &cid = ptr[u]; cid < (int)adj[u].size(); ++cid) {
//         Edge &e = adj[u][cid];
//         if (level[u] + 1 != level[e.to] || e.flow == e.cap) continue;
//         int tr = dfs(e.to, sink, min(pushed, e.cap - e.flow));
//         if (tr == 0) continue;
//         e.flow += tr;
//         adj[e.to][e.rev].flow -= tr;
//         return tr;
//     }
//     return 0;
// }

// int dinic(int source, int sink) {
//     int flow = 0;
//     while (bfs(source, sink)) {
//         memset(ptr, 0, sizeof(ptr));
//         while (int pushed = dfs(source, sink, INF)) {
//             flow += pushed;
//         }
//     }
//     return flow;
// }

// void find_paths(int u, int sink, vector<int>& path, vector<bool>& visited, vector<vector<int>>& paths) {
//     if (u == sink) {
//         paths.push_back(path);
//         return;
//     }
//     visited[u] = true;
//     for (Edge &e : adj[u]) {
//         if (e.flow > 0 && !visited[e.to]) {
//             path.push_back(e.to);
//             e.flow = 0;  // Mark the edge as used
//             find_paths(e.to, sink, path, visited, paths);
//             path.pop_back();
//         }
//     }
//     visited[u] = false;
// }

// int main() {
//     int n, m;
//     cin >> n >> m;

//     for (int i = 0; i < m; i++) {
//         int a, b;
//         cin >> a >> b;
//         add_edge(a, b, 1);  // Unit capacity for each teleporter
//     }

//     int source = 1;
//     int sink = n;

//     int max_days = dinic(source, sink);
//     cout << max_days << endl;

//     vector<vector<int>> paths;
//     vector<bool> visited(n + 1, false);
//     vector<int> path = {source};

//     for (int i = 0; i < max_days; ++i) {
//         find_paths(source, sink, path, visited, paths);
//     }

//     for (const auto& p : paths) {
//         cout << p.size() << endl;
//         for (int room : p) {
//             cout << room << " ";
//         }
//         cout << endl;
//     }

//     return 0;
// }


// #include <iostream>
// #include <vector>
// #include <queue>
// #include <cstring>

// using namespace std;

// const int MAXN = 500;
// const int INF = 1e9;

// vector<int> adj[MAXN + 1];
// int capacity[MAXN + 1][MAXN + 1];
// int parent[MAXN + 1];

// bool bfs(int source, int sink) {
//     memset(parent, -1, sizeof(parent));
//     queue<pair<int, int>> q;
//     q.push({source, INF});
    
//     while (!q.empty()) {
//         int curr = q.front().first;
//         int flow = q.front().second;
//         q.pop();
        
//         for (int next : adj[curr]) {
//             if (parent[next] == -1 && capacity[curr][next]) {
//                 parent[next] = curr;
//                 int new_flow = min(flow, capacity[curr][next]);
//                 if (next == sink) return true;
//                 q.push({next, new_flow});
//             }
//         }
//     }
//     return false;
// }

// int edmonds_karp(int source, int sink) {
//     int max_flow = 0;
//     while (bfs(source, sink)) {
//         int flow = INF;
//         for (int curr = sink; curr != source; curr = parent[curr]) {
//             int prev = parent[curr];
//             flow = min(flow, capacity[prev][curr]);
//         }
//         for (int curr = sink; curr != source; curr = parent[curr]) {
//             int prev = parent[curr];
//             capacity[prev][curr] -= flow;
//             capacity[curr][prev] += flow;
//         }
//         max_flow += flow;
//     }
//     return max_flow;
// }

// vector<vector<int>> find_paths(int source, int sink, int n) {
//     vector<vector<int>> paths;
//     vector<bool> visited(n + 1, false);
//     while (true) {
//         queue<int> q;
//         vector<int> path;
//         q.push(source);
//         visited[source] = true;
//         bool found = false;
        
//         while (!q.empty() && !found) {
//             int node = q.front();
//             q.pop();
//             path.push_back(node);
            
//             if (node == sink) {
//                 found = true;
//                 break;
//             }
            
//             for (int next : adj[node]) {
//                 if (capacity[node][next] == 0 && !visited[next]) {
//                     visited[next] = true;
//                     q.push(next);
//                     break;
//                 }
//             }
//         }
        
//         if (!found) break;
        
//         paths.push_back(path);
//         for (int i = 1; i <= n; i++) visited[i] = false;
//     }
//     return paths;
// }

// int main() {
//     int n, m;
//     cin >> n >> m;
    
//     for (int i = 0; i < m; i++) {
//         int a, b;
//         cin >> a >> b;
//         adj[a].push_back(b);
//         capacity[a][b] = 1;  // Unit capacity for each teleporter
//     }
    
//     int source = 1;
//     int sink = n;
    
//     int max_days = edmonds_karp(source, sink);
//     cout << max_days << endl;
    
//     vector<vector<int>> paths = find_paths(source, sink, n);
//     for (const auto& path : paths) {
//         cout << path.size() << endl;
//         for (int room : path) {
//             cout << room << " ";
//         }
//         cout << endl;
//     }
    
//     return 0;
// }
