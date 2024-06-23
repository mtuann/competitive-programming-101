#include <iostream>
#include <vector>
using namespace std;

class SegmentTree {
private:
    vector<int> tree;
    vector<int> lazy;
    int n;

    void build(vector<int>& arr, int start, int end, int node) {
        if (start == end) {
            tree[node] = arr[start];
        } else {
            int mid = (start + end) / 2;
            build(arr, start, mid, 2 * node + 1);
            build(arr, mid + 1, end, 2 * node + 2);
            tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
        }
    }

    void updateRangeUtil(int start, int end, int l, int r, int delta, int node) {
        if (lazy[node] != 0) {
            tree[node] += (end - start + 1) * lazy[node];
            if (start != end) {
                lazy[2 * node + 1] += lazy[node];
                lazy[2 * node + 2] += lazy[node];
            }
            lazy[node] = 0;
        }

        if (start > end || start > r || end < l)
            return;

        if (start >= l && end <= r) {
            tree[node] += (end - start + 1) * delta;
            if (start != end) {
                lazy[2 * node + 1] += delta;
                lazy[2 * node + 2] += delta;
            }
            return;
        }

        int mid = (start + end) / 2;
        updateRangeUtil(start, mid, l, r, delta, 2 * node + 1);
        updateRangeUtil(mid + 1, end, l, r, delta, 2 * node + 2);
        tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
    }

    int queryRangeUtil(int start, int end, int l, int r, int node) {
        if (lazy[node] != 0) {
            tree[node] += (end - start + 1) * lazy[node];
            if (start != end) {
                lazy[2 * node + 1] += lazy[node];
                lazy[2 * node + 2] += lazy[node];
            }
            lazy[node] = 0;
        }

        if (start > end || start > r || end < l)
            return 0;

        if (start >= l && end <= r)
            return tree[node];

        int mid = (start + end) / 2;
        int leftSum = queryRangeUtil(start, mid, l, r, 2 * node + 1);
        int rightSum = queryRangeUtil(mid + 1, end, l, r, 2 * node + 2);
        return leftSum + rightSum;
    }

public:
    SegmentTree(vector<int>& arr) {
        n = arr.size();
        tree.resize(4 * n);
        lazy.resize(4 * n, 0);
        build(arr, 0, n - 1, 0);
    }

    void updateRange(int l, int r, int delta) {
        updateRangeUtil(0, n - 1, l, r, delta, 0);
    }

    int queryRange(int l, int r) {
        return queryRangeUtil(0, n - 1, l, r, 0);
    }
};

int main() {
    vector<int> arr = {1, 3, 5, 7, 9, 11};
    SegmentTree segTree(arr);

    cout << "Initial sum of values in given range (1, 3): " << segTree.queryRange(1, 3) << endl;

    segTree.updateRange(1, 5, 10);

    cout << "Updated sum of values in given range (1, 3): " << segTree.queryRange(1, 3) << endl;

    return 0;
}
