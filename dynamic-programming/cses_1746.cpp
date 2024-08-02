#include <iostream>
#include <vector>

using namespace std;

const int MOD = 1e9 + 7;

int main() {
    int n, m;
    cin >> n >> m;
    
    vector<int> x(n);
    for (int i = 0; i < n; ++i) {
        cin >> x[i];
    }
    
    vector<vector<int>> dp(n, vector<int>(m + 1, 0));
    
    // Initialization for the first index
    if (x[0] == 0) {
        for (int v = 1; v <= m; ++v) {
            dp[0][v] = 1;
        }
    } else {
        dp[0][x[0]] = 1;
    }
    
    // Fill the dp table
    for (int i = 1; i < n; ++i) {
        if (x[i] == 0) {
            for (int v = 1; v <= m; ++v) {
                dp[i][v] = dp[i-1][v];
                if (v > 1) dp[i][v] = (dp[i][v] + dp[i-1][v-1]) % MOD;
                if (v < m) dp[i][v] = (dp[i][v] + dp[i-1][v+1]) % MOD;
            }
        } else {
            int v = x[i];
            dp[i][v] = dp[i-1][v];
            if (v > 1) dp[i][v] = (dp[i][v] + dp[i-1][v-1]) % MOD;
            if (v < m) dp[i][v] = (dp[i][v] + dp[i-1][v+1]) % MOD;
        }
    }
    
    int result = 0;
    for (int v = 1; v <= m; ++v) {
        result = (result + dp[n-1][v]) % MOD;
    }
    
    cout << result << endl;
    
    return 0;
}
