#include <iostream>
#include <vector>

using namespace std;

class SegmentTree {
public:
    SegmentTree(const vector<long long>& data) {
        n = data.size();
        tree.assign(4 * n, 0);
        lazy.assign(4 * n, 0);
        build(data, 0, 0, n - 1);
    }

    void update(int l, int r, int value) {
        update(0, 0, n - 1, l, r, value);
    }

    long long query(int idx) {
        return query(0, 0, n - 1, idx);
    }

private:
    vector<long long> tree;
    vector<long long> lazy;
    int n;

    void build(const vector<long long>& data, int node, int start, int end) {
        if (start == end) {
            tree[node] = data[start];
        } else {
            int mid = (start + end) / 2;
            build(data, 2 * node + 1, start, mid);
            build(data, 2 * node + 2, mid + 1, end);
            tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
        }
    }

    void propagate(int node, int start, int end) {
        if (lazy[node] != 0) {
            tree[node] += (end - start + 1) * lazy[node];
            if (start != end) {
                lazy[2 * node + 1] += lazy[node];
                lazy[2 * node + 2] += lazy[node];
            }
            lazy[node] = 0;
        }
    }

    void update(int node, int start, int end, int l, int r, int value) {
        propagate(node, start, end);

        if (r < start || end < l) {
            return;
        }

        if (l <= start && end <= r) {
            tree[node] += 1ll*(end - start + 1) * value;
            if (start != end) {
                lazy[2 * node + 1] += value;
                lazy[2 * node + 2] += value;
            }
            return;
        }

        int mid = (start + end) / 2;
        update(node * 2 + 1, start, mid, l, r, value);
        update(node * 2 + 2, mid + 1, end, l, r, value);
        tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
    }

    long long query(int node, int start, int end, int idx) {
        propagate(node, start, end);

        if (start == end) {
            return tree[node];
        }

        int mid = (start + end) / 2;
        if (idx <= mid) {
            return query(node * 2 + 1, start, mid, idx);
        } else {
            return query(node * 2 + 2, mid + 1, end, idx);
        }
    }
};

int main() {
    int n, q;
    cin >> n >> q;

    vector<long long> data(n);
    for (int i = 0; i < n; ++i) {
        cin >> data[i];
    }

    SegmentTree seg_tree(data);

    while (q--) {
        int type, x, y, u;
        cin >> type >> x;
        if (type == 1) {
            // Update operation
            cin >> y >> u;
            seg_tree.update(x - 1, y - 1, u);
        } else if (type == 2) {
            // Point query
            cout << seg_tree.query(x - 1) << endl;
        }
    }

    return 0;
}
// g++ -std=c++14 -o a cses_1651.cpp && ./a < a.in

