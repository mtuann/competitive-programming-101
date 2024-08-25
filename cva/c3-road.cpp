#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAXN = 500005;
vector<int> tree[MAXN];
vector<long long> top3[MAXN];
long long dist[MAXN];
long long depth[MAXN], height[MAXN];

// BFS to find the farthest node and its distance from the starting node
pair<int, int> bfs(int start, int n) {
    queue<int> q;
    vector<bool> visited(n + 1, false);
    q.push(start);
    visited[start] = true;
    dist[start] = 0;
    int farthest_node = start;

    while (!q.empty()) {
        int node = q.front();
        q.pop();
        for (int neighbor : tree[node]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                dist[neighbor] = dist[node] + 1;
                q.push(neighbor);
                if (dist[neighbor] > dist[farthest_node]) {
                    farthest_node = neighbor;
                }
            }
        }
    }
    return {farthest_node, dist[farthest_node]};
}

long long ans = 0;

void dfs(int u, int p) {
    top3[u].clear();
    top3[u].push_back(height[u]);
    
    depth[u] = 1;
    
    for (int v : tree[u]) {
        if (v == p) continue;
        height[v] = height[u] + 1;
        dfs(v, u);
        depth[u] = max(depth[u], depth[v] + 1);
        // for all children v of u, add the top 3 values of v to the top 3 values of u
        top3[u].push_back(depth[v]);
    }
    
    sort(top3[u].begin(), top3[u].end(), greater<int>());

    if (top3[u].size() >= 3) {
        ans = max(ans, 1ll * (top3[u][2] + top3[u][1]) * (top3[u][0]));
        ans = max(ans, 1ll * (top3[u][0] + top3[u][1]) * (top3[u][2]));
        ans = max(ans, 1ll * (top3[u][0] + top3[u][2]) * (top3[u][1]));
        // cout << u << " " << (top3[u][2] + top3[u][1]) * (top3[u][0]) << endl;
        // cout << top3[u][0] << " " << top3[u][1] << " " << top3[u][2] << endl;
    }

    if (top3[u].size() == 2) {
        ans = max(ans, 1ll * top3[u][0] * top3[u][1]);
    }
    // printf("u=%d, depth=%d, height=%d\n", u, depth[u], height[u]);

}
int main() {
    int n;
    cin >> n;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }

    // Step 1: Find the two most distant leaf nodes X1 and X2
    pair<int, int> p1 = bfs(1, n);  // Run BFS from any node, let's start from node 1
    pair<int, int> p2 = bfs(p1.first, n);  // Run BFS from the farthest node found

    // int X1 = p1.first;
    int X2 = p2.first;
    memset(height, 0, sizeof(height));
    memset(depth, 0, sizeof(depth));
    dfs(X2, 0);
    memset(height, 0, sizeof(height));
    memset(depth, 0, sizeof(depth));
    dfs(p1.first, 0);
    cout << ans << endl;
    

    return 0;
}
