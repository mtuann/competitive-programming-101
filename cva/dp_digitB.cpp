#include <iostream>
#include <vector>
#include <cstring>

const int MOD = 1e9 + 7;
using namespace std;

int D;
vector<int> digits;
int dp[10005][105][2];

// Function for digit DP
int digit_dp(int pos, int mod, bool tight) {
    if (pos == digits.size()) {
        return (mod % D == 0) ? 1 : 0;  // Check if the sum modulo D is 0
    }

    if (dp[pos][mod][tight] != -1) {
        return dp[pos][mod][tight];
    }

    int limit = tight ? digits[pos] : 9;
    int res = 0;

    for (int d = 0; d <= limit; d++) {
        res = (res + digit_dp(pos + 1, (mod + d) % D, tight && (d == limit))) % MOD;
    }

    return dp[pos][mod][tight] = res;
}

// Function to process the number as a string and convert it into digits
int solve(string K) {
    digits.clear();
    for (char c : K) {
        digits.push_back(c - '0');  // Convert character to digit
    }

    memset(dp, -1, sizeof(dp));  // Reset dp array

    // Start from the first digit, with sum mod D = 0 and tight = true (because we are restricted by K initially)
    return digit_dp(0, 0, 1);
}

int main() {
    string K;
    cin >> K;  // Input large number K as string
    cin >> D;  // Input divisor D

    int result = solve(K);
    cout << (result - 1 + MOD ) % MOD<< endl;  // Output the result
    return 0;
}

// g++ -std=c++11 dp_digitB.cpp -o a && ./a < a.in
