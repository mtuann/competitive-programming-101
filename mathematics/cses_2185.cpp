#include <iostream>
#include <vector>
#include <numeric>  // for std::gcd
using namespace std;
typedef long long ll;

ll gcd(ll a, ll b) {
    while (b != 0) {
        a %= b;
        swap(a, b);
    }
    return a;
}

// Function to calculate lcm of two numbers
ll lcm(ll a, ll b) {
    return (a / gcd(a, b)) * b;
}

int main() {
    ll n;
    int k;
    cin >> n >> k;
    
    vector<ll> primes(k);
    for (int i = 0; i < k; ++i) {
        cin >> primes[i];
    }
    
    ll result = 0;
    
    // Loop over all subsets of primes (2^k subsets)
    for (int mask = 1; mask < (1 << k); ++mask) {
        ll lcm_val = 1;
        int bits = 0;
        
        // For each bit in the mask, check which primes are selected
        for (int i = 0; i < k; ++i) {
            if (mask & (1 << i)) {
                lcm_val = lcm(lcm_val, primes[i]);
                // If LCM exceeds n, break early to avoid overflow
                if (lcm_val > n) break;
                bits++;
            }
        }
        
        if (lcm_val > n) continue;
        
        // Apply inclusion-exclusion principle
        ll multiples = n / lcm_val;
        if (bits % 2 == 1) {
            result += multiples;  // Include
        } else {
            result -= multiples;  // Exclude
        }
    }
    
    cout << result << endl;
    return 0;
}
