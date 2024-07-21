// https://codeforces.com/contest/1990/problem/C

#include <iostream>
#include <vector>
#include <cmath>
#include <cstring>
#include <set>
#define ll long long
using namespace std;

const int MAXN = (int)2e5 + 10;

int n;
int a[MAXN];
vector<int> adj[MAXN];

set <int> s;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int nTest;
    cin >> nTest;

    while (nTest--) {
        
        cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        ll ans = 0;
        for (int it = 0; it < 2; it++) {
            vector<bool> was(n + 1, false);

            int mx = 0;
            for (int i = 0; i < n; i++) {
                ans += a[i];
                if (was[a[i]]) {
                    mx = max(mx, a[i]);
                }
                
                was[a[i]] = true;
                a[i] = mx;
                cout << a[i] << " \n"[i == n - 1];
            }
            
        }
        cout << ans << '\n';
        for (int i = 0; i < n; i++) {
            ans += a[i] * 1LL * (n - i);
            cout << a[i] * 1LL * (n - i) << " \n"[i == n - 1];
        }
        cout << ans << '\n';
    }
    return 0;
}
// g++ -o a -std=c++11 1990C.cpp && ./a < a.in