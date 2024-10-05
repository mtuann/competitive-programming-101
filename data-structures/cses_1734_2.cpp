#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

struct Query {
    int l, r, idx;
};

class FenwickTree {
public:
    vector<int> bit;
    int n;

    FenwickTree(int size) : n(size), bit(size + 1, 0) {}

    void update(int index, int delta) {
        while (index <= n) {
            bit[index] += delta;
            index += index & -index;
        }
    }

    int query(int index) {
        int sum = 0;
        while (index > 0) {
            sum += bit[index];
            index -= index & -index;
        }
        return sum;
    }

    int rangeQuery(int l, int r) {
        return query(r) - query(l - 1);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, q;
    cin >> n >> q;

    vector<int> arr(n + 1);
    map<int, int> last_occurrence;
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }

    vector<Query> queries(q);
    vector<int> result(q);

    for (int i = 0; i < q; i++) {
        int a, b;
        cin >> a >> b;
        queries[i] = {a, b, i};  // 1-based indexing
    }

    // Sort the queries by the right endpoint
    sort(queries.begin(), queries.end(), [](Query &a, Query &b) {
        return a.r < b.r;
    });

    FenwickTree fenwick(n);
    int current_r = 0;

    // Process the queries in sorted order
    for (Query query : queries) {
        while (current_r < query.r) {
            current_r++;
            int value = arr[current_r];
            // Remove the last occurrence of the current value
            if (last_occurrence[value] != 0) {
                fenwick.update(last_occurrence[value], -1);
            }
            // Add the current occurrence
            last_occurrence[value] = current_r;
            fenwick.update(current_r, 1);
        }

        // Answer the current query
        result[query.idx] = fenwick.rangeQuery(query.l, query.r);
    }

    // Output all results
    for (int i = 0; i < q; i++) {
        cout << result[i] << "\n";
    }

    return 0;
}
