#include <iostream>
#include <vector>

const int MOD = 1e9 + 7;

std::vector<long long> factorial;
std::vector<long long> inverse_factorial;

// Function to compute modular inverse using Fermat's Little Theorem
long long mod_inv(long long a, int mod) {
    long long result = 1, exp = mod - 2;
    while (exp > 0) {
        if (exp % 2 == 1) result = result * a % mod;
        a = a * a % mod;
        exp /= 2;
    }
    return result;
}

// Function to precompute factorials and their modular inverses
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

// Function to compute the binomial coefficient C(a, b) % MOD
long long binomial_coefficient(int a, int b) {
    if (b > a || b < 0) return 0;
    return factorial[a] * inverse_factorial[b] % MOD * inverse_factorial[a - b] % MOD;
}

int main() {
    int n, m;
    std::cin >> n >> m;
    
    // Compute factorials and inverse factorials up to (n + m - 1)
    precompute(n + m - 1);
    
    // Compute the number of ways to distribute m apples among n children
    std::cout << binomial_coefficient(n + m - 1, m) << std::endl;
    
    return 0;
}
