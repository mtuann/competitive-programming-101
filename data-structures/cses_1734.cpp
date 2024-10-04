#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>
using namespace std;

struct Query {
    int l, r, idx;
};

int BLOCK_SIZE;
vector<int> answer;

void add(int x, int &distinct_count, map<int, int> &freq) {
    if (freq[x] == 0) distinct_count++;
    freq[x]++;
}

void remove(int x, int &distinct_count, map<int, int> &freq) {
    if (freq[x] == 1) distinct_count--;
    freq[x]--;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, q;
    cin >> n >> q;

    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    BLOCK_SIZE = sqrt(n);
    vector<Query> queries(q);
    answer.resize(q);

    for (int i = 0; i < q; i++) {
        int a, b;
        cin >> a >> b;
        queries[i] = {a - 1, b - 1, i};  // convert to 0-based indexing
    }

    // Sort the queries
    sort(queries.begin(), queries.end(), [](Query &a, Query &b) {
        int block_a = a.l / BLOCK_SIZE;
        int block_b = b.l / BLOCK_SIZE;
        if (block_a != block_b)
            return block_a < block_b;
        return (block_a % 2 == 0) ? (a.r < b.r) : (a.r > b.r);  // optimize the second comparison
    });

    int current_l = 0, current_r = -1;
    int distinct_count = 0;
    map<int, int> freq;

    for (Query query : queries) {
        int l = query.l;
        int r = query.r;

        // Move right pointer to r
        while (current_r < r) {
            current_r++;
            add(arr[current_r], distinct_count, freq);
        }
        while (current_r > r) {
            remove(arr[current_r], distinct_count, freq);
            current_r--;
        }

        // Move left pointer to l
        while (current_l < l) {
            remove(arr[current_l], distinct_count, freq);
            current_l++;
        }
        while (current_l > l) {
            current_l--;
            add(arr[current_l], distinct_count, freq);
        }

        // Store the result for this query
        answer[query.idx] = distinct_count;
    }

    // Output all answers
    for (int i = 0; i < q; i++) {
        cout << answer[i] << "\n";
    }

    return 0;
}
