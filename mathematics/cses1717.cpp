#include <iostream>
#include <vector>

const int MOD = 1e9 + 7;

int countDerangements(int n) {
    // Base cases
    if (n == 1) return 0;
    if (n == 2) return 1;
    
    // Vector to store the number of derangements for each number up to n
    std::vector<long long> derangements(n + 1);
    derangements[0] = 1; // !0 = 1
    derangements[1] = 0; // !1 = 0
    
    for (int i = 2; i <= n; ++i) {
        derangements[i] = (i - 1) * (derangements[i - 1] + derangements[i - 2]) % MOD;
    }
    
    return derangements[n];
}

int main() {
    int n;
    std::cin >> n;
    std::cout << countDerangements(n) << std::endl;
    return 0;
}

// The problem at hand involves calculating the number of ways to distribute gifts such that each child receives a gift brought by another child. This is a classic problem in combinatorics, specifically involving derangements (permutations where no element appears in its original position).

// To solve this problem, we need to compute the number of derangements of \( n \) items, often denoted as \( !n \). The number of derangements can be computed using the following recursive formula:
// \[ !n = (n - 1) \times (!(n - 1) + !(n - 2)) \]
// with the base cases:
// \[ !0 = 1 \]
// \[ !1 = 0 \]

// Given the constraint \( 1 \le n \le 10^6 \), we need an efficient way to compute derangements up to \( 10^6 \). This can be achieved using dynamic programming to avoid recalculating values multiple times.

