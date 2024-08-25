#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class SegmentTree {
private:
    int n;
    vector<vector<int>> tree;

    // Helper function to merge two vectors into a sorted vector
    vector<int> merge(const vector<int>& a, const vector<int>& b) {
        vector<int> result;
        int i = 0, j = 0;
        while (i < a.size() && j < b.size()) {
            if (a[i] < b[j]) {
                result.push_back(a[i++]);
            } else {
                result.push_back(b[j++]);
            }
        }
        while (i < a.size()) result.push_back(a[i++]);
        while (j < b.size()) result.push_back(b[j++]);
        return result;
    }

    void build(const vector<int>& salaries) {
        for (int i = 0; i < n; ++i) {
            tree[n + i] = {salaries[i]};
        }
        for (int i = n - 1; i > 0; --i) {
            tree[i] = merge(tree[i * 2], tree[i * 2 + 1]);
        }
    }

    int countInRange(const vector<int>& vec, int a, int b) {
        return upper_bound(vec.begin(), vec.end(), b) - lower_bound(vec.begin(), vec.end(), a);
    }

public:
    SegmentTree(const vector<int>& salaries) {
        n = salaries.size();
        tree.resize(2 * n);
        build(salaries);
    }

    void update(int index, int old_value, int new_value) {
        index += n;
        auto it = lower_bound(tree[index].begin(), tree[index].end(), old_value);
        if (it != tree[index].end() && *it == old_value) {
            tree[index].erase(it);
        }
        tree[index].insert(lower_bound(tree[index].begin(), tree[index].end(), new_value), new_value);

        while (index > 1) {
            index /= 2;
            tree[index] = merge(tree[index * 2], tree[index * 2 + 1]);
        }
    }

    int rangeQuery(int left, int right, int a, int b) {
        int res = 0;
        left += n;
        right += n + 1;

        while (left < right) {
            if (left % 2 == 1) res += countInRange(tree[left++], a, b);
            if (right % 2 == 1) res += countInRange(tree[--right], a, b);
            left /= 2;
            right /= 2;
        }
        return res;
    }
};

int main() {
    int n, q;
    cin >> n >> q;
    vector<int> salaries(n);

    for (int i = 0; i < n; ++i) {
        cin >> salaries[i];
    }

    SegmentTree segTree(salaries);

    for (int i = 0; i < q; ++i) {
        char type;
        cin >> type;

        if (type == '!') {
            int k, x;
            cin >> k >> x;
            k--; // Convert to 0-based index
            segTree.update(k, salaries[k], x);
            salaries[k] = x;
        } else if (type == '?') {
            int a, b;
            cin >> a >> b;
            cout << segTree.rangeQuery(0, n - 1, a, b) << endl;
        }
    }

    return 0;
}
// g++ -std=c++17 -o a cses_1144.cpp && ./a < a.in