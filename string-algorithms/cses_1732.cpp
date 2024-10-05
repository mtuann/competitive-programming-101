#include <iostream>
#include <vector>
using namespace std;

// Function to compute the prefix function
vector<int> computePrefixFunction(const string& s) {
    int n = s.length();
    vector<int> pi(n);
    for (int i = 1; i < n; i++) {
        int j = pi[i - 1]; // length of previous longest border
        while (j > 0 && s[i] != s[j]) {
            j = pi[j - 1]; // fall back to the previous border
        }
        if (s[i] == s[j]) {
            j++;
        }
        pi[i] = j; // set the prefix function
    }
    return pi;
}

// Function to find all border lengths
vector<int> findBorderLengths(const string& s) {
    vector<int> pi = computePrefixFunction(s);
    vector<int> borders;
    
    int borderLength = pi.back(); // Length of the longest border
    while (borderLength > 0) {
        borders.push_back(borderLength);
        borderLength = pi[borderLength - 1]; // Move to the next border
    }
    
    // Reverse the borders to print in increasing order
    reverse(borders.begin(), borders.end());
    return borders;
}

int main() {
    string s;
    cin >> s;

    vector<int> borders = findBorderLengths(s);
    for (int length : borders) {
        cout << length << " ";
    }
    cout << endl;

    return 0;
}
