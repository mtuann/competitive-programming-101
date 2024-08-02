#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <algorithm>

using namespace std;

const int MAX_DIGITS = 19;
const int MOD = 1e9 + 7;

// DP table
long long dp[MAX_DIGITS][10][2];

// Function to count valid numbers up to the given limit
long long countValidNumbers(const string &limit) {
    int n = limit.size();
    memset(dp, -1, sizeof(dp));

    auto dfs = [&](int pos, int lastDigit, bool isTight) -> long long {
        if (pos == n) return 1; // We've placed all digits successfully

        if (dp[pos][lastDigit][isTight] != -1) return dp[pos][lastDigit][isTight];

        int maxDigit = isTight ? limit[pos] - '0' : 9;
        long long result = 0;

        for (int digit = 0; digit <= maxDigit; ++digit) {
            if (digit != lastDigit) {
                result += dfs(pos + 1, digit, isTight && (digit == maxDigit));
                result %= MOD;
            }
        }

        return dp[pos][lastDigit][isTight] = result;
    };

    return dfs(0, -1, true);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    long long a, b;
    cin >> a >> b;

    string strA = to_string(a - 1);
    string strB = to_string(b);

    long long result = (countValidNumbers(strB) - countValidNumbers(strA) + MOD) % MOD;

    cout << result << endl;

    return 0;
}
