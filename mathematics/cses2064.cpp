#include <iostream>
#include <vector>

const int MOD = 1e9 + 7;

std::vector<long long> factorial;
std::vector<long long> inverse_factorial;

long long mod_inv(long long a, int mod) {
    long long result = 1, exp = mod - 2;
    while (exp > 0) {
        if (exp % 2 == 1) result = result * a % mod;
        a = a * a % mod;
        exp /= 2;
    }
    return result;
}

void precompute(int max_n) {
    factorial.resize(max_n + 1);
    inverse_factorial.resize(max_n + 1);
    factorial[0] = 1;
    for (int i = 1; i <= max_n; ++i) {
        factorial[i] = factorial[i - 1] * i % MOD;
    }
    inverse_factorial[max_n] = mod_inv(factorial[max_n], MOD);
    for (int i = max_n - 1; i >= 0; --i) {
        inverse_factorial[i] = inverse_factorial[i + 1] * (i + 1) % MOD;
    }
}

long long catalan_number(int n) {
    if (n % 2 != 0) return 0; // If n is not even, no valid sequence.
    int k = n / 2;
    return factorial[2 * k] * inverse_factorial[k + 1] % MOD * inverse_factorial[k] % MOD;
}

int main() {
    int n;
    std::cin >> n;
    
    precompute(n); // Precompute factorials and inverse factorials up to n
    
    std::cout << catalan_number(n) << std::endl;
    
    return 0;
}
