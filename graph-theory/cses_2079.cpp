#include <iostream>
#include <vector>
using namespace std;

const int MAXN = 200005;
int n;
vector<int> adj[MAXN];
int subtree_size[MAXN];

void dfs(int u, int parent, int& centroid, int total_nodes) {
    subtree_size[u] = 1;
    bool is_centroid = true;

    for (int v : adj[u]) {
        if (v == parent) continue;
        dfs(v, u, centroid, total_nodes);
        subtree_size[u] += subtree_size[v];

        // Check if the current node u can be a centroid
        if (subtree_size[v] > total_nodes / 2) {
            is_centroid = false;
        }
    }

    // Check the size of the "remaining" tree (outside of the subtree rooted at u)
    if (total_nodes - subtree_size[u] > total_nodes / 2) {
        is_centroid = false;
    }

    if (is_centroid) {
        centroid = u;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n;
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    int centroid = -1;
    dfs(1, -1, centroid, n);

    cout << centroid << "\n";

    return 0;
}
