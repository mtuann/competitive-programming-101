#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct SegmentTree {
    struct Node {
        long long sum, maxPrefixSum, maxSuffixSum, maxSubarraySum;
    };
    
    int n;
    vector<Node> tree;
    
    SegmentTree(int size) {
        n = size;
        tree.resize(4 * n);
    }

    Node combine(Node left, Node right) {
        Node res;
        res.sum = left.sum + right.sum;
        res.maxPrefixSum = max(left.maxPrefixSum, left.sum + right.maxPrefixSum);
        res.maxSuffixSum = max(right.maxSuffixSum, right.sum + left.maxSuffixSum);
        res.maxSubarraySum = max({left.maxSubarraySum, right.maxSubarraySum, left.maxSuffixSum + right.maxPrefixSum});
        return res;
    }

    void build(vector<int>& arr, int v, int tl, int tr) {
        if (tl == tr) {
            tree[v].sum = arr[tl];
            tree[v].maxPrefixSum = max(0LL, (long long)arr[tl]);
            tree[v].maxSuffixSum = max(0LL, (long long)arr[tl]);
            tree[v].maxSubarraySum = max(0LL, (long long)arr[tl]);
        } else {
            int tm = (tl + tr) / 2;
            build(arr, v * 2, tl, tm);
            build(arr, v * 2 + 1, tm + 1, tr);
            tree[v] = combine(tree[v * 2], tree[v * 2 + 1]);
        }
    }

    void update(int v, int tl, int tr, int pos, int new_val) {
        if (tl == tr) {
            tree[v].sum = new_val;
            tree[v].maxPrefixSum = max(0LL, (long long)new_val);
            tree[v].maxSuffixSum = max(0LL, (long long)new_val);
            tree[v].maxSubarraySum = max(0LL, (long long)new_val);
        } else {
            int tm = (tl + tr) / 2;
            if (pos <= tm)
                update(v * 2, tl, tm, pos, new_val);
            else
                update(v * 2 + 1, tm + 1, tr, pos, new_val);
            tree[v] = combine(tree[v * 2], tree[v * 2 + 1]);
        }
    }

    Node query() {
        return tree[1]; // Root of the tree contains the result for the entire array
    }
    
    void update(int pos, int new_val) {
        update(1, 0, n - 1, pos, new_val);
    }

    long long getMaxSubarraySum() {
        return query().maxSubarraySum;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    int n, m;
    cin >> n >> m;
    
    vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }
    
    SegmentTree segTree(n);
    segTree.build(arr, 1, 0, n - 1);

    for (int i = 0; i < m; ++i) {
        int k, x;
        cin >> k >> x;
        segTree.update(k - 1, x);  // Convert 1-based index to 0-based
        cout << segTree.getMaxSubarraySum() << "\n";
    }

    return 0;
}
