#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <cstring>

#define ll long long
using namespace std;
const int MAXN = 1e5 + 5;
vector<ll> bit[MAXN];
int n;

ll get_sum(int l, int x) {
    ll ans = 0;
    for (int idx = x; idx > 0; idx -= idx & (-idx)) {
        ans += bit[l][idx];
    }
    return ans;
}

void update(int l, int x, long long v) {
    for (int idx = x; idx < MAXN; idx += idx & (-idx)) {
        bit[l][idx] += v;
    }
}

int main() {
    int temp, k;
    ll kq = 0;
    cin >> n >> k;
    // cout << n << " " << k << endl;
    for (int i = 1; i <= k+2; i++) bit[i].resize(MAXN);

    k++;

    for (int i = 0; i < n; i++) {
        cin >> temp;
        update(1, temp, 1);
        for (int l = 2; l <= k; ++l) {
            ll m = get_sum(l-1, temp-1);
            // cout << i << " " << l << " " << m << endl;
            update(l, temp, m);
        }
        // kq += get_sum(k, temp);
        // cout << "Get: " << get_sum(k, temp) << endl;
        // cout << "---\n";
        
    }
    cout << get_sum(k, n) << endl;
    return 0;
}

// g++ -std=c++17 -o a 597C.cpp && ./a < a.in