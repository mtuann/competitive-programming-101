#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

const int MOD = 1e9 + 7;

vector<int> digits;
int dp[110][2][2][2];  // dp[pos][last1][contains_13][tight]

// Function to perform digit dynamic programming and count numbers that do not contain "13"
int digit_dp(int pos, bool last1, bool contains_13, bool tight) {
    if (contains_13) return 0;  // Invalid number if "13" is found
    if (pos == digits.size()) return 1;  // Valid number, return 1
    if (dp[pos][last1][contains_13][tight] != -1) return dp[pos][last1][contains_13][tight];

    int ans = 0;
    int limit = tight ? digits[pos] : 9;  // If tight, limit the digit to the corresponding position

    for (int d = 0; d <= limit; ++d) {
        ans = (ans + digit_dp(pos + 1, d == 1, last1 && d == 3, tight && (d == limit))) % MOD;
    }

    return dp[pos][last1][contains_13][tight] = ans;
}

// Function to count numbers from 0 to n (represented by a string) that do not contain "13"
int count_numbers_without_13(const string &num_str) {
    digits.clear();
    for (char ch : num_str) {
        digits.push_back(ch - '0');  // Convert string digits to integers
    }

    memset(dp, -1, sizeof(dp));  // Initialize dp array to -1 for memoization

    return digit_dp(0, false, false, true);
}

int main() {
    freopen("smm.inp", "r", stdin);
    freopen("smm.out", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0);
    int n, q;
    string orginal_str;
    cin >> n >> q;
    cin >> orginal_str;
    memset(dp, -1, sizeof(dp));
    while(q--) {
        int op, u, v;
        cin >> op >> u >> v;
        if (op == 2) {
            orginal_str[u - 1] = v + '0';
        } else {
            
            string number = orginal_str.substr(u - 1, v - u + 1);
            int result = count_numbers_without_13(number);
            cout << result << endl;
        }
    }

    return 0;
}

// g++ -std=c++11 -O2 -Wall string_number_13.cpp -o a && ./a < a.in
