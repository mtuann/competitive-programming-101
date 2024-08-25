#include <iostream>
#include <vector>
#include <unordered_set>
#include <string>
using namespace std;

const int MOD = 1000000007;

int countWaysToSplit(const string& X, const unordered_set<string>& stringSet, int maxLength) {
    int n = X.size();
    vector<int> dp(n + 1, 0);
    dp[0] = 1;  // Base case: There's 1 way to split an empty string

    for (int i = 1; i <= n; i++) {
        string currentSubstring = "";
        for (int j = i; j > 0 && (i - j + 1) <= maxLength; j--) {
            currentSubstring = X[j - 1] + currentSubstring;  // Build the substring in reverse
            if (stringSet.find(currentSubstring) != stringSet.end()) {
                dp[i] = (dp[i] + dp[j - 1]) % MOD;
            }
        }
    }

    return dp[n];
}

int main() {
    int n;
    cin >> n;
    unordered_set<string> stringSet;
    int maxLength = 0;

    // Insert all strings from the set into the hash set
    for (int i = 0; i < n; i++) {
        string Si;
        cin >> Si;
        stringSet.insert(Si);
        maxLength = max(maxLength, (int)Si.size());
    }

    string X;
    cin >> X;

    // Calculate the number of ways to split X
    int result = countWaysToSplit(X, stringSet, maxLength);
    cout << result << endl;

    return 0;
}
// g++ -std=c++14 -o a cf-trie3.cpp && ./a < a.in
