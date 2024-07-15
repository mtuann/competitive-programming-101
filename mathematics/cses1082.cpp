#include <iostream>
using namespace std;

using ll = long long;
const ll MOD = 1000000007;

// Function to calculate (x^y) % p using Modular Exponentiation
ll power(ll x, ll y, ll p) {
    ll res = 1;
    x = x % p;
    while (y > 0) {
        if (y & 1)
            res = (res * x) % p;
        y = y >> 1;
        x = (x * x) % p;
    }
    return (res + p) % p;
}

// Function to find modular inverse of x under modulo MOD
ll mod_inv(ll x) {
    return power(x, MOD - 2, MOD);
}

// Function to calculate the sum from 1 to n modulo MOD
ll sum(ll n) {
    return (((n % MOD) * ((n + 1) % MOD) % MOD) * mod_inv(2)) % MOD;
}

// Function to calculate the sum of divisors of all numbers from 1 to n
ll divisorSum(ll n) {

    ll ans = 0;

    for (ll l = 1; l <= n;) {
        ll k = n / l;
        ll r = n / k;
        cout << "l: " << l << " r: " << r << " k: " << k << endl;
        k %= MOD;
        
        // For i=l to i=r, floor(n/i) will be k
        ans = (ans + ((sum(r) - sum(l - 1) + MOD) % MOD * k) % MOD) % MOD;
        l = r + 1;
    }

    return ans;
}

int main() {
    ll n;
    std::cin >> n;
    std::cout << divisorSum(n) << endl;
    return 0;
}
// g++ -std=c++14 -o a cses1082.cpp && ./a < a.in
