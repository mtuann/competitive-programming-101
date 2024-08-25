#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 200000;
vector<int> adj[MAXN + 1];
int value[MAXN + 1];
int entry[MAXN + 1], exit_node[MAXN + 1], flat[MAXN + 1];
int timer = 0;

void dfs(int node, int parent) {
    entry[node] = ++timer;
    flat[timer] = node;
    for (int neighbor : adj[node]) {
        if (neighbor != parent) {
            dfs(neighbor, node);
        }
    }
    exit_node[node] = timer;
}

class FenwickTree {
public:
    FenwickTree(int size) : size(size) {
        tree.assign(size + 1, 0);
    }

    void update(int index, int delta) {
        for (; index <= size; index += index & -index) {
            tree[index] += delta;
        }
    }

    long long query(int index) const {
        long long sum = 0;
        for (; index > 0; index -= index & -index) {
            sum += tree[index];
        }
        return sum;
    }

    long long rangeQuery(int left, int right) const {
        return query(right) - query(left - 1);
    }

private:
    vector<long long> tree;
    int size;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    for (int i = 1; i <= n; ++i) {
        cin >> value[i];
    }

    vector<pair<int, int>> edges(n - 1);
    for (auto& edge : edges) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    dfs(1, -1);

    FenwickTree fenwick(n);

    for (int i = 1; i <= n; ++i) {
        fenwick.update(entry[i], value[i]);
    }

    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            int s, x;
            cin >> s >> x;
            int current_value = fenwick.rangeQuery(entry[s], entry[s]);
            fenwick.update(entry[s], x - current_value);
        } else if (type == 2) {
            int s;
            cin >> s;
            cout << fenwick.rangeQuery(entry[s], exit_node[s]) << '\n';
        }
    }

    return 0;
}
