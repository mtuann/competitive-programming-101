#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 20;
int dp[1 << MAXN];
int backtrack[1 << MAXN];
int value[MAXN][MAXN];

int main() {
    freopen("dance.inp", "r", stdin);
    freopen("dance.out", "w", stdout);
    int N, M;
    cin >> N >> M;

    // Ensure that N ≤ M
    // if (N > M) {
    //     cout << "Error: N should be less than or equal to M." << endl;
    //     return 1;
    // }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> value[i][j]; // Input the value of matching male i with female j
        }
    }

    // Iterate over all masks
    for (int mask = 0; mask < (1 << M); mask++) {
        int i = __builtin_popcount(mask); // Number of males matched so far

        if (i >= N) continue; // We only match exactly N males

        for (int j = 0; j < M; j++) {
            if (!(mask & (1 << j))) { // If female j is not matched
                int new_mask = mask | (1 << j);
                if (dp[new_mask] < dp[mask] + value[i][j]) {
                    dp[new_mask] = dp[mask] + value[i][j];
                    backtrack[new_mask] = j; // Store the index of female j
                }
            }
        }
        // cout << "Mask: " << mask << " DP: " << dp[mask] << endl;
    }

    // The final answer is the maximum value for the mask where exactly N females are selected
    // int full_mask = (1 << M) - 1;
    int best_value = 0, best_mask = 0;
    for (int mask = 0; mask < (1 << M); mask++) {
        if (__builtin_popcount(mask) == N) {
            if (dp[mask] > best_value) {
                best_value = dp[mask];
                best_mask = mask;
            }
            // best_value = max(best_value, dp[mask]);
            // best_mask = mask;
            // cout << "VMMask: " << mask << " DP: " << dp[mask] << endl;
        }
    }
    int max_value = best_value;

    cout << max_value << endl;

    // Backtrack to find the matching
    int mask = best_mask;
    vector<pair<int, int>> matching;

    for (int i = N - 1; i >= 0; i--) {
        int j = backtrack[mask]; // Female j was matched with Male i
        matching.push_back({i, j});
        mask ^= (1 << j); // Remove j from the mask
    }

    // Print out the matching pairs
    // cout << "Matching Pairs (Male[i] -> Female[j]):" << endl;
    // for (auto& p : matching) {
    //     // cout << "Male[" << p.first << "] -> Female[" << p.second << "]" << endl;
    //     cout << p.first + 1 << " " << p.second + 1 << endl;
    // }
    for (int i = (int)matching.size() - 1; i >= 0; i--) {
        cout << matching[i].second + 1 << " ";
    }

    return 0;
}
// g++ -std=c++14 -o a c3-bitmap.cpp && ./a < a.in