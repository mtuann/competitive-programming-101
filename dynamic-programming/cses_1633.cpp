#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

const int MOD = 1e9 + 7;
const int MAXN = 10 + int(1e6);
int n;
int dp[MAXN];

int main() {
    
    cin >> n;

    memset(dp, 0, sizeof(dp));
    dp[0] = 1;  // Base case: there's one way to get the sum 0

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= 6; ++j) {
            if (i - j >= 0) {
                dp[i] = (dp[i] + dp[i - j]) % MOD;
            }
        }
    }

    cout << dp[n] << endl;
    return 0;
}
