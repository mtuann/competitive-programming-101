#include <iostream>
#include <vector>
using namespace std;
const int INF = 1e9;
const int MAXN = 1e5 + 10;
int n;

int arr[MAXN];
int tree[4 * MAXN];

void build(int start, int end, int node) {
    if (start == end) {
        tree[node] = arr[start];
        return;
    }
    int mid = (start + end) / 2;
    build(start, mid, 2 * node);
    build(mid + 1, end, 2 * node + 1);
    tree[node] = max(tree[2 * node], tree[2 * node + 1]);
}

void updatePoint(int start, int end, int idx, int val, int node) {
    if (start == end) {
        arr[idx] = val;
        tree[node] = val;
        return;
    }
    int mid = (start + end) / 2;
    if (start <= idx && idx <= mid) {
        updatePoint(start, mid, idx, val, 2 * node);
    } else {
        updatePoint(mid + 1, end, idx, val, 2 * node + 1);
    }
    tree[node] = max(tree[2 * node], tree[2 * node + 1]);
}


int queryRangeUtil(int start, int end, int l, int r, int node) {
    
    // if (start > end || start > r || end < l)
    if (start > r || end < l)
        return -INF;

    if (start >= l && end <= r)
        return tree[node];

    int mid = (start + end) / 2;
    int leftMax = queryRangeUtil(start, mid, l, r, 2 * node);
    int rightMax = queryRangeUtil(mid + 1, end, l, r, 2 * node + 1);
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
        if (type == 2) {
            int l, r;
            cin >> l >> r;
            l -= 1;
            r -= 1;
            cout << queryRangeUtil(0, n - 1, l, r, 1) << "\n";
        } else {
            int idx, val;
            cin >> idx >> val;
            idx -= 1;
            updatePoint(0, n - 1, idx, val, 1);
        }
    }


    return 0;
}

// g++ -std=c++17 -o a vnoi_segtree_itez1.cpp && ./a < a.in