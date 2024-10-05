#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int MOD = 1e9 + 7;

int main() {
    int n; // Length of the final string
    string pattern; // The pattern string
    cin >> n >> pattern;

    int m = pattern.size();
    
    // If the pattern is longer than the string, it's impossible
    if (m > n) {
        cout << 0 << endl;
        return 0;
    }

    // Calculate 26^(n-m) mod MOD
    long long power = 1;
    for (int i = 0; i < n - m; ++i) {
        power = (power * 26) % MOD;
    }

    // Number of positions where the pattern can start
    long long positions = n - m + 1;

    // Total number of valid strings
    long long result = (positions * power) % MOD;

    cout << result << endl;

    return 0;
}
