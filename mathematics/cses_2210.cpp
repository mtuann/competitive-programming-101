#include <iostream>
using namespace std;

const int MOD = 1e9 + 7;

// Function to compute (base^exp) % mod using modular exponentiation
long long mod_pow(long long base, long long exp, long long mod) {
    long long result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

int main() {
    long long n;
    cin >> n;

    // Total number of grids without considering rotations is 2^(n^2)
    long long total_grids = mod_pow(2, n * n, MOD);

    // Now, we use Burnside's Lemma to calculate distinct grids.
    // For 0 degree rotation, all grids are unchanged.
    long long unchanged_0 = total_grids;

    // For 180 degree rotation, the grid must be symmetric around the center
    // If n is even, half the cells are free to choose, because each symmetric pair must be the same.
    // If n is odd, the center cell is independent, but all other cells are paired symmetrically.
    long long unchanged_180 = mod_pow(2, (n * n + 1) / 2, MOD);

    // For 90 and 270 degree rotations, the number of unchanged grids depends on the grid size.
    // If n % 2 != 0, no grid can remain unchanged under 90-degree rotation.
    // If n % 2 == 0, we have to calculate based on symmetric quadrants.

    long long unchanged_90 = 0;
    long long unchanged_270 = 0;

    if (n % 2 == 0) {
        unchanged_90 = mod_pow(2, (n / 2) * (n / 2), MOD);
        unchanged_270 = unchanged_90;
    }

    // Burnside's Lemma
    long long distinct_grids = (unchanged_0 + unchanged_180 + unchanged_90 + unchanged_270) % MOD;
    distinct_grids = (distinct_grids * mod_pow(4, MOD - 2, MOD)) % MOD; // Divide by 4 (modular inverse of 4)

    // Output the result
    cout << distinct_grids << endl;

    return 0;
}
