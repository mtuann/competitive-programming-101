#include <iostream>
using namespace std;

const int MOD = 1000000007;

// Function to perform modular exponentiation
long long modExp(long long base, long long exp, int mod) {
    long long result = 1;
    base = base % mod; // Handle base greater than mod

    while (exp > 0) {
        if (exp % 2 == 1) // If exp is odd, multiply base with result
            result = (result * base) % mod;
        
        exp = exp >> 1; // Divide exp by 2
        base = (base * base) % mod; // Square the base
    }

    return result;
}

int main() {
    int n;
    cin >> n;

    // Compute 2^n % (10^9 + 7)
    long long result = modExp(2, n, MOD);

    // Print the result
    cout << result << endl;

    return 0;
}
