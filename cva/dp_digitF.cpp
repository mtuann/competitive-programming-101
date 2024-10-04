#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <algorithm>

using namespace std;

const int MOD = 1e9 + 7;

vector<int> digits, digits_a;
long long dp[20][150][2]; // DP table to store the count of valid numbers

// Function to count numbers <= n with a digit sum equal to S
long long digit_dp(int pos, int sum, bool tight, int S) {
    if (sum < 0) return 0;  // Invalid sum
    if (pos == digits.size()) {
        // if (sum == 0) cout << pos << " " << sum << " " << tight <<  " " << S << " " << 1 << endl;
        dp[pos][sum][tight] = sum == 0 ? 1 : 0;
        return sum == 0 ? 1 : 0;  // If we've used all digits, check if sum is exactly 0
    }

    if (dp[pos][sum][tight] != -1) {
        return dp[pos][sum][tight];
    }

    int limit = tight ? digits[pos] : 9;
    long long res = 0;

    for (int d = 0; d <= limit; ++d) {
        res += digit_dp(pos + 1, sum - d, tight && (d == limit), S);
    }
    // if (sum == S) cout << pos << " " << sum << " " << tight <<  " " << S << " " << res << endl;
    return dp[pos][sum][tight] = res;
}

// Helper function to calculate count of numbers <= n with a digit sum of S
long long count_numbers_with_sum(long long n, int S) {
    digits.clear();
    while (n > 0) {
        digits.push_back(n % 10);
        n /= 10;
    }
    reverse(digits.begin(), digits.end());
    memset(dp, -1, sizeof(dp));

    return digit_dp(0, S, 1, S);  // Start digit DP with the full number
}

// Function to find the smallest number in [A, B] with a digit sum of S
long long find_smallest_number_with_sum(long long A, long long B, int S) {
    digits.clear();
    digits_a.clear();
    
    // Extract digits of B
    while (B > 0) {
        digits.push_back(B % 10);
        B /= 10;
    }
    reverse(digits.begin(), digits.end());
    
    // Extract digits of A
    while (A > 0) {
        digits_a.push_back(A % 10);
        A /= 10;
    }
    reverse(digits_a.begin(), digits_a.end());

    // Ensure digits_a and digits have the same size by padding A with leading 0s if needed
    while (digits_a.size() < digits.size()) {
        digits_a.insert(digits_a.begin(), 0);
    }

    vector<int> smallest;
    int sum = S;
    bool tight = true;
    bool is_equal_to_A = true; // Check if we're still constructing a number equal to A
    // cout << "Digits length: " << digits.size() << endl;
    for (int pos = 0; pos < digits.size(); ++pos) {
        int limit = tight ? digits[pos] : 9;
        bool found = false;
        
        // Compare each digit of A and B to ensure the number >= A
        for (int d = 0; d <= limit; ++d) {
            if (is_equal_to_A && d < digits_a[pos]) {
                continue; // If we're still equal to A, don't pick a digit smaller than A's current digit
            }
            // cout << "Checking digit: " << d << " at pos: " << pos << endl;
            int next_sum = sum - d;
            if (next_sum >= 0) {
                // Try to see if the current digit can form a valid solution
                // memset(dp, -1, sizeof(dp));
                // int count = digit_dp(pos + 1, next_sum, tight && (d == limit), S);
                long long count = dp[pos + 1][next_sum][tight && (d == limit)];
                
                // cout << "Count: " << count << " at pos: " << pos + 1 << " next_sum = " << next_sum << " tight = " << tight << " d = " << d << " limit = " << limit <<  " " << (tight && (d == limit)) << endl;
                if (count > 0) {
                    smallest.push_back(d);
                    // cout << "Adding digit: " << d << " to smallest at pos: " << pos << endl;
                    sum = next_sum;
                    if (d < limit) tight = false;
                    if (d > digits_a[pos]) is_equal_to_A = false; // Once we surpass A, we don't need to follow A's digits
                    found = true;
                    break;
                }
            }
        }
        if (!found) break;  // Should never happen, as at least one valid number exists.
    }

    // Convert the vector of digits back to the smallest number
    long long smallest_number = 0;
    for (int d : smallest) {
        smallest_number = smallest_number * 10 + d;
    }

    return smallest_number;  // Return the smallest number that is >= A and satisfies the condition
}

int main() {
    long long A, B;
    int S;
    cin >> A >> B >> S;

    // Count how many numbers in range [A, B] have a digit sum of S
    long long count_a = count_numbers_with_sum(A - 1, S);
    
    long long count_b = count_numbers_with_sum(B, S);
    long long count_in_range = count_b - count_a;
    
    // Find the smallest number in range [A, B] with digit sum of S
    long long smallest_number = find_smallest_number_with_sum(A, B, S);

    // Output the results
    cout << count_in_range << endl;  // First output: count of valid numbers
    cout << smallest_number << endl;  // Second output: the smallest valid number

    return 0;
}


// g++ -std=c++11 dp_digitF.cpp -o a && ./a < a.in
