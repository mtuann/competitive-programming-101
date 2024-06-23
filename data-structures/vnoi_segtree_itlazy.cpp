#include <iostream>
#include <vector>
using namespace std;

const int MAXN = 1e5 + 10;
const long long INF = 1e18 + 19;
int n;

int arr[MAXN];
long long tree[4 * MAXN], lazy[4 * MAXN];

void build(int start, int end, int node) {
    if (start == end) {
        tree[node] = (long long)arr[start];
        return;
    }
    int mid = (start + end) / 2;
    build(start, mid, 2 * node);
    build(mid + 1, end, 2 * node + 1);
    tree[node] = max(tree[2 * node], tree[2 * node + 1]);
}

void fix(int node, int start, int end) {
    if (lazy[node] != 0) {
        tree[node] += lazy[node];
        if (start != end) {
            lazy[2 * node] += lazy[node];
            lazy[2 * node + 1] += lazy[node];
        }
        lazy[node] = 0;
    }
}

void updateRange(int node, int start, int end, int l, int r, int val) {
    fix(node, start, end);

    if (start > end || start > r || end < l)
        return;
    if (start >= l && end <= r) {
        lazy[node] += val;
        fix(node, start, end);
        return;
    }
    int mid = (start + end) / 2;
    updateRange(2 * node, start, mid, l, r, val);
    updateRange(2 * node + 1, mid + 1, end, l, r, val);
    tree[node] = max(tree[2 * node], tree[2 * node + 1]);
}


long long queryRangeUtil(int start, int end, int l, int r, int node) {
    fix(node, start, end);
    // if (start > end || start > r || end < l)
    if (start > r || end < l)
        return -INF;

    if (start >= l && end <= r)
        return tree[node];

    int mid = (start + end) / 2;
    long long leftMax = queryRangeUtil(start, mid, l, r, 2 * node);
    long long rightMax = queryRangeUtil(mid + 1, end, l, r, 2 * node + 1);
    return max(leftMax, rightMax);
}


int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    build(0, n - 1, 1);
    int q;
    cin >> q;
    while (q--) {
        int type;
        cin >> type;
       if (type == 1) {
            int x, y, val;
            cin >> x >> y >> val;
            x -= 1;
            y -= 1;
            updateRange(1, 0, n - 1, x, y, val);
       } else {
            int l, r;
            cin >> l >> r;
            l -= 1;
            r -= 1;
            cout << queryRangeUtil(0, n - 1, l, r, 1) << "\n";
        }
    }

    return 0;
}

// g++ -std=c++17 -o a vnoi_segtree_itlazy.cpp && ./a < a.in