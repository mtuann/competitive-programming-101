#include <iostream>
#include <string>
#include <vector>

using namespace std;

const int MOD = 1e9 + 7;

int m, d;
string a, b;
vector<vector<int>> dp;

// Function to count d-magic numbers with length `length` less than or equal to `x`
int count_d_magic_numbers(const string& x, bool tight, int pos, int mask, int length) {
    if (pos == length) return (mask == 0) ? 1 : 0; // Valid number if no odd-positioned digits are non-zero
    if (!tight && dp[pos][mask] != -1) return dp[pos][mask];

    int limit = tight ? x[pos] - '0' : 9;
    int count = 0;

    for (int digit = 0; digit <= limit; digit++) {
        if (pos % 2 == 0) { // Even positions (0, 2, 4...) => d can appear
            if (digit == d) {
                count += count_d_magic_numbers(x, tight && (digit == limit), pos + 1, mask, length);
                count %= MOD;
            } else if (digit != 0) {
                count += count_d_magic_numbers(x, tight && (digit == limit), pos + 1, mask | (1 << (digit - 1)), length);
                count %= MOD;
            } else {
                count += count_d_magic_numbers(x, tight && (digit == limit), pos + 1, mask, length);
                count %= MOD;
            }
        } else { // Odd positions (1, 3, 5...) => d cannot appear
            if (digit != d) {
                count += count_d_magic_numbers(x, tight && (digit == limit), pos + 1, mask, length);
                count %= MOD;
            }
        }
    }

    if (!tight) dp[pos][mask] = count;

    return count;
}

// Function to count d-magic numbers in the range [a, b]
int count_in_range(const string& low, const string& high) {
    int length = high.size();
    int count_high = count_d_magic_numbers(high, true, 0, 0, length);
    int count_low = count_d_magic_numbers(low, true, 0, 0, length);

    // To get count in range, we take count_high - count_low
    return (count_high - count_low + MOD) % MOD;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> m >> d;
    cin >> a >> b;

    // Initialize DP array
    dp.assign(2000, vector<int>(1 << 10, -1));

    // Count all d-magic numbers that are multiple of m in the range [a, b]
    int result = 0;

    for (int i = 0; i <= b.length(); i++) {
        string sub_b = b.substr(0, i);
        string sub_a = a.substr(0, i);

        for (int j = 0; j < m; j++) {
            if (count_in_range(sub_a, sub_b) % m == 0) {
                result += count_in_range(sub_a, sub_b);
                result %= MOD;
            }
        }
    }

    cout << result << endl;
    return 0;
}

// g++ -std=c++11 digit_cf_6282.cpp -o a && ./a 