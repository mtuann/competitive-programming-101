#include <iostream>
#include <vector>
#include <limits>
#include <bitset>

using namespace std;

const int MAX_N = 20; // Maximum number of people
const long long INF = numeric_limits<long long>::max();

long long minRides(vector<int>& weights, int maxWeight) {
    int n = weights.size();
    vector<long long> allSums(1 << n, 0);
    vector<long long> dp(1 << n, INF);
    dp[0] = 0; // Base case: no people, no rides

    // Precompute all possible sums for each subset
    for (int mask = 0; mask < (1 << n); ++mask) {
        long long subsetSum = 0;
        for (int i = 0; i < n; ++i) {
            if (mask & (1 << i)) {
                subsetSum += weights[i];
            }
        }
        if (subsetSum <= maxWeight) {
            allSums[mask] = subsetSum;
        }
    }

    // Dynamic programming to find minimum number of rides
    for (int mask = 0; mask < (1 << n); ++mask) {
        if (dp[mask] < INF) {
            for (int submask = 0; submask < (1 << n); ++submask) {
                if ((mask & submask) == 0 && allSums[submask] > 0) {
                    // Skip if submask sum exceeds maximum weight
                    if (allSums[submask] <= maxWeight) {
                        dp[mask | submask] = min(dp[mask | submask], dp[mask] + 1);
                    }
                }
            }
        }
    }

    return dp[(1 << n) - 1];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    long long x;
    cin >> n >> x;

    vector<int> weights(n);
    for (int i = 0; i < n; ++i) {
        cin >> weights[i];
    }

    cout << minRides(weights, x) << endl;

    return 0;
}


// #include <iostream>
// #include <vector>
// #include <limits>
// #include <bitset>

// using namespace std;

// const int MAX_N = 20; // Maximum number of people
// const long long INF = numeric_limits<long long>::max();

// long long minRides(vector<int>& weights, int maxWeight) {
//     int n = weights.size();
//     vector<long long> allSums(1 << n, 0);
//     vector<long long> dp(1 << n, INF);
//     dp[0] = 0; // Base case: no people, no rides

//     // Precompute all possible sums for each subset
//     for (int mask = 0; mask < (1 << n); ++mask) {
//         long long subsetSum = 0;
//         for (int i = 0; i < n; ++i) {
//             if (mask & (1 << i)) {
//                 subsetSum += weights[i];
//             }
//         }
//         if (subsetSum <= maxWeight) {
//             allSums[mask] = subsetSum;
//         }
//     }

//     // Dynamic programming to find minimum number of rides
//     for (int mask = 0; mask < (1 << n); ++mask) {
//         if (dp[mask] < INF) {
//             for (int submask = 0; submask < (1 << n); ++submask) {
//                 if ((mask & submask) == 0 && allSums[submask] > 0) {
//                     dp[mask | submask] = min(dp[mask | submask], dp[mask] + 1);
//                 }
//             }
//         }
//     }

//     return dp[(1 << n) - 1];
// }

// int main() {
//     ios::sync_with_stdio(false);
//     cin.tie(nullptr);

//     int n;
//     long long x;
//     cin >> n >> x;

//     vector<int> weights(n);
//     for (int i = 0; i < n; ++i) {
//         cin >> weights[i];
//     }

//     cout << minRides(weights, x) << endl;

//     return 0;
// }
