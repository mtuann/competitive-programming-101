#include <iostream>
#include <vector>

using namespace std;

const int LOG = 18;  // log2(200000) ~ 17.6, so we use 18 for safety

vector<vector<int>> up;
vector<int> depth;

void preprocess(int n, const vector<int>& boss) {
    up.assign(n + 1, vector<int>(LOG + 1, -1));
    depth.assign(n + 1, 0);
    
    for (int i = 2; i <= n; ++i) {
        up[i][0] = boss[i - 2];  // boss[i] is the direct boss of employee i+1
        depth[i] = depth[boss[i - 2]] + 1;
    }

    for (int j = 1; j <= LOG; ++j) {
        for (int i = 1; i <= n; ++i) {
            if (up[i][j - 1] != -1) {
                up[i][j] = up[up[i][j - 1]][j - 1];
            }
        }
    }
}

int lca(int a, int b) {
    if (depth[a] < depth[b]) {
        swap(a, b);
    }

    // Lift a to the same level as b
    for (int j = LOG; j >= 0; --j) {
        if (depth[a] - (1 << j) >= depth[b]) {
            a = up[a][j];
        }
    }

    if (a == b) {
        return a;
    }

    // Lift both a and b up until they meet
    for (int j = LOG; j >= 0; --j) {
        if (up[a][j] != -1 && up[a][j] != up[b][j]) {
            a = up[a][j];
            b = up[b][j];
        }
    }

    // Their LCA is the parent of the node they both reached
    return up[a][0];
}

int main() {
    int n, q;
    cin >> n >> q;

    vector<int> boss(n - 1);
    for (int i = 0; i < n - 1; ++i) {
        cin >> boss[i];
    }

    preprocess(n, boss);

    for (int i = 0; i < q; ++i) {
        int a, b;
        cin >> a >> b;
        cout << lca(a, b) << endl;
    }

    return 0;
}
