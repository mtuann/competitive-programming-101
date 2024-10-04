#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct SegmentTree {
    int n;
    struct Node {
        long long sum, maxPrefixSum;
    };
    vector<Node> tree;
    
    SegmentTree(int size) {
        n = size;
        tree.resize(4 * n);
    }

    // Combine two nodes
    Node combine(Node left, Node right) {
        Node res;
        res.sum = left.sum + right.sum;
        res.maxPrefixSum = max(left.maxPrefixSum, left.sum + right.maxPrefixSum);
        return res;
    }

    // Build the segment tree
    void build(vector<int>& arr, int v, int tl, int tr) {
        if (tl == tr) {
            tree[v].sum = arr[tl];
            tree[v].maxPrefixSum = max(0LL, (long long)arr[tl]);
        } else {
            int tm = (tl + tr) / 2;
            build(arr, v * 2, tl, tm);
            build(arr, v * 2 + 1, tm + 1, tr);
            tree[v] = combine(tree[v * 2], tree[v * 2 + 1]);
        }
    }

    // Update a value in the array
    void update(int v, int tl, int tr, int pos, int new_val) {
        if (tl == tr) {
            tree[v].sum = new_val;
            tree[v].maxPrefixSum = max(0LL, (long long)new_val);
        } else {
            int tm = (tl + tr) / 2;
            if (pos <= tm)
                update(v * 2, tl, tm, pos, new_val);
            else
                update(v * 2 + 1, tm + 1, tr, pos, new_val);
            tree[v] = combine(tree[v * 2], tree[v * 2 + 1]);
        }
    }

    // Query the maximum prefix sum in the range [l, r]
    Node query(int v, int tl, int tr, int l, int r) {
        if (l > r) return {0, 0};
        if (l == tl && r == tr) {
            return tree[v];
        }
        int tm = (tl + tr) / 2;
        Node left_part = query(v * 2, tl, tm, l, min(r, tm));
        Node right_part = query(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r);
        return combine(left_part, right_part);
    }
    
    void update(int pos, int new_val) {
        update(1, 0, n - 1, pos, new_val);
    }

    long long getMaxPrefixSum(int l, int r) {
        return query(1, 0, n - 1, l, r).maxPrefixSum;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    int n, q;
    cin >> n >> q;
    
    vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }
    
    SegmentTree segTree(n);
    segTree.build(arr, 1, 0, n - 1);

    for (int i = 0; i < q; ++i) {
        int type;
        cin >> type;
        if (type == 1) {
            int k, u;
            cin >> k >> u;
            segTree.update(k - 1, u);  // Convert 1-based index to 0-based
        } else if (type == 2) {
            int a, b;
            cin >> a >> b;
            cout << segTree.getMaxPrefixSum(a - 1, b - 1) << "\n";  // Convert 1-based to 0-based
        }
    }

    return 0;
}
