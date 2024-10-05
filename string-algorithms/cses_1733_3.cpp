#include <iostream>
#include <vector>
#include <string>
using namespace std;

const int MOD = 1e9 + 7; // Modulo value for hashing
const int BASE = 31;      // Base for polynomial rolling hash

// Function to compute x^y % p using iterative exponentiation by squaring
long long modPow(long long x, long long y, long long p) {
    long long res = 1; // Initialize result
    x = x % p;         // Update x if it is more than or equal to p
    while (y > 0) {
        // If y is odd, multiply x with result
        if (y & 1)
            res = (res * x) % p;
        // y must be even now
        y = y >> 1; // y = y/2
        x = (x * x) % p; // Change x to x^2
    }
    return res;
}

// Function to compute hash values of the prefixes of the string
vector<long long> computeHash(const string& s) {
    int n = s.size();
    vector<long long> hash(n + 1, 0);
    long long base_power = 1; // BASE^i % MOD
    
    for (int i = 0; i < n; ++i) {
        hash[i + 1] = (hash[i] * BASE + (s[i] - 'a' + 1)) % MOD;
        base_power = (base_power * BASE) % MOD;
    }
    
    return hash;
}

// Function to get the hash of the substring s[l:r] (0-based, inclusive)
long long getSubstringHash(const vector<long long>& hash, int l, int r) {
    return (hash[r + 1] - (hash[l] * modPow(BASE, r - l + 1, MOD) % MOD) + MOD) % MOD;
}

// Function to find all period lengths using hashing
vector<int> findPeriodLengths(const string& s) {
    int n = s.size();
    vector<long long> hash = computeHash(s);
    vector<int> periods;
    
    for (int len = 1; len <= n; ++len) {
        if (n % len == 0) { // Check if length divides n
            long long pattern_hash = getSubstringHash(hash, 0, len - 1);
            bool is_period = true;
            for (int start = len; start < n; start += len) {
                if (getSubstringHash(hash, start, start + len - 1) != pattern_hash) {
                    is_period = false;
                    break;
                }
            }
            if (is_period) {
                periods.push_back(len);
            }
        }
    }
    
    return periods;
}

// Main function
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
