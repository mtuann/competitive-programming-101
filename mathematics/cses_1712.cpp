#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;
const int MOD_EXP = MOD - 1;  // Fermat's Theorem requires using mod (MOD-1) for exponents

// Function to calculate a^b % mod using binary exponentiation
long long mod_pow(long long a, long long b, long long mod) {
    long long result = 1;
    a %= mod;
    while (b > 0) {
        if (b % 2 == 1) {
            result = (result * a) % mod;
        }
        a = (a * a) % mod;
        b /= 2;
    }
    return result;
}

// Function to calculate b^c % (MOD-1) for exponent reduction
long long mod_exp_pow(long long b, long long c) {
    return mod_pow(b, c, MOD_EXP);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    while (n--) {
        long long a, b, c;
        cin >> a >> b >> c;

        if (a == 0 && b == 0) {
            if (c == 0) {
                cout << 0 << "\n";  // Any 0^k is 0
            } else {
                cout << 1 << "\n";  // 0^0 is considered 1
            }
            
        } else if (a == 0) {
            cout << 0 << "\n";  // Any 0^k is 0
        } else {
            // First calculate b^c % (MOD-1)
            long long exp = mod_exp_pow(b, c);
            // Now calculate a^exp % MOD
            cout << mod_pow(a, exp, MOD) << "\n";
        }
    }

    return 0;
}
