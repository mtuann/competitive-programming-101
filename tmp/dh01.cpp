#include <iostream>
using namespace std;

const int MOD = 1e9 + 7;
int n, k, d;
int a[1000001];
int del[1000001];
int dp[1000001], cnt[1000001];
int main() {
    cin >> n >> k >> d;
    memset(del, 0, sizeof(del));
    for (int i = 1; i <= k; ++i) {
        int u;
        cin >> u;
        del[u] = 1;
    }
    int nn = 0;
    for (int i = 1; i <= n; ++i) {
        if (del[i] == 0)
            a[++nn] = i;
    }
    for (int i = 1; i <= nn; ++i) {
        cout << a[i] << " \n"[i == nn];
    }

    dp[0] = 0;
    cnt[0] = 1;
    a[0] = 0;
    for (int i = 1; i <= nn; ++i) {
        dp[i] = 1;
        cnt[i] = 1;
        for (int j = 0; j <= i; ++j) {
            if (a[i] - a[j] <= d)
                continue;
            if (dp[i] < dp[j] +  1) {
                dp[i] = dp[j] + 1;
                cnt[i] = cnt[j];
            } else if (dp[i] == dp[j] + 1) {
                cnt[i] += cnt[j];
            }
            cnt[i] %= MOD;    
        }
    }
    int max_dp = 0, cnt_max = 0;
    for (int i = 1; i <= nn; ++i) {
        if (dp[i] > max_dp) {
            max_dp = dp[i];
            cnt_max = cnt[i];
        } else if (dp[i] == max_dp) {
            cnt_max += cnt[i];
            cnt_max %= MOD;
        }
    }
    cout << max_dp << " " << cnt_max << endl;

    return 0;
}

// g++ -std=c++14 -o a dh01.cpp && ./a < a.in

