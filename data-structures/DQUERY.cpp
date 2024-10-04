#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

struct Query {
    int l, r, idx;
};

int block_size;
vector<int> result;
vector<int> freq(1000001, 0);  // Frequency array to store the count of each element
int distinct_count = 0;  // Number of distinct elements in the current range

bool compare(Query& a, Query& b) {
    int block_a = a.l / block_size;
    int block_b = b.l / block_size;
    if (block_a != block_b)
        return block_a < block_b;
    return a.r < b.r;
}

void add(int x, const vector<int>& arr) {
    freq[arr[x]]++;
    if (freq[arr[x]] == 1) {
        distinct_count++;
    }
}

void remove(int x, const vector<int>& arr) {
    freq[arr[x]]--;
    if (freq[arr[x]] == 0) {
        distinct_count--;
    }
}

int main() {
    int n, q;
    cin >> n;

    vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }

    cin >> q;
    vector<Query> queries(q);
    result.resize(q);

    for (int i = 0; i < q; ++i) {
        cin >> queries[i].l >> queries[i].r;
        queries[i].l--;  // 1-based to 0-based indexing
        queries[i].r--;
        queries[i].idx = i;  // Store the index of the query to output answers in the correct order
    }

    block_size = sqrt(n);
    sort(queries.begin(), queries.end(), compare);

    int current_l = 0, current_r = -1;

    for (int i = 0; i < q; ++i) {
        int l = queries[i].l;
        int r = queries[i].r;

        // Move the right pointer to the correct position
        while (current_r < r) {
            current_r++;
            add(current_r, arr);
        }
        while (current_r > r) {
            remove(current_r, arr);
            current_r--;
        }

        // Move the left pointer to the correct position
        while (current_l < l) {
            remove(current_l, arr);
            current_l++;
        }
        while (current_l > l) {
            current_l--;
            add(current_l, arr);
        }

        // Store the result for this query
        result[queries[i].idx] = distinct_count;
    }

    // Output all results
    for (int i = 0; i < q; ++i) {
        cout << result[i] << endl;
    }

    return 0;
}

// g++ -std=c++11 -O2 -Wall DQUERY.cpp -o a && ./a < a.in
