#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

typedef long long ll;

vector<int> digits;
ll dp[20][180][2]; // dp[pos][sum][tight]: pos -> current digit position, sum -> sum of digits till now, tight -> if we're bound by the number `n`

// Digit DP function to calculate sum of digits from 0 to n
ll digit_sum_dp(int pos, int sum, bool tight) {
    if (pos == digits.size()) return sum;  // Base case: when we've processed all digits, return the sum
    if (dp[pos][sum][tight] != -1) return dp[pos][sum][tight];

    ll ans = 0;
    int limit = tight ? digits[pos] : 9;  // If tight is true, we must limit this position to the corresponding digit of n

    for (int d = 0; d <= limit; ++d) {
        ans += digit_sum_dp(pos + 1, sum + d, tight && (d == limit));  // Proceed with the next digit
    }

    return dp[pos][sum][tight] = ans;
}

// Function to compute digit sum for all numbers from 0 to n
ll digit_sum(ll n) {
    if (n < 0) return 0;
    
    digits.clear();
    while (n > 0) {
        digits.push_back(n % 10);  // Extract digits
        n /= 10;
    }
    
    reverse(digits.begin(), digits.end());  // Reverse to process from the most significant digit
    memset(dp, -1, sizeof(dp));  // Reset the dp table
    
    return digit_sum_dp(0, 0, true);
}

int main() {
    int t;
    cin >> t;  // Number of test cases
    while (t--) {
        ll a, b;
        cin >> a >> b;
        
        // Calculate the digit sum in the range [a, b]
        ll result = digit_sum(b) - digit_sum(a - 1);
        cout << result << endl;
    }

    return 0;
}

// g++ -std=c++11 -O2 -Wall spoj_PR003004.cpp -o a && ./a