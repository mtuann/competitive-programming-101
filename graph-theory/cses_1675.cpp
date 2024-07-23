#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Edge {
    int u, v, cost;
    bool operator<(const Edge& other) const {
        return cost < other.cost;
    }
};

vector<int> parent, rnk;

int find(int x) {
    if (parent[x] != x)
        parent[x] = find(parent[x]);
    return parent[x];
}

void unionSet(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);

    if (rootX != rootY) {
        if (rnk[rootX] > rnk[rootY]) {
            parent[rootY] = rootX;
        } else if (rnk[rootX] < rnk[rootY]) {
            parent[rootX] = rootY;
        } else {
            parent[rootY] = rootX;
            rnk[rootX]++;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<Edge> edges(m);
    for (int i = 0; i < m; ++i) {
        cin >> edges[i].u >> edges[i].v >> edges[i].cost;
        --edges[i].u;
        --edges[i].v;
    }

    sort(edges.begin(), edges.end());

    parent.resize(n);
    rnk.resize(n, 0);
    for (int i = 0; i < n; ++i) {
        parent[i] = i;
    }

    long long totalCost = 0;
    int edgeCount = 0;

    for (const Edge& e : edges) {
        int rootU = find(e.u);
        int rootV = find(e.v);

        if (rootU != rootV) {
            unionSet(rootU, rootV);
            totalCost += e.cost;
            edgeCount++;
        }

        if (edgeCount == n - 1) {
            break;
        }
    }

    if (edgeCount == n - 1) {
        cout << totalCost << "\n";
    } else {
        cout << "IMPOSSIBLE\n";
    }

    return 0;
}
