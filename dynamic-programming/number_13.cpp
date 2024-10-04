#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

typedef long long ll;

vector<int> digits;
ll dp[20][2][2][2]; // dp[pos][last1][contains_13][tight]: pos -> current digit, last1 -> if last digit was 1, contains_13 -> whether we've already seen "13", tight -> if we are bound by the number `n`

// Function to calculate how many numbers do not contain "13"
ll digit_dp(int pos, bool last1, bool contains_13, bool tight) {
    if (contains_13) return 0;  // If "13" has already been found, exclude this number
    if (pos == digits.size()) return 1;  // Valid number, so return 1
    if (dp[pos][last1][contains_13][tight] != -1) return dp[pos][last1][contains_13][tight];

    ll ans = 0;
    int limit = tight ? digits[pos] : 9;  // If tight, limit this position to the corresponding digit of n

    for (int d = 0; d <= limit; ++d) {
        ans += digit_dp(pos + 1, d == 1, last1 && d == 3, tight && (d == limit));
    }

    return dp[pos][last1][contains_13][tight] = ans;
}

// Function to count how many numbers from 0 to n do not contain "13"
ll count_numbers_without_13(ll n) {
    if (n < 0) return 0;
    
    digits.clear();
    while (n > 0) {
        digits.push_back(n % 10);  // Extract digits
        n /= 10;
    }

    reverse(digits.begin(), digits.end());  // Reverse to process from the most significant digit
    memset(dp, -1, sizeof(dp));  // Reset the dp table
    
    return digit_dp(0, false, false, true);
}

int main() {
    ll l, r;
    cin >> l >> r;
    
    // Count numbers without "13" from l to r
    ll result = count_numbers_without_13(r) - count_numbers_without_13(l - 1);
    
    cout << result << endl;

    return 0;
}
