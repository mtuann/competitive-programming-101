#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <climits>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<long long> weights(n);
    long long totalSum = 0;
    for (int i = 0; i < n; ++i) {
        cin >> weights[i];
        totalSum += weights[i];
    }

    long long minDifference = LLONG_MAX;

    // Generate all subsets
    int numSubsets = 1 << n; // 2^n subsets
    for (int mask = 0; mask < numSubsets; ++mask) {
        long long subsetSum = 0;
        for (int i = 0; i < n; ++i) {
            if (mask & (1 << i)) {
                subsetSum += weights[i];
            }
        }
        long long remainingSum = totalSum - subsetSum;
        minDifference = min(minDifference, abs(subsetSum - remainingSum));
    }

    cout << minDifference << endl;

    return 0;
}
