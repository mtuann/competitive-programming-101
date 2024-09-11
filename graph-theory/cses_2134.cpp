#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 200005;
int n, q;
int values[MAXN];
vector<int> adj[MAXN];
int parent[MAXN], depth[MAXN], heavy[MAXN], head[MAXN], pos[MAXN];
int cur_pos = 0;
int segTree[4*MAXN];

int dfs(int v) {
    int size = 1;
    int max_c_size = 0;
    for (int c : adj[v]) {
        if (c == parent[v]) continue;
        parent[c] = v;
        depth[c] = depth[v] + 1;
        int c_size = dfs(c);
        size += c_size;
        if (c_size > max_c_size) {
            max_c_size = c_size;
            heavy[v] = c;
        }
    }
    return size;
}

void decompose(int v, int h) {
    head[v] = h;
    pos[v] = cur_pos++;
    if (heavy[v] != -1)
        decompose(heavy[v], h);
    for (int c : adj[v]) {
        if (c != parent[v] && c != heavy[v])
            decompose(c, c);
    }
}

void buildSegTree(int v, int tl, int tr) {
    if (tl == tr) {
        segTree[v] = values[pos[tl]];
    } else {
        int tm = (tl + tr) / 2;
        buildSegTree(2*v, tl, tm);
        buildSegTree(2*v+1, tm+1, tr);
        segTree[v] = max(segTree[2*v], segTree[2*v+1]);
    }
}

void updateSegTree(int v, int tl, int tr, int pos, int new_val) {
    if (tl == tr) {
        segTree[v] = new_val;
    } else {
        int tm = (tl + tr) / 2;
        if (pos <= tm)
            updateSegTree(2*v, tl, tm, pos, new_val);
        else
            updateSegTree(2*v+1, tm+1, tr, pos, new_val);
        segTree[v] = max(segTree[2*v], segTree[2*v+1]);
    }
}

int querySegTree(int v, int tl, int tr, int l, int r) {
    if (l > r) 
        return -1;
    if (l == tl && r == tr) {
        return segTree[v];
    }
    int tm = (tl + tr) / 2;
    return max(querySegTree(2*v, tl, tm, l, min(r, tm)),
               querySegTree(2*v+1, tm+1, tr, max(l, tm+1), r));
}

int query(int a, int b) {
    int res = -1;
    while (head[a] != head[b]) {
        if (depth[head[a]] > depth[head[b]])
            swap(a, b);
        res = max(res, querySegTree(1, 0, n-1, pos[head[b]], pos[b]));
        b = parent[head[b]];
    }
    if (depth[a] > depth[b])
        swap(a, b);
    res = max(res, querySegTree(1, 0, n-1, pos[a], pos[b]));
    return res;
}

void change(int s, int x) {
    updateSegTree(1, 0, n-1, pos[s], x);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    cin >> n >> q;
    for (int i = 1; i <= n; ++i) {
        cin >> values[i];
    }
    
    for (int i = 0; i < n-1; ++i) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    
    fill(heavy, heavy + n + 1, -1);
    
    dfs(1);
    decompose(1, 1);
    
    buildSegTree(1, 0, n-1);
    
    while (q--) {
        int type, a, b;
        cin >> type >> a >> b;
        if (type == 1) {
            change(a, b);
        } else {
            cout << query(a, b) << "\n";
        }
    }
    
    return 0;
}
