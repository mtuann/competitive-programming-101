#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class LCA {
public:
    vector<vector<int>> up;  // up[v][j] is the 2^j-th ancestor of node v
    vector<int> depth;       // depth of each node
    int LOG;

    LCA(int n) {
        LOG = log2(n) + 1;
        up.assign(n, vector<int>(LOG, -1));
        depth.assign(n, 0);
    }

    void dfs(int v, int p, const vector<vector<int>>& adj) {
        up[v][0] = p;  // immediate parent of v
        for (int j = 1; j < LOG; j++) {
            if (up[v][j-1] != -1)
                up[v][j] = up[up[v][j-1]][j-1];
        }
        for (int u : adj[v]) {
            if (u != p) {
                depth[u] = depth[v] + 1;
                dfs(u, v, adj);
            }
        }
    }

    void preprocess(int root, const vector<vector<int>>& adj) {
        dfs(root, -1, adj);
    }

    int lca(int u, int v) {
        if (depth[u] < depth[v])
            swap(u, v);
        
        // Bring u and v to the same depth
        int diff = depth[u] - depth[v];
        for (int j = 0; j < LOG; j++) {
            if ((diff >> j) & 1)
                u = up[u][j];
        }

        if (u == v)
            return u;

        // Binary lifting
        for (int j = LOG-1; j >= 0; j--) {
            if (up[u][j] != up[v][j]) {
                u = up[u][j];
                v = up[v][j];
            }
        }

        return up[u][0];
    }
};

int main() {
    int n = 9;
    vector<vector<int>> adj(n);

    // Example tree structure
    adj[0].push_back(1);
    adj[1].push_back(0);

    adj[0].push_back(2);
    adj[2].push_back(0);

    adj[1].push_back(3);
    adj[3].push_back(1);

    adj[1].push_back(4);
    adj[4].push_back(1);

    adj[2].push_back(5);
    adj[5].push_back(2);

    adj[2].push_back(6);
    adj[6].push_back(2);

    adj[4].push_back(7);
    adj[7].push_back(4);

    adj[4].push_back(8);
    adj[8].push_back(4);

    LCA lca_solver(n);
    lca_solver.preprocess(0, adj);

    cout << "LCA of 7 and 8: " << lca_solver.lca(7, 8) << endl; // Should be 4
    cout << "LCA of 3 and 4: " << lca_solver.lca(3, 4) << endl; // Should be 1
    cout << "LCA of 5 and 6: " << lca_solver.lca(5, 6) << endl; // Should be 2
    cout << "LCA of 3 and 6: " << lca_solver.lca(3, 6) << endl; // Should be 0

    return 0;
}
