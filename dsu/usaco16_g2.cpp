// https://usaco.org/index.php?page=viewproblem2&cpid=646
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int N = 2e5 + 5;
int n, m;
vector<int> adj[N];
int a[N], b[N];

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
    freopen("closing.in", "r", stdin);
    freopen("closing.out", "w", stdout);
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        a[i]--;
        b[i] = 0;
    }
    vector<string> ans;
    DSU dsu(n);
    int cnt = 1;
    ans.push_back("YES");
    b[a[n - 1]] = 1;

    for (int i = n - 2; i >= 0; i--) {
        cnt += 1;
        b[a[i]] = 1;
        for (int v : adj[a[i]]) {
            if (b[v]) {
                int root_a = dsu.find(a[i]);
                int root_v = dsu.find(v);
                if (root_a != root_v) {
                    cnt--;
                    dsu.union_set(a[i], v);
                }
            }
        }
        if (cnt != 1) ans.push_back("NO");
        else ans.push_back("YES");
    }
    reverse(ans.begin(), ans.end());
    for (string s : ans) cout << s << '\n';


    return 0;
}
// g++ -std=c++17 -o a usaco16_g2.cpp && ./a

