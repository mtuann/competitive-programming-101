#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int INF = 1e9+7;

class SegmentTree {
    vector<int> tree;
    int size;

public:
    SegmentTree(int n) {
        size = n;
        tree.resize(2 * n, -1);
    }

    void build(const vector<int>& arr) {
        for (int i = 0; i < size; ++i) {
            tree[size + i] = arr[i];
        }
        for (int i = size - 1; i > 0; --i) {
            tree[i] = max(tree[2 * i], tree[2 * i + 1]);
        }
    }

    void update(int pos, int value) {
        pos += size;
        tree[pos] = value;
        while (pos > 1) {
            pos /= 2;
            tree[pos] = max(tree[2 * pos], tree[2 * pos + 1]);
        }
    }

    int query(int l, int r, int x) {
        l += size;
        r += size;
        while (l <= r) {
            if (l % 2 == 1 && tree[l] >= x) return l - size;
            if (r % 2 == 0 && tree[r] >= x) return r - size;
            l = (l + 1) / 2;
            r = (r - 1) / 2;
        }
        return -1;
    }
};

int main() {
    int n, m;
    cin >> n >> m;

    vector<int> hotels(n);
    for (int i = 0; i < n; ++i) {
        cin >> hotels[i];
    }

    SegmentTree segTree(n);
    segTree.build(hotels);

    for (int i = 0; i < m; ++i) {
        int rooms_needed;
        cin >> rooms_needed;

        int index = segTree.query(0, n - 1, rooms_needed);
        if (index != -1) {
            cout << index + 1 << " ";
            hotels[index] -= rooms_needed;
            segTree.update(index, hotels[index]);
        } else {
            cout << 0 << " ";
        }
    }
    cout << endl;

    return 0;
}

// g++ -std=c++17 -o a cses_1143.cpp && ./a < a.in