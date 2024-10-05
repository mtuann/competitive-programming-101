#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Function to transform the input string for Manacher's algorithm
string preprocess(const string& s) {
    string result = "#";
    for (char c : s) {
        result += c;
        result += "#";
    }
    return result;
}

// Function to find the longest palindromic substring using Manacher's algorithm
string longestPalindromicSubstring(const string& s) {
    string T = preprocess(s);
    int n = T.size();
    vector<int> P(n, 0); // Array to store the radius of palindromes
    int center = 0, right = 0;

    for (int i = 1; i < n - 1; i++) {
        if (i < right) {
            P[i] = min(right - i, P[2 * center - i]); // Use the mirror property
        }

        // Attempt to expand the palindrome centered at i
        while (T[i + P[i] + 1] == T[i - P[i] - 1]) {
            P[i]++;
        }

        // Update the center and right boundary if the palindrome extends past right
        if (i + P[i] > right) {
            center = i;
            right = i + P[i];
        }
    }

    // Find the maximum radius and its center
    int maxLen = 0, centerIndex = 0;
    for (int i = 1; i < n - 1; i++) {
        if (P[i] > maxLen) {
            maxLen = P[i];
            centerIndex = i;
        }
    }

    // Extract the longest palindrome
    // int start = (centerIndex - maxLen) / 2; // Calculate the start index in the original string
    int start = max(0, (centerIndex - maxLen) / 2); // Ensure start is non-negative

    return s.substr(start, maxLen); // Return the longest palindromic substring
}

// Main function
int main() {
    string s;
    cin >> s;

    string result = longestPalindromicSubstring(s);
    cout << result << endl;

    return 0;
}
