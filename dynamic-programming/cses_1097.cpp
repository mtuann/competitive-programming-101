#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<long long> x(n);
    for (int i = 0; i < n; ++i) {
        cin >> x[i];
    }

    // dp[i][j] will store the maximum score difference (player1 - player2) for subarray [i, j]
    vector<vector<long long>> dp(n, vector<long long>(n, 0));

    // Base case: when the subarray is of length 1
    for (int i = 0; i < n; ++i) {
        dp[i][i] = x[i];
    }

    // Fill the DP table for subarrays of length 2 up to n
    for (int len = 2; len <= n; ++len) {
        for (int i = 0; i <= n - len; ++i) {
            int j = i + len - 1;
            dp[i][j] = max(x[i] - dp[i+1][j], x[j] - dp[i][j-1]);
        }
    }

    // Calculate the maximum possible score for the first player
    long long total_sum = 0;
    for (int i = 0; i < n; ++i) {
        total_sum += x[i];
    }
    long long max_score_difference = dp[0][n-1];
    long long first_player_max_score = (total_sum + max_score_difference) / 2;

    cout << first_player_max_score << endl;

    return 0;
}
