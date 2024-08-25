#include <iostream>
#include <vector>

using namespace std;

class SegmentTree {
public:
    SegmentTree(const vector<int>& data) {
        n = data.size();
        tree.assign(4 * n, 0);
        build(data, 0, 0, n - 1);
    }

    void update(int idx, int value) {
        update(0, 0, n - 1, idx, value);
    }

    long long query(int l, int r) {
        return query(0, 0, n - 1, l, r);
    }

private:
    vector<long long> tree;
    int n;

    void build(const vector<int>& data, int node, int start, int end) {
        if (start == end) {
            tree[node] = data[start];
        } else {
            int mid = (start + end) / 2;
            build(data, 2 * node + 1, start, mid);
            build(data, 2 * node + 2, mid + 1, end);
            tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
        }
    }

    void update(int node, int start, int end, int idx, int value) {
        if (start == end) {
            tree[node] = value;
        } else {
            int mid = (start + end) / 2;
            if (start <= idx && idx <= mid) {
                update(node * 2 + 1, start, mid, idx, value);
            } else {
                update(node * 2 + 2, mid + 1, end, idx, value);
            }
            tree[node] = tree[node * 2 + 1] + tree[node * 2 + 2];
        }
    }

    long long query(int node, int start, int end, int l, int r) {
        if (r < start || end < l) {
            return 0; // Out of range
        }
        if (l <= start && end <= r) {
            return tree[node];
        }
        int mid = (start + end) / 2;
        long long left_sum = query(node * 2 + 1, start, mid, l, r);
        long long right_sum = query(node * 2 + 2, mid + 1, end, l, r);
        return left_sum + right_sum;
    }
};

int main() {
    int n, q;
    cin >> n >> q;

    vector<int> data(n);
    for (int i = 0; i < n; ++i) {
        cin >> data[i];
    }

    SegmentTree seg_tree(data);

    while (q--) {
        int type, x, y;
        cin >> type >> x >> y;
        if (type == 1) {
            // Update operation
            seg_tree.update(x - 1, y);
        } else if (type == 2) {
            // Range sum query
            cout << seg_tree.query(x - 1, y - 1) << endl;
        }
    }

    return 0;
}
