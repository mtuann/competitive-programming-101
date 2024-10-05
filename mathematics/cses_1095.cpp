#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

// Function to calculate a^b % MOD using binary exponentiation
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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    while (n--) {
        long long a, b;
        cin >> a >> b;
        if (a == 0 && b == 0) {
            cout << 1 << "\n";  // 0^0 is considered 1
        } else {
            cout << mod_pow(a, b, MOD) << "\n";
        }
    }

    return 0;
}
