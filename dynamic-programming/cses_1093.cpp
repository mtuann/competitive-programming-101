#include <iostream>
#include <vector>

const int MOD = 1e9 + 7;

using namespace std;

int countWaysToDivide(int n) {
    long long sum = (n * (n + 1)) / 2;
    
    // If sum is odd, we cannot split into two equal subsets
    if (sum % 2 != 0) return 0;

    long long target = sum / 2;
    vector<long long> dp(target + 1, 0);
    dp[0] = 1; // Base case: one way to make sum 0

    for (int i = 1; i <= n; ++i) {
        for (int j = target; j >= i; --j) {
            dp[j] = (dp[j] + dp[j - i]) % MOD;
        }
    }

    return (dp[target] * 500000004) % MOD; // Multiply by modular inverse of 2 to divide by 2
}

int main() {
    int n;
    cin >> n;

    cout << countWaysToDivide(n) << endl;

    return 0;
}
