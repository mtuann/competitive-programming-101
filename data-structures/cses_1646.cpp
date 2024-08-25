#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n, q;
    cin >> n >> q;

    vector<int> arr(n + 1, 0);
    vector<long long> prefix_sum(n + 1, 0);

    // Reading the array
    for (int i = 1; i <= n; ++i) {
        cin >> arr[i];
    }

    // Compute prefix sums
    for (int i = 1; i <= n; ++i) {
        prefix_sum[i] = prefix_sum[i - 1] + arr[i];
    }

    // Process each query
    while (q--) {
        int a, b;
        cin >> a >> b;
        // Answer the query using the prefix sums array
        cout << prefix_sum[b] - prefix_sum[a - 1] << endl;
    }

    return 0;
}
