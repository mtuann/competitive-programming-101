#include <iostream>
#include <vector>

using namespace std;

const int LOG = 18;  // log2(200000) ~ 17.6, so we use 18 for safety
const int MAXN = 10 + 200000;
vector<vector<int>> up;
vector<int> depth;
vector<int> subtreeSize;
vector<vector<int>> adj;

void dfs(int node, int parent) {
    up[node][0] = parent;
    for (int i = 1; i <= LOG; ++i) {
        if (up[node][i - 1] != -1) {
            up[node][i] = up[up[node][i - 1]][i - 1];
        }
    }
    for (int neighbor : adj[node]) {
        if (neighbor != parent) {
            depth[neighbor] = depth[node] + 1;
            dfs(neighbor, node);
        }
    }
}

int lca(int a, int b) {
    if (depth[a] < depth[b]) swap(a, b);

    // Lift a to the same level as b
    for (int i = LOG; i >= 0; --i) {
        if (depth[a] - (1 << i) >= depth[b]) {
            a = up[a][i];
        }
    }

    if (a == b) return a;

    // Lift both a and b up until they meet
    for (int i = LOG; i >= 0; --i) {
        if (up[a][i] != up[b][i]) {
            a = up[a][i];
            b = up[b][i];
        }
    }

    return up[a][0];
}

int n, m;

int c[MAXN];
int pathCount[MAXN];
int stopCount[MAXN];
int ans[MAXN];

void dfs2(int node, int parent) {
    // subtreeSize[node] = 1;
    for (int neighbor : adj[node]) {
        if (neighbor != parent) {
            dfs2(neighbor, node);
            pathCount[node] += pathCount[neighbor];
        }
    }
    ans[node] += pathCount[node] - c[node];
    pathCount[node] -= stopCount[node];
}

void processPaths(vector<pair<int, int>> &paths) {
    for (auto &path : paths) {
        int u = path.first, v = path.second;
        int lcaNode = lca(u, v);
        cout << "LCA(" << u << ", " << v << ") = " << lcaNode << endl;
        // The path contribution counts for u to lcaNode, and v to lcaNode.
        pathCount[u]++;
        pathCount[v]++;
        stopCount[lcaNode] += 2;
        if (lcaNode != u && lcaNode != v) c[lcaNode]+=1;
        else pathCount[lcaNode]--, stopCount[lcaNode]--;
    }
    dfs2(1, -1);
    for (int i = 1; i <= n; ++i) {
        cout << ans[i] << " ";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> m;

    adj.assign(n + 1, vector<int>());
    up.assign(n + 1, vector<int>(LOG + 1, -1));
    depth.assign(n + 1, 0);
    subtreeSize.assign(n + 1, 0);

    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    dfs(1, -1);

    vector<pair<int, int>> paths(m);
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        paths[i] = {a, b};
    }

    processPaths(paths);

    return 0;
}

// g++ -std=c++20 -o a cses_1136.cpp && ./a < a.in