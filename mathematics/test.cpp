#include <iostream>
#include <vector>
#include <cmath>
#define ll long long
#define pii pair<int, int>
#define fi first
#define se second

using namespace std;
const int inf = 1e9 + 7;
const int MAXN = 1e7 + 7;
const int MAXK = 1e5 + 7;
const int MAXSUB2 = 2e2 + 10;
const int MOD = 1e9 + 7;
ll dp[MAXSUB2][MAXSUB2];
int n, k, d, sl;
int b[MAXN];
vector<int> a;
namespace sub12 {
    bool check() {
        if (n - k <= 2e2 + 10) return 1;
        return 0;
    }
    void solve() {
        for (int i = 0; i < sl; i++) dp[i][1] = 1;
        dp[1][1] = 1;
        for (int i = 1; i <= sl; i++) {
            for (int j = 1; j < sl; j++) {
                for (int k = j - 1; k >= 0; k--) {
                    if (a[j] - a[k] > d) {
                        dp[j][i] = (dp[j][i] + dp[k][i-1]) % MOD;
                    }
                }
            }
        }
        for (int i = sl; i >= 0; i--) {
            ll temp = 0;
            for (int j = 0; j < sl; j++) {
                temp = (temp + dp[j][i]) % MOD;
            }
            if (temp > 0) {
                cout << i << endl << temp;
                return;
            }
        }
    }
}
int main() {
    cin.tie(0)->sync_with_stdio(0);
    memset(dp, 0, sizeof(dp));
    cin >> n >> k >> d;
    sl = n-k;
	// memset(b, 0, sizeof(b));
    for (int i = 0; i < k; i++) {
        int x;
        cin >> x;
        b[x] = 1;
		cout << x << endl;
    }
    for (int i = 1; i <= n; i++) {
        if (b[i] == 0) {
			a.push_back(i);
			// cout << i << endl;
		}
    }
	cout << sl << " " << int(a.size()) << endl;
    if (sub12::check() == 1) {sub12::solve(); return 0;}
    return 0;
}

// g++ -std=c++14 -o a test.cpp && ./a < a.in

