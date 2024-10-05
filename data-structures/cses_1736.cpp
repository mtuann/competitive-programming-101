#include <bits/stdc++.h>
using namespace std;

class FenwickTree {
public:
    FenwickTree(int size) : size(size) {
        tree.resize(size + 1, 0); // 1-indexed Fenwick Tree
    }

    void add(int index, long long value) {
        while (index <= size) {
            tree[index] += value;
            index += index & -index;
        }
    }

    long long sum(int index) {
        long long total = 0;
        while (index > 0) {
            total += tree[index];
            index -= index & -index;
        }
        return total;
    }

    long long range_sum(int left, int right) {
        return sum(right) - sum(left - 1);
    }

private:
    int size;
    vector<long long> tree;
};

void process_queries(int n, int q, vector<long long>& array, vector<tuple<int, int, int>>& queries) {
    FenwickTree fenwick(n);

    // Initialize the Fenwick Tree with the original values
    for (int i = 1; i <= n; ++i) {
        fenwick.add(i, array[i - 1]); // 1-indexed
    }

    for (const auto& query : queries) {
        int type = get<0>(query);
        int a = get<1>(query);
        int b = get<2>(query);

        if (type == 1) {  // Increase operation
            // Increment the first element by 1, second by 2, ..., up to (b-a+1)
            fenwick.add(a, 1); // Start adding from index a
            if (b + 1 <= n) {
                fenwick.add(b + 1, -(b - a + 2)); // To cancel out increment at b+1
            }
            if (b + 2 <= n) {
                fenwick.add(b + 2, (b - a + 2)); // Reset next value
            }
        } else if (type == 2) {  // Sum query
            long long total_sum = fenwick.range_sum(a, b);
            // Add the extra increments caused by the series increment
            long long extra_sum = (b - a + 1) * (b - a + 2) / 2; // Sum of 1 to (b-a+1)
            cout << (total_sum + extra_sum) << "\n";
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    vector<long long> array(n);

    for (int i = 0; i < n; ++i) {
        cin >> array[i];
    }

    vector<tuple<int, int, int>> queries;

    for (int i = 0; i < q; ++i) {
        int type, a, b;
        cin >> type >> a >> b;
        queries.emplace_back(type, a, b);
    }

    process_queries(n, q, array, queries);

    return 0;
}
