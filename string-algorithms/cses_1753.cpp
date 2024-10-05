#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Function to build the LPS (Longest Prefix Suffix) array
vector<int> buildLPS(const string &pattern) {
    int m = pattern.length();
    vector<int> lps(m, 0);
    
    int length = 0; // Length of the previous longest prefix suffix
    int i = 1; // Start from the second character
    while (i < m) {
        if (pattern[i] == pattern[length]) {
            length++;
            lps[i] = length;
            i++;
        } else {
            if (length != 0) {
                // Don't increment i here
                length = lps[length - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
    return lps;
}

// Function to count the occurrences of the pattern in the string
int KMP(const string &text, const string &pattern) {
    int n = text.length();
    int m = pattern.length();
    
    // Build the LPS array for the pattern
    vector<int> lps = buildLPS(pattern);
    
    int i = 0; // index for text
    int j = 0; // index for pattern
    int count = 0; // To count the occurrences
    
    while (i < n) {
        if (pattern[j] == text[i]) {
            i++;
            j++;
        }
        
        if (j == m) {
            count++;
            j = lps[j - 1];
        } else if (i < n && pattern[j] != text[i]) {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }
    
    return count;
}

int main() {
    string text, pattern;
    cin >> text >> pattern;
    
    // Count the number of occurrences of the pattern in the text
    int result = KMP(text, pattern);
    
    // Output the result
    cout << result << endl;
    
    return 0;
}
