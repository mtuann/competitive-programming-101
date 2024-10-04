#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 200005;
vector<int> adj[MAXN];
int parent[MAXN], depth[MAXN], heavy[MAXN], head[MAXN], pos[MAXN], subtree_size[MAXN];
int values[MAXN];  // original values at each node
int segtree[4 * MAXN];  // segment tree to store max values
int cur_pos = 0;

// Segment Tree Operations
void build(int node, int start, int end) {
    if (start == end) {
        segtree[node] = values[start];
    } else {
        int mid = (start + end) / 2;
        build(2 * node, start, mid);
        build(2 * node + 1, mid + 1, end);
        segtree[node] = max(segtree[2 * node], segtree[2 * node + 1]);
    }
}

void update(int node, int start, int end, int idx, int value) {
    if (start == end) {
        segtree[node] = value;
    } else {
        int mid = (start + end) / 2;
        if (idx <= mid) {
            update(2 * node, start, mid, idx, value);
        } else {
            update(2 * node + 1, mid + 1, end, idx, value);
        }
        segtree[node] = max(segtree[2 * node], segtree[2 * node + 1]);
    }
}

int query(int node, int start, int end, int l, int r) {
    if (r < start || end < l)
        return -1;  // outside the range
    if (l <= start && end <= r)
        return segtree[node];  // fully inside the range
    int mid = (start + end) / 2;
    return max(query(2 * node, start, mid, l, r), query(2 * node + 1, mid + 1, end, l, r));
}

// DFS to find subtree sizes and determine heavy edges
int dfs(int u) {
    int size = 1;
    int max_size = 0;
    for (int v : adj[u]) {
        if (v != parent[u]) {
            parent[v] = u;
            depth[v] = depth[u] + 1;
            int v_size = dfs(v);
            size += v_size;
            if (v_size > max_size) {
                max_size = v_size;
                heavy[u] = v;
            }
        }
    }
    return size;
}

// Decomposing the tree into chains
void decompose(int u, int h) {
    head[u] = h;  // head of the current chain
    pos[u] = ++cur_pos;  // position in the segment tree
    values[pos[u]] = values[u];  // values in the segment tree are based on the original values

    if (heavy[u] != -1) {
        decompose(heavy[u], h);
    }

    for (int v : adj[u]) {
        if (v != parent[u] && v != heavy[u]) {
            decompose(v, v);  // start a new chain
        }
    }
}

// Query the maximum value on the path from u to v
int query_up(int u, int v) {
    int res = -1;
    while (head[u] != head[v]) {
        if (depth[head[u]] < depth[head[v]])
            swap(u, v);
        res = max(res, query(1, 1, cur_pos, pos[head[u]], pos[u]));
        u = parent[head[u]];
    }
    if (depth[u] > depth[v])
        swap(u, v);
    res = max(res, query(1, 1, cur_pos, pos[u], pos[v]));
    return res;
}

// Update the value of node u
void update_value(int u, int new_value) {
    update(1, 1, cur_pos, pos[u], new_value);
}

int main() {
    int n, q;
    cin >> n >> q;

    for (int i = 1; i <= n; i++) {
        cin >> values[i];  // read initial values
    }

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // Initialize
    fill(heavy, heavy + n + 1, -1);

    // DFS to calculate heavy edges and sizes
    parent[1] = -1;
    depth[1] = 0;
    dfs(1);

    // Decompose the tree
    decompose(1, 1);

    // Build the segment tree
    build(1, 1, cur_pos);

    // Process queries
    while (q--) {
        int type;
        cin >> type;

        if (type == 1) {
            // Update the value of a node
            int s, x;
            cin >> s >> x;
            update_value(s, x);
        } else if (type == 2) {
            // Find the maximum value on the path between nodes a and b
            int a, b;
            cin >> a >> b;
            cout << query_up(a, b) << " ";
        }
    }

    return 0;
}
// g++ -std=c++17 -O2 -Wall cses_2134.cpp -o a && ./a < a.in