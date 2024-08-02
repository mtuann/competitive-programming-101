#include <iostream>
#include <vector>

using namespace std;

const int MOD = 1e9 + 7;

int main() {
    int n, m;
    cin >> n >> m;
    
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    dp[0][0] = 1;
    
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= m; ++j) {
            if (dp[i][j] > 0) {
                if (i + 1 <= n && j + 1 <= m) {
                    dp[i + 1][j + 1] = (dp[i + 1][j + 1] + dp[i][j]) % MOD;
                }
                if (i + 2 <= n) {
                    dp[i + 2][j] = (dp[i + 2][j] + dp[i][j]) % MOD;
                }
                if (j + 2 <= m) {
                    dp[i][j + 2] = (dp[i][j + 2] + dp[i][j]) % MOD;
                }
            }
        }
    }

    cout << dp[n][m] << endl;
    
    return 0;
}
