#include <iostream>
#include <vector>
#include <cmath>
 
const int MOD = 1000000007;
 
// Hàm tính mũ modulo
long long fast_pow(long long base, long long exp, long long mod=MOD) {
    long long result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = result * base % mod;
        }
        base = base * base % mod;
        exp /= 2;
    }
    return result;
}
 
// Hàm tính số lượng các ước
long long count_divisors(const std::vector<std::pair<int, int>>& factors) {
    long long count = 1;
    for (const auto& factor : factors) {
        count = count * (factor.second + 1) % MOD;
    }
    return count;
}
 
// Hàm tính tổng các ước
long long sum_of_divisors(const std::vector<std::pair<int, int>>& factors) {
    long long sum = 1;
    for (const auto& factor : factors) {
        int p = factor.first;
        int e = factor.second;
        long long term_sum = (fast_pow(p, e + 1) - 1 + MOD) % MOD * fast_pow(p - 1, MOD - 2, MOD) % MOD;
        sum = sum * term_sum % MOD;
    }
    return sum;
}
 
// Hàm tính tích các ước
// Function to calculate the product of all divisors of a number given its prime factorization
long long product_of_divisors(const std::vector<std::pair<int, int>>& factors) {
    long long product = 1;
    long long N = 1;
    long long total_divisors = 1, half_divisor = 1;
    long long sqrt_N = 1;
    bool is_square = false;
 
    // Calculate N from the prime factorization
    for (const auto& factor : factors) {
        int prime = factor.first;
        int exponent = factor.second;
 
        long long prime_power = fast_pow(prime, exponent);
 
        // Multiply to get N
        N = (N * prime_power) % MOD;
        
        // Compute total number of divisors
        total_divisors = (total_divisors * (exponent + 1) ) % (MOD - 1);
        
        // Check if the exponent is even
        if (exponent % 2 == 1) {
            if (!is_square) {
                half_divisor = (half_divisor * ((exponent + 1) / 2) ) % (MOD - 1);
            } else {
                half_divisor = (half_divisor * (exponent + 1) ) % (MOD - 1);
            }
            is_square = true;
        } else {
            half_divisor = (half_divisor * (exponent + 1) ) % (MOD - 1);
        }

        sqrt_N = (sqrt_N * fast_pow(prime, exponent / 2) % MOD) % MOD;

        
    }
    // 2 cases
    // is square then kq = 
    // std::cout << "is_square: " << is_square << std::endl;
    // std::cout << half_divisor << " " << total_divisors << " " << sqrt_N << std::endl;
    if (!is_square) {
        product = fast_pow(sqrt_N, total_divisors);
    } else {
        product = fast_pow(N, half_divisor);
    }
 
    return product;
}
 
 
 
int main() {
    int n;
    std::cin >> n;
    std::vector<std::pair<int, int>> factors(n);
    for (int i = 0; i < n; ++i) {
        int x, k;
        std::cin >> x >> k;
        factors[i] = {x, k};
    }
 
    long long num_divisors = count_divisors(factors);
    long long sum_divisors = sum_of_divisors(factors);
    long long prod_divisors = product_of_divisors(factors);
 
    std::cout << num_divisors << " " << sum_divisors << " " << prod_divisors << std::endl;
 
    return 0;
}

// g++ -std=c++14 -o a test.cpp && ./a < a.in