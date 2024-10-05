#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e6 + 1;
int div_count[MAXN];  // div_count[i] will store the number of divisors of i

// Precompute the number of divisors for every integer from 1 to MAXN-1
void precompute_divisors() {
    // Initialize divisor counts to zero
    for (int i = 1; i < MAXN; i++) {
        for (int j = i; j < MAXN; j += i) {
            div_count[j]++;
        }
    }
    // Time complexity: O(N log N) N * (1 + 1/2 + 1/3 + ... + 1/N) = O(N log N)
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    precompute_divisors();  // Precompute divisors count for all numbers up to MAXN-1

    int n;
    cin >> n;
    
    // Process each query
    while (n--) {
        int x;
        cin >> x;
        cout << div_count[x] << "\n";  // Output the number of divisors for x
    }

    return 0;
}
