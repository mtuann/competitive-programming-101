#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

const int LOG = 18;  // log2(200000) ~ 17.6, so we use 18 for safety

vector<vector<int>> up;
vector<int> depth;

void preprocess(int n, const vector<int>& boss) {
    up.assign(n + 1, vector<int>(LOG + 1, -1));
    depth.assign(n + 1, 0);
    
    for (int i = 2; i <= n; ++i) {
        up[i][0] = boss[i-2];  // boss[i] is the direct boss of employee i+1
        depth[i] = depth[boss[i-2]] + 1;
    }

    for (int j = 1; j <= LOG; ++j) {
        for (int i = 1; i <= n; ++i) {
            if (up[i][j-1] != -1) {
                up[i][j] = up[up[i][j-1]][j-1];
            }
        }
    }
}

int get_kth_ancestor(int x, int k) {
    if (depth[x] < k) return -1;

    for (int j = LOG; j >= 0; --j) {
        if ((k >> j) & 1) {
            x = up[x][j];
            if (x == -1) return -1;
        }
    }
    return x;
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
        int x, k;
        cin >> x >> k;
        cout << get_kth_ancestor(x, k) << endl;
    }

    return 0;
}
