#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>

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

// Function to calculate the number of distinct permutations
long long count_permutations(const std::string& s) {
    std::unordered_map<char, int> freq;
    for (char c : s) {
        freq[c]++;
    }
    
    int n = s.size();
    long long result = factorial[n];
    
    for (auto& [character, count] : freq) {
        result = result * inverse_factorial[count] % MOD;
    }
    
    return result;
}

int main() {
    std::string s;
    std::cin >> s;
    
    int n = s.size();
    
    // Precompute factorials and inverse factorials up to n
    precompute(n);
    
    // Compute the number of distinct permutations
    std::cout << count_permutations(s) << std::endl;
    
    return 0;
}
