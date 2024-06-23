#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <cstring>
#define ll long long
using namespace std;

const int MAXN = 1e5 + 10;
const int sai = 1e6;
ll mintemp, maxtemp;
int f[MAXN];
int g[MAXN];
int a[MAXN];
ll n, s, l;
ll stmin[4*MAXN], stmax[4*MAXN], stf[4*MAXN];

void build(int id, int l, int r) {
    if (l == r) {
        stmin[id] = a[l];
        stmax[id] = a[l];
        return;
    }
    int mid = (l + r) / 2;
    build(id * 2, l, mid);
    build(id * 2 + 1, mid+1, r);
    stmin[id] = min(stmin[id*2], stmin[id*2+1]);
    stmax[id] = max(stmax[id*2], stmax[id*2+1]);
}
void getminmax(int id, int u, int v, int l, int r) {
    if (l >= u && r <= v) {
        mintemp = min(mintemp, stmin[id]);
        maxtemp = max(maxtemp, stmax[id]);
        return;
    }
    if (l > v || r < u) return;
    int mid = (l + r) / 2;
    getminmax(id * 2, u, v, l, mid);
    getminmax(id * 2 + 1, u, v, mid + 1, r);
}
int getf(int id, int u, int v, int l, int r) {
    if (l >= u && r <= v) {
        //cout << l << " " << r << " " << stf[id] << endl;
        //if (u == 4 && v == 4) cout << u << " " << stf[id];
        return stf[id];
    }
    if (l > v || r < u) return sai;
    int mid = (l + r) / 2;
    return min(getf(id * 2, u, v, l, mid), getf(id * 2 + 1, u, v, mid+1, r));
}
void update(int id, int k, int l, int r) {
    if (l > k || r < k) return;
    if (l == r) {
        stf[id] = f[k];
        //if (k == 4) cout << k << " " << stf[id] << endl;
        //cout << k << endl;
        return;
    }

    int mid = (l + r) / 2;
    update(id * 2, k, l, mid);
    update(id * 2 + 1, k, mid+1, r);
    stf[id] = min(stf[id * 2], stf[id * 2 + 1]);
}


int main() {

    cin >> n >> s >> l;
    for (int i = 1; i <= n; i++) cin >> a[i];
    build(1, 1, n);
    int vt = n;
    maxtemp = -1e9;
    mintemp = 1e9;
    for (int i = n; i >= 1; i--) {
        if (vt == i && vt > 0) vt--;
        getminmax(1, vt, i, 1, n);
        while (maxtemp - mintemp <= s && vt > 0) {
            //cout << mintemp << " " << maxtemp << " " << vt << endl;
            vt--;
            getminmax(1, vt, i, 1, n);
        }
        maxtemp = -1e9;
        mintemp = 1e9;
        g[i] = i - vt;
    }

    // for (int i = 1; i <= n; ++i) cout << g[i] << " ";
    // cout << endl;

    // for (int i = 1; i <= n; ++i) cout << i - g[i] + 1 << " ";
    // cout << endl;

    fill(stf, stf + 4 * MAXN, 1e6);
    memset(f, 0, sizeof(f));
    f[1] = 0;
    f[0] = 0;
    build(1, 1, n);
    for (int i = 1; i <= n; i++) {
        int minf;
        // int lll = i - g[i] + 1;
        // // mean tu [lll, i] la doan thoa man dieu kien
        // // chon dc cac gia tri tu [lll - 1, i - l]
        // if (i > l) {
        //     if (lll - 1 >= 1) {
        //         minf = getf(1, lll - 1, i - l, 1, n);
        //         f[i] = min(sai, minf + 1);
        //     } else {
        //         // lll = 1
        //         f[i] = 1;
        //     }
        // } else {
        //     if (i == l && lll == 1) f[i] = 1;
        //     else f[i] = sai;
        // }

        if (i - l >= 1 && i - g[i] >= 1) {
            // co doan truoc do, va do dai doan g[i] > 0
            minf = getf(1, i - g[i], i - l, 1, n);
            // cout << i << " " << "Run 1" << " " << minf << endl;
            // if (minf == sai) f[i] = f[i-1] + 1; // why cap nhat nay, cap nhat no voi minf + 1, sai
            // else f[i] = minf + 1;
            f[i] = min(minf + 1, sai);
        }
        else  {
            // xet tan 3 truong hop
            if (i < l) {
                f[i] = sai;
            } else if (i == l) {
                if (g[i] >= l) f[i] = 1;
                else f[i] = sai;
            } else {
            //    i > l && i - g[i] < 1 hay g[i] = i;
                f[i] = 1;
            }
            // khong co doan truoc do, hoac do dai doan g[i] = 0
            // dieu kien ko dung, chia ko ro rang
            // cout << i << " " << "Run 2" << endl;

            // minf = getf(1, 1, i-1, 1, n);
            // // chua chac la doan dung, chi la doan dung khi ma length >= l;
            // // viec gan f[i] voi g[i] >= i la sai cho cac update sau
            // // chi gan khi i >= l va doan trc do co gia tri != sai
            
            // if (g[i] >= i) f[i] = 1;
            // else f[i] = minf + 1;
        }

        // if (minf == sai && n-i+1 < l) {
        //     // Ko can set vi lan sau se gap
        //     cout << -1;
        //     exit(0);
        // }

        // else if (minf == sai && g[i + l - 1] < l) {
        //     // Ko can set vi lan sau se gap
        //     cout << -1;
        //     exit(0);
        // }
        // cout << i << " " << f[i] << endl;

        update(1, i, 1, n);
        //cout << i << " " << i-g[i] << " " << i - l << " " << minf << " " << f[i] << endl;
        
    }
    if (f[n] == sai) cout << -1 << '\n';
    else cout << f[n] << '\n';
}

// g++ -std=c++17 -o a 487B.cpp && ./a < a.in