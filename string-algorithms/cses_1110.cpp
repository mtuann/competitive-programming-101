#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Function to find the lexicographically minimal rotation using Booth's algorithm
string minimalRotation(const string& s) {
    string doubled = s + s;  // Double the string
    int n = s.size();
    vector<int> f(n * 2, -1); // Failure function
    int k = 0; // Least rotation of string found so far

    for (int j = 1; j < doubled.size(); j++) {
        char sj = doubled[j];
        int i = f[j - k - 1];

        while (i != -1 && sj != doubled[k + i + 1]) {
            if (sj < doubled[k + i + 1]) {
                k = j - i - 1;
            }
            i = f[i];
        }
        if (sj != doubled[k + i + 1]) {
            if (sj < doubled[k]) {
                k = j;
            }
            f[j - k] = -1;
        } else {
            f[j - k] = i + 1;
        }
    }

    return doubled.substr(k, n); // Return the minimal rotation
}

// Main function
int main() {
    string s;
    cin >> s;

    string result = minimalRotation(s);
    cout << result << endl;

    return 0;
}
