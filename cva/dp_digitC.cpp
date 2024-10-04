#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

vector<int> digits;
long long dp[20][11][2][2];  // Adding another dimension to track if the number has started (no leading zeros)

// Recursive DP function
long long digit_dp(int pos, int prev_digit, bool tight, bool num_started) {
    if (pos == digits.size()) {
        return 1;  // Valid number found
    }

    if (dp[pos][prev_digit][tight][num_started] != -1) {
        return dp[pos][prev_digit][tight][num_started];
    }

    int limit = tight ? digits[pos] : 9;
    long long res = 0;

    for (int d = 0; d <= limit; ++d) {
        if (!num_started || d != prev_digit) {  // Ensure no two consecutive digits are the same unless it's leading zeros
            res += digit_dp(pos + 1, d, tight && (d == limit), num_started || d != 0);
        }
    }

    return dp[pos][prev_digit][tight][num_started] = res;
}

// Helper function to count valid numbers <= n
long long count_valid(long long n) {
    if (n < 0) return 0;  // Edge case when n is 0
    if (n == 0) return 1;  // Special case for 0
    
    digits.clear();
    while (n > 0) {
        digits.push_back(n % 10);
        n /= 10;
    }
    reverse(digits.begin(), digits.end());
    
    memset(dp, -1, sizeof(dp));

    return digit_dp(0, 10, 1, 0);  // Start with prev_digit = 10 (no prev digit), tight=true, and num_started=false
}

// Main function to solve the range problem
int main() {
    long long a, b;
    
    cin >> a >> b;

    long long result_b = count_valid(b);  // Count valid numbers <= b
    long long result_a = count_valid(a - 1);  // Count valid numbers < a

    cout << result_b - result_a << endl;  // Difference gives valid numbers in range [a, b]

    return 0;
}

// g++ -std=c++11 dp_digitC.cpp -o a && ./a < a.in
