#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int N = 1e5 + 5;
int n;
int b[N];

class DSU {
    vector<int> parent; // parent of each node: if parent[i] = i, then i is the root
    vector<int> sz; // size of each set
    vector<long long> sum; // sum of each set
public:
    DSU(int n, vector<int> &a) {
        parent.resize(n);
        sz.resize(n);
        sum.resize(n);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
            sz[i] = 1;
            sum[i] = a[i];
        }
    }

    long long get_sum(int x) {
        return sum[find(x)];
    }

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    void union_set(int x, int y) {
        int px = find(x);
        int py = find(y);
        if (px == py) return;
        if (sz[px] < sz[py]) swap(px, py);
        parent[py] = px;
        sz[px] += sz[py];
        sum[px] += sum[py];
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> b[i];
        b[i]--;
        // cout << "b[i]: " << b[i] << '\n';
    }

    
    DSU dsu(n, a);
    vector<long long> res;
    long long ans = 0;
    vector<bool> vis(n, false);

    for (int i = n - 1; i >= 0; --i) {
        
        res.push_back(ans);
        vis[b[i]] = true;
        int x = b[i] - 1;
        int y = b[i] + 1;

        if (x >= 0 && x < n && vis[x]) {
            dsu.union_set(b[i], x);
        }
        if (y >= 0 && y < n && vis[y]) {
            dsu.union_set(b[i], y);
        }
        ans = max(ans, dsu.get_sum(b[i]));
    }

    for (int i = n - 1; i >= 0; --i) {
        cout << res[i] << '\n';
    }

    return 0;
}

// clang++ -std=c++17 -o dsu dsu.cpp
