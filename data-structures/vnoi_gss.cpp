#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
const int INF = 1e9 + 7;
const int MAXN = 5e4 + 10;
int n;

struct Node {
    int pre, suf, sum, maxsum;

     Node(int pre = -INF, int suf = -INF, int sum = 0, int maxsum = -INF) : pre(pre), suf(suf), sum(sum), maxsum(maxsum) {}

    static Node merge(Node& a, Node& b) {
        return Node(
            max(a.pre, a.sum + b.pre),
            max(b.suf, b.sum + a.suf),
            a.sum + b.sum,
            // max({a.maxsum, b.maxsum, a.suf + b.pre})
            max(max(a.maxsum, b.maxsum), a.suf + b.pre)
        );
    }
};

Node tree[4 * MAXN];
int arr[MAXN];

void build(int root, int start, int end) {
    if (start == end) {
        tree[root] = Node(arr[start], arr[start], arr[start], arr[start]);
        return;
    }
    int mid = (start + end) / 2;
    build(2 * root, start, mid);
    build(2 * root + 1, mid + 1, end);
    tree[root] = Node::merge(tree[2 * root], tree[2 * root + 1]);
}



Node queryRangeUtil(int start, int end, int l, int r, int node) {
    if (start > r || end < l) {
        return Node();
    }

    if (start >= l && end <= r) {
        return tree[node];
    }

    int mid = (start + end) / 2;
    Node left = queryRangeUtil(start, mid, l, r, 2 * node);
    Node right = queryRangeUtil(mid + 1, end, l, r, 2 * node + 1);
    return Node::merge(left, right);

}


int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    build(1, 0, n - 1);
    int q;
    cin >> q;
    while (q--) {
        int u, v;
        cin >> u >> v;
        cout << queryRangeUtil(0, n - 1, u - 1, v - 1, 1).maxsum << '\n';
    }

    return 0;
}

// g++ -std=c++17 -o a vnoi_gss.cpp && ./a < a.in