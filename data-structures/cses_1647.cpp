#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

class SegmentTree {
public:
    SegmentTree(const vector<int>& data) {
        n = data.size();
        tree.assign(4 * n, INT_MAX);
        build(data, 0, 0, n - 1);
    }

    int query(int l, int r) {
        return query(0, 0, n - 1, l, r);
    }

private:
    vector<int> tree;
    int n;

    void build(const vector<int>& data, int node, int start, int end) {
        if (start == end) {
            tree[node] = data[start];
        } else {
            int mid = (start + end) / 2;
            build(data, 2 * node + 1, start, mid);
            build(data, 2 * node + 2, mid + 1, end);
            tree[node] = min(tree[2 * node + 1], tree[2 * node + 2]);
        }
    }

    int query(int node, int start, int end, int l, int r) {
        if (r < start || end < l) {
            return INT_MAX;
        }
        if (l <= start && end <= r) {
            return tree[node];
        }
        int mid = (start + end) / 2;
        int left_min = query(2 * node + 1, start, mid, l, r);
        int right_min = query(2 * node + 2, mid + 1, end, l, r);
        return min(left_min, right_min);
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
        int a, b;
        cin >> a >> b;
        // Convert 1-based index to 0-based index
        cout << seg_tree.query(a - 1, b - 1) << endl;
    }

    return 0;
}
