#include <iostream>
#include <vector>
using namespace std;

// Function to compute the prefix function
vector<int> computePrefixFunction(const string& s) {
    int n = s.length();
    vector<int> pi(n);
    for (int i = 1; i < n; i++) {
        int j = pi[i - 1]; // length of the previous longest border
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

// Function to find all period lengths
vector<int> findPeriodLengths(const string& s) {
    int n = s.length();
    vector<int> pi = computePrefixFunction(s);
    vector<int> periods;
    
    for (int i = 0; i < n; i++) {
        // Length of the period can be derived from pi
        int len = i + 1; // Length of the current substring s[0:i]
        int period = len - pi[i]; // Period length
        if (len % period == 0) {
            periods.push_back(len);
        }
    }
    
    return periods;
}

int main() {
    string s;
    cin >> s;

    vector<int> periods = findPeriodLengths(s);
    for (int length : periods) {
        cout << length << " ";
    }
    cout << endl;

    return 0;
}
