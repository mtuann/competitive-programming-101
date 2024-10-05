#include <iostream>
#include <vector>

using namespace std;

struct SegmentTree {
    int n;
    vector<long long> tree, lazySet, lazyAdd;
    vector<bool> lazySetFlag;

    SegmentTree(int size) : n(size), tree(4 * size, 0), lazySet(4 * size, 0), lazyAdd(4 * size, 0), lazySetFlag(4 * size, false) {}

    // Apply pending updates before processing current node
    void push(int node, int start, int end) {
        if (lazySetFlag[node]) {
            // Set all elements in range to lazySet[node]
            tree[node] = lazySet[node] * (end - start + 1);
            if (start != end) {
                lazySet[2 * node] = lazySet[node];
                lazySet[2 * node + 1] = lazySet[node];
                lazyAdd[2 * node] = 0;
                lazyAdd[2 * node + 1] = 0;
                lazySetFlag[2 * node] = true;
                lazySetFlag[2 * node + 1] = true;
            }
            lazySetFlag[node] = false;
        }
        if (lazyAdd[node] != 0) {
            tree[node] += lazyAdd[node] * (end - start + 1);
            if (start != end) {
                lazyAdd[2 * node] += lazyAdd[node];
                lazyAdd[2 * node + 1] += lazyAdd[node];
            }
            lazyAdd[node] = 0;
        }
    }

    // Update range [l, r] by adding 'val' (increment operation)
    void updateAdd(int node, int start, int end, int l, int r, long long val) {
        push(node, start, end);
        if (start > r || end < l) return;  // Out of range
        if (start >= l && end <= r) {  // Fully in range
            lazyAdd[node] += val;
            push(node, start, end);
            return;
        }
        int mid = (start + end) / 2;
        updateAdd(2 * node, start, mid, l, r, val);
        updateAdd(2 * node + 1, mid + 1, end, l, r, val);
        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }

    // Update range [l, r] to 'val' (set operation)
    void updateSet(int node, int start, int end, int l, int r, long long val) {
        push(node, start, end);
        if (start > r || end < l) return;  // Out of range
        if (start >= l && end <= r) {  // Fully in range
            lazySet[node] = val;
            lazySetFlag[node] = true;
            lazyAdd[node] = 0;
            push(node, start, end);
            return;
        }
        int mid = (start + end) / 2;
        updateSet(2 * node, start, mid, l, r, val);
        updateSet(2 * node + 1, mid + 1, end, l, r, val);
        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }

    // Query the sum of range [l, r]
    long long query(int node, int start, int end, int l, int r) {
        push(node, start, end);
        if (start > r || end < l) return 0;  // Out of range
        if (start >= l && end <= r) {  // Fully in range
            return tree[node];
        }
        int mid = (start + end) / 2;
        return query(2 * node, start, mid, l, r) + query(2 * node + 1, mid + 1, end, l, r);
    }

    // Public interfaces for queries and updates
    void updateAdd(int l, int r, long long val) {
        updateAdd(1, 0, n - 1, l, r, val);
    }

    void updateSet(int l, int r, long long val) {
        updateSet(1, 0, n - 1, l, r, val);
    }

    long long query(int l, int r) {
        return query(1, 0, n - 1, l, r);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }

    SegmentTree segTree(n);

    // Initialize segment tree with the initial values
    for (int i = 0; i < n; ++i) {
        segTree.updateSet(i, i, arr[i]);
    }

    // Process queries
    while (q--) {
        int type, a, b;
        cin >> type >> a >> b;
        --a, --b;  // Convert to 0-based indexing

        if (type == 1) {
            long long x;
            cin >> x;
            segTree.updateAdd(a, b, x);
        } else if (type == 2) {
            long long x;
            cin >> x;
            segTree.updateSet(a, b, x);
        } else if (type == 3) {
            cout << segTree.query(a, b) << "\n";
        }
    }

    return 0;
}
