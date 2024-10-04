#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

const int MOD = 1e9 + 7;

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
        if (!num_started || abs(d - prev_digit) <= 1) {  // Ensure no two consecutive digits are the same unless it's leading zeros
            res += digit_dp(pos + 1, d, tight && (d == limit), num_started || d != 0);
        }
    }

    return dp[pos][prev_digit][tight][num_started] = res;
}

// Function to count special numbers <= n
long long count_special(long long n) {
    if (n < 0) return 0;

    digits.clear();
    while (n > 0) {
        digits.push_back(n % 10);
        n /= 10;
    }
    reverse(digits.begin(), digits.end());

    memset(dp, -1, sizeof(dp));
    return digit_dp(0, 10, 1, 0);  // Start with no previous digit (-1)
}

// Function to find the Kth special number greater than X
long long find_kth_special(long long K, long long X) {
    long long low = X + 1;
    long long high = 1e18;  // A large upper limit for the search

    while (low < high) {
        long long mid = (low + high) / 2;
        long long count = count_special(mid) - count_special(X);
        // cout << "Mid: " << mid << " Count: " << count << endl;
        if (count >= K) {
            high = mid;  // The Kth number is in the lower half
        } else {
            low = mid + 1;  // The Kth number is in the upper half
        }
    }

    return low;  // The Kth special number
}

int main() {
    long long K, X;
    cin >> K >> X;
    // cout << "K: " << K << " X: " << X << endl;
    long long result = find_kth_special(K, X);
    cout << result << endl;

    return 0;
}



// g++ -std=c++11 dp_digitG.cpp -o a && ./a < a.in
