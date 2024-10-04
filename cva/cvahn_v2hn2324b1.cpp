#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;

ll N, K, X, D;

// Function to compute the total count of numbers with remainders from 'a' to 'b'
ll count_remainders(ll N, ll K, ll a, ll b, ll cycles, ll rem) {
    if (a > b) return 0;
    ll num_rems = b - a + 1;

    // Number of remainders with count cycles + 1
    ll num_r_plus = 0;
    if (rem >= a && rem <= b) {
        num_r_plus = rem - a + 1;
    } else if (rem > b) {
        num_r_plus = num_rems;
    }

    // Number of remainders with count cycles
    ll num_r = num_rems - num_r_plus;

    ll total_count = num_r_plus * (cycles + 1) + num_r * cycles;
    return total_count;
}

// Function to find the D-th element in the sorted sequence
ll find_dth_element() {
    ll cycles = N / K;
    ll rem = N % K;

    // Total counts in each section
    ll S1 = count_remainders(N, K, X, K - 1, cycles, rem);
    ll S0 = count_remainders(N, K, 0, 0, cycles, rem);
    ll S2 = count_remainders(N, K, 1, X - 1, cycles, rem);

    if (D <= S1) {
        // D lies in remainders from X to K - 1
        // ll num_rems = K - X;
        ll num_r_plus = 0;
        if (rem >= X) num_r_plus = rem - X + 1;

        ll cnt_cycles_plus1 = num_r_plus * (cycles + 1);
        if (D <= cnt_cycles_plus1) {
            // D lies in remainders with cycles + 1
            ll r = X + (D - 1) / (cycles + 1);
            ll pos_in_group = (D - 1) % (cycles + 1);
            ll num = r + K * (cycles - pos_in_group);
            return num;
        } else {
            // D lies in remainders with cycles
            ll D_remaining = D - cnt_cycles_plus1;
            // ll num_r_cycles = num_rems - num_r_plus;
            ll r = X + num_r_plus + (D_remaining - 1) / cycles;
            ll pos_in_group = (D_remaining - 1) % cycles;
            ll num = r + K * (cycles - 1 - pos_in_group);
            return num;
        }
    } else if (D <= S1 + S0) {
        // D lies in remainder 0
        ll D_in_S0 = D - S1;
        ll count_r0 = (rem >= 0) ? cycles + 1 : cycles;
        ll pos_in_group = D_in_S0 - 1;
        ll num = 0 + K * (count_r0 - 1 - pos_in_group);
        return num;
    } else if (D <= S1 + S0 + S2) {
        // D lies in remainders from 1 to X - 1
        ll D_in_S2 = D - S1 - S0;
        // ll num_rems = X - 1;
        ll num_r_plus = 0;
        if (rem >= 1) num_r_plus = min(rem, X - 1);

        ll cnt_cycles_plus1 = num_r_plus * (cycles + 1);
        if (D_in_S2 <= cnt_cycles_plus1) {
            // D lies in remainders with cycles + 1
            ll r = 1 + (D_in_S2 - 1) / (cycles + 1);
            ll pos_in_group = (D_in_S2 - 1) % (cycles + 1);
            ll num = r + K * (cycles - pos_in_group);
            return num;
        } else {
            // D lies in remainders with cycles
            ll D_remaining = D_in_S2 - cnt_cycles_plus1;
            // ll num_r_cycles = num_rems - num_r_plus;
            ll r = 1 + num_r_plus + (D_remaining - 1) / cycles;
            ll pos_in_group = (D_remaining - 1) % cycles;
            ll num = r + K * (cycles - 1 - pos_in_group);
            return num;
        }
    } else {
        // D is out of bounds
        return -1;
    }
}

int main() {
    freopen("DCH.inp", "r", stdin);
    freopen("DCH.out", "w", stdout);
    int Q;
    cin >> Q;  // Number of queries
    while (Q--) {
        cin >> N >> K >> X >> D;

        // Adjust X if necessary (since remainders are modulo K)
        X %= K;

        ll result = find_dth_element();
        cout << result << endl;
    }
    return 0;
}

// g++ -std=c++11 -O2 -Wall cvahn_v2hn2324b1.cpp -o a && ./a < a.in
