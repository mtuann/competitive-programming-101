#include <iostream>
#include <vector>

const int MOD = 1e9 + 7;

typedef std::vector<std::vector<long long>> Matrix;

// Function to multiply two 2x2 matrices with modulo operation
Matrix multiply(const Matrix& a, const Matrix& b) {
    Matrix result(2, std::vector<long long>(2));
    result[0][0] = (a[0][0] * b[0][0] + a[0][1] * b[1][0]) % MOD;
    result[0][1] = (a[0][0] * b[0][1] + a[0][1] * b[1][1]) % MOD;
    result[1][0] = (a[1][0] * b[0][0] + a[1][1] * b[1][0]) % MOD;
    result[1][1] = (a[1][0] * b[0][1] + a[1][1] * b[1][1]) % MOD;
    return result;
}

// Function to perform matrix exponentiation
Matrix power(Matrix a, long long n) {
    Matrix result = {{1, 0}, {0, 1}};  // Identity matrix
    while (n > 0) {
        if (n % 2 == 1) {
            result = multiply(result, a);
        }
        a = multiply(a, a);
        n /= 2;
    }
    return result;
}

int main() {
    long long n;
    std::cin >> n;
    
    if (n == 0) {
        std::cout << 0 << std::endl;
        return 0;
    }
    if (n == 1) {
        std::cout << 1 << std::endl;
        return 0;
    }
    
    // Base transformation matrix
    Matrix F = {{1, 1}, {1, 0}};
    
    // Compute F^n
    Matrix result = power(F, n - 1);
    
    // F_n is located at result[0][0]
    std::cout << result[0][0] << std::endl;
    
    return 0;
}
