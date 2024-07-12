#include <iostream>
#include <vector>

const int MOD = 1000000007;
const int MAX = 1000000;

std::vector<long long> fact(MAX + 1);
std::vector<long long> inv_fact(MAX + 1);

// Function to perform modular exponentiation
long long mod_pow(long long base, long long exp, long long mod) {
    long long result = 1;
    while (exp > 0) {
        if (exp % 2 == 1)
            result = (result * base) % mod;
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

// Function to preprocess factorials and their inverses
void preprocess() {
    fact[0] = fact[1] = 1;
    for (int i = 2; i <= MAX; ++i) {
        fact[i] = fact[i - 1] * i % MOD;
    }

    inv_fact[MAX] = mod_pow(fact[MAX], MOD - 2, MOD); // Fermat's little theorem
    for (int i = MAX - 1; i >= 0; --i) {
        inv_fact[i] = inv_fact[i + 1] * (i + 1) % MOD;
    }
}

// Function to calculate binomial coefficient C(a, b) % MOD
long long binomial_coefficient(int a, int b) {
    if (b > a) return 0;
    return fact[a] * inv_fact[b] % MOD * inv_fact[a - b] % MOD;
}

int main() {
    preprocess();

    int n;
    std::cin >> n;
    while (n--) {
        int a, b;
        std::cin >> a >> b;
        std::cout << binomial_coefficient(a, b) << "\n";
    }

    return 0;
}

// https://cses.fi/problemset/task/1716
// Stars and Bars: The problem of distributing identical objects into distinct groups can be solved using the "stars and bars" technique. Imagine representing the m apples as stars (*) and using n-1 bars (|) to separate them into n groups (for the children). For example:
// **|*|***  (2 apples for child 1, 1 for child 2, 3 for child 3)
