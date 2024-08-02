#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int editDistance(const string& s1, const string& s2) {
    int n = s1.length();
    int m = s2.length();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1));

    // Initialize the base cases
    for (int i = 0; i <= n; ++i) {
        dp[i][0] = i; // Cost of deleting all characters from s1
    }
    for (int j = 0; j <= m; ++j) {
        dp[0][j] = j; // Cost of inserting all characters into s1
    }

    // Fill the dp table
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1]; // No change needed
            } else {
                dp[i][j] = min({
                    dp[i - 1][j] + 1, // Delete
                    dp[i][j - 1] + 1, // Insert
                    dp[i - 1][j - 1] + 1 // Replace
                });
            }
        }
    }

    return dp[n][m];
}

int main() {
    string s1, s2;
    cin >> s1 >> s2;
    cout << editDistance(s1, s2) << endl;
    return 0;
}
