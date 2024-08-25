#include <iostream>
#include <vector>

using namespace std;

const int LOG = 18;  // log2(200000) ~ 17.6, so we use 18 for safety

vector<vector<int>> up;
vector<int> depth;

void dfs(int node, int parent, const vector<vector<int>>& adj) {
    up[node][0] = parent;
    for (int i = 1; i <= LOG; ++i) {
        if (up[node][i - 1] != -1) {
            up[node][i] = up[up[node][i - 1]][i - 1];
        }
    }
    for (int neighbor : adj[node]) {
        if (neighbor != parent) {
            depth[neighbor] = depth[node] + 1;
            dfs(neighbor, node, adj);
        }
    }
}

int lca(int a, int b) {
    if (depth[a] < depth[b]) swap(a, b);

    // Bring a and b to the same depth
    for (int i = LOG; i >= 0; --i) {
        if (depth[a] - (1 << i) >= depth[b]) {
            a = up[a][i];
        }
    }

    if (a == b) return a;

    // Lift both a and b up until they meet at LCA
    for (int i = LOG; i >= 0; --i) {
        if (up[a][i] != up[b][i]) {
            a = up[a][i];
            b = up[b][i];
        }
    }

    return up[a][0];
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, q;
    cin >> n >> q;

    vector<vector<int>> adj(n + 1);
    up.assign(n + 1, vector<int>(LOG + 1, -1));
    depth.assign(n + 1, 0);

    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    // Start DFS from node 1 (assuming it's the root)
    dfs(1, -1, adj);

    for (int i = 0; i < q; ++i) {
        int a, b;
        cin >> a >> b;
        int lca_ab = lca(a, b);
        int distance = depth[a] + depth[b] - 2 * depth[lca_ab];
        cout << distance << endl;
    }

    return 0;
}
