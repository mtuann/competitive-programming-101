#include <iostream>
#include <vector>

using namespace std;

const int MOD = 1e9 + 7;
const int MAX_N = 1000000;

vector<long long> dp(MAX_N + 1, 0);

void compute_dp() {
    dp[0] = 1;
    for (int i = 1; i <= MAX_N; ++i) {
        dp[i] = (dp[i-1] * 3) % MOD;
        if (i >= 2) {
            dp[i] = (dp[i] + dp[i-2] * 2) % MOD;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    vector<int> queries(t);
    int max_n = 0;
    for (int i = 0; i < t; ++i) {
        cin >> queries[i];
        if (queries[i] > max_n) {
            max_n = queries[i];
        }
    }

    // Compute dp values up to the maximum `n` in queries
    compute_dp();

    // Output results for each query
    for (int i = 0; i < t; ++i) {
        cout << dp[queries[i]] << endl;
    }

    return 0;
}
