#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, q;
    cin >> n >> q;

    vector<int> arr(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }

    // Difference array to calculate how much each element violates the increasing order
    vector<long long> operations(n + 1, 0);

    // Precompute the required operations for each pair of adjacent elements
    for (int i = 2; i <= n; i++) {
        if (arr[i] < arr[i - 1]) {
            operations[i] = arr[i - 1] - arr[i];
        }
    }

    // Build a prefix sum array for the operations array
    vector<long long> prefix_sum(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        prefix_sum[i] = prefix_sum[i - 1] + operations[i];
    }

    // Process queries
    while (q--) {
        int a, b;
        cin >> a >> b;
        // The number of operations needed to make the subarray [a, b] increasing
        cout << prefix_sum[b] - prefix_sum[a] << "\n";
    }

    return 0;
}
