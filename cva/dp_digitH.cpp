#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

long long L, R, k;
vector<int> digits;
long long dp[20][135][2];  // dp[pos][mod][tight]

long long digit_dp(int pos, int mod, bool tight, int prev_digit) {
    if (pos == digits.size()) {
        return mod == 0 ? 1 : 0;  // Count if the number is valid
    }

    if (dp[pos][mod][tight] != -1) {
        return dp[pos][mod][tight];
    }

    int limit = tight ? digits[pos] : 9;
    long long count = 0;

    for (int d = 0; d <= limit; ++d) {
        if (d == prev_digit) continue;  // Skip if two consecutive digits are the same
        
        // Calculate next tightness
        count += digit_dp(pos + 1, (mod * 10 + d) % k, tight && (d == limit), d);
    }

    return dp[pos][mod][tight] = count;
}

// Function to count numbers <= n that are divisible by k
long long count_valid(long long n) {
    digits.clear();
    while (n > 0) {
        digits.push_back(n % 10);
        n /= 10;
    }
    reverse(digits.begin(), digits.end());
    
    memset(dp, -1, sizeof(dp));
    return digit_dp(0, 0, true, -1);  // Start with no previous digit
}

// Function to find the smallest lexicographical number >= L and <= R
long long find_smallest_number() {
    for (long long x = L; x <= R; ++x) {
        if (x % k == 0) {
            // Convert to string for lexicographical comparison
            string str_x = to_string(x);
            // Ensure no two consecutive identical digits
            bool valid = true;
            for (int i = 1; i < str_x.size(); ++i) {
                if (str_x[i] == str_x[i - 1]) {
                    valid = false;
                    break;
                }
            }
            if (valid) {
                return x;  // Return the first valid number found
            }
        }
    }
    return -1;  // If no valid number found
}

int main() {
    while (cin >> L >> R >> k) {
        // Count valid numbers in the range [L, R]
        long long valid_count = count_valid(R) - count_valid(L - 1);
        
        // Find the smallest valid number in the range [L, R]
        long long smallest_number = find_smallest_number();
        
        // Output results
        cout << smallest_number << endl;
    }
    return 0;
}


// g++ -std=c++11 dp_digitH.cpp -o a && ./a
