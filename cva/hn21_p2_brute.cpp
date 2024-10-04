#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <numeric>
#include <ctime>
#define pii pair<int, int>
#define ll long long
using namespace std;

const int MAXN = 2e3 + 10;
const int MAXK = 1e6 + 10;
ll que[MAXK];
int n;
vector<ll> a;
bool thoaman(ll i, ll j, ll  k) {
    ll i2 = i * i, j2 = j * j, k2 = k * k;
    if (i2 + j2 <= k2) return 0;
    return 1;
}

void solve() {
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        ll l, c;
        cin >> l >> c;
        que[l] = c;
        a.push_back(l);
    }
    sort(a.begin(), a.end());
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            for (int k = j + 1; k < n; k++) {
                int x = a[i], y = a[j], z = a[k];
                if (thoaman(x, y, z)) {
                    ans += 1ll * que[x] * que[y] * que[z];
                    cout << x << " " << y << " " << z << " " << que[x] << " " << que[y] << " " << que[z] << " " << 1ll * que[x] * que[y] * que[z] << endl;
                }
            }
        }
    }
    cout << ans;
}

int main() {
    cin >> n;
    solve();
}
