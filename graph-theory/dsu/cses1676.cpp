// https://cses.fi/problemset/task/1676
// https://cses.fi/problemset/result/9464662/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int N = 1e5 + 5;
int n, m;

class DSU {
    vector<int> parent; // parent of each node: if parent[i] = i, then i is the root
    vector<int> sz; // size of each set

public:
    DSU(int n) {
        parent.resize(n);
        sz.resize(n);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
            sz[i] = 1;
        }
    }

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    int get_size(int x) {
        return sz[find(x)];
    }

    void union_set(int x, int y) {
        int px = find(x);
        int py = find(y);
        if (px == py) return;
        if (sz[px] < sz[py]) swap(px, py);
        parent[py] = px;
        sz[px] += sz[py];
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m;
    
    DSU dsu(n);
    int total = n, max_size = 1;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        if (dsu.find(u) == dsu.find(v)) {
            cout << total << ' ' << max_size << '\n';
            continue;
        } else {
            total--;
            dsu.union_set(u, v);
            max_size = max(max_size, dsu.get_size(u));
            cout << total << ' ' << max_size << '\n';
        }
    }
    return 0;
}
// g++ -std=c++17 -o a cses1676.cpp && ./a

