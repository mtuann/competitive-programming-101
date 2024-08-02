#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>  // For memset

using namespace std;

const int MAXN = 5001;
int n;
long long x[MAXN];
long long dp[MAXN][MAXN];

// Recursive function with memoization to calculate the maximum score difference
long long maxScoreDifference(int i, int j) {
    if (i > j) return 0;
    if (i == j) return x[i];

    if (dp[i][j] != -1) return dp[i][j];

    // Choose either to remove the element at i or at j
    long long takeLeft = x[i] - maxScoreDifference(i + 1, j);
    long long takeRight = x[j] - maxScoreDifference(i, j - 1);

    // Store and return the maximum of these choices
    dp[i][j] = max(takeLeft, takeRight);
    return dp[i][j];
}

int main() {
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> x[i];
    }

    // Initialize DP table with -1 (indicating uncomputed states)
    memset(dp, -1, sizeof(dp));

    // Calculate the maximum score difference for the entire array
    long long total_sum = 0;
    for (int i = 0; i < n; ++i) {
        total_sum += x[i];
    }
    long long max_score_difference = maxScoreDifference(0, n - 1);
    long long first_player_max_score = (total_sum + max_score_difference) / 2;

    cout << first_player_max_score << endl;

    return 0;
}
