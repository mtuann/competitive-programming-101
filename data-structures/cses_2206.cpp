#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

struct SegmentTree {
    int n;
    vector<long long> tree;

    SegmentTree(int size) {
        n = size;
        tree.assign(4 * n, LLONG_MAX);
    }

    void update(int v, int tl, int tr, int pos, long long new_val) {
        if (tl == tr) {
            tree[v] = new_val;
        } else {
            int tm = (tl + tr) / 2;
            if (pos <= tm)
                update(v * 2, tl, tm, pos, new_val);
            else
                update(v * 2 + 1, tm + 1, tr, pos, new_val);
            tree[v] = min(tree[v * 2], tree[v * 2 + 1]);
        }
    }

    long long query(int v, int tl, int tr, int l, int r) {
        if (l > r) return LLONG_MAX;
        if (l == tl && r == tr) {
            return tree[v];
        }
        int tm = (tl + tr) / 2;
        return min(query(v * 2, tl, tm, l, min(r, tm)),
                   query(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r));
    }

    void update(int pos, long long new_val) {
        update(1, 0, n - 1, pos, new_val);
    }

    long long query(int l, int r) {
        return query(1, 0, n - 1, l, r);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, q;
    cin >> n >> q;

    vector<int> p(n);
    for (int i = 0; i < n; ++i) {
        cin >> p[i];
    }

    // Segment Trees for p_i - i and p_i + i
    SegmentTree st1(n), st2(n);
    for (int i = 0; i < n; ++i) {
        st1.update(i, p[i] - i);
        st2.update(i, p[i] + i);
    }

    while (q--) {
        int type, k;
        cin >> type >> k;
        if (type == 1) {
            // Update the price of pizza in building k
            int x;
            cin >> x;
            --k; // Convert 1-based index to 0-based
            st1.update(k, x - k);
            st2.update(k, x + k);
        } else {
            // Query the minimum price for building k
            --k; // Convert 1-based index to 0-based
            long long res = min(st1.query(0, k) + k, st2.query(k, n - 1) - k);
            cout << res << "\n";
        }
    }

    return 0;
}
