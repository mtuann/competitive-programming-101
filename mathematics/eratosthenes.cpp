#include <iostream>
#include <vector>
#include <unordered_map>
#include <cmath>

using namespace std;

const int MAX_N = 1000000;

vector<int> smallest_prime_factor(MAX_N + 1);

void compute_spf() {
    // Sieve of Eratosthenes to compute smallest prime factors
    for (int i = 2; i <= MAX_N; ++i) {
        smallest_prime_factor[i] = i; // Initialize with itself
    }
    
    for (int p = 2; p * p <= MAX_N; ++p) {
        if (smallest_prime_factor[p] == p) { // p is prime
            for (int multiple = p * p; multiple <= MAX_N; multiple += p) {
                if (smallest_prime_factor[multiple] == multiple) {
                    smallest_prime_factor[multiple] = p;
                }
            }
        }
    }
}

unordered_map<int, int> get_prime_factors(int n) {
    unordered_map<int, int> factors;
    
    while (n != 1) {
        int prime_factor = smallest_prime_factor[n];
        ++factors[prime_factor];
        n /= prime_factor;
    }
    
    return factors;
}

unordered_map<int, int> get_large_prime_factors(int n) {
    unordered_map<int, int> factors;
    
    int limit = sqrt(n);
    while (n % 2 == 0) {
        ++factors[2];
        n /= 2;
    }
    for (int i = 3; i <= limit; i += 2) {
        while (n % i == 0) {
            ++factors[i];
            n /= i;
        }
    }
    if (n > 1) {
        ++factors[n];
    }
    
    return factors;
}

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(nullptr);
    
    compute_spf(); // Precompute smallest prime factors
    
    int T;
    cin >> T;
    
    while (T--) {
        int a, b;
        cin >> a >> b;
        
        unordered_map<int, int> factors_a;
        if (a <= MAX_N) {
            factors_a = get_prime_factors(a);
        } else {
            factors_a = get_large_prime_factors(a);
        }

        for (auto& factor : factors_a) {
            factor.second *= 2; // Square the exponents for a^2
        }
        
        unordered_map<int, int> factors_b;
        if (b <= MAX_N) {
            factors_b = get_prime_factors(b);
        } else {
            factors_b = get_large_prime_factors(b);
        }
        for (auto& factor : factors_b) {
            factor.second *= 2; // Square the exponents for b^2
        }
        
        for (const auto& factor_b : factors_b) {
            factors_a[factor_b.first] += factor_b.second;
        }
        
        long long result = 1;
        for (const auto& factor : factors_a) {
            result *= 1ll * (factor.second + 1);
        }
        
        cout << result << "\n";
    }
    
    return 0;
}
