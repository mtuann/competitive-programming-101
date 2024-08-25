#include <iostream>
#include <vector>
#include <cmath>
#include <cstring>
#define ll long long

using namespace std;
int m, n, d, k;
char s[1010][1010];
int a[1010][1010];
int b[1010][1010];

void sol1000() {

}


int main() {
    freopen("KHUDANCU.INP", "r", stdin);
    freopen("KHUDANCU.OUT", "w", stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> m >> n >> d >> k;

    // if (m > 1000 or n > 1000) {
    //     sol1000();
    //     return 0;
    // }

    for (int i = 1; i <= m; i++) {
        // for (int j = 1; j <= n; j++) {
        //     cin >> s[i][j];
        // }
        cin >> (s[i] + 1);
    }
    // cout << m << " " << n << " " << d << " " << k << endl;
    // for (int i = 1; i <= m; i++) {
    //     // for (int j = 1; j <= n; j++) {
    //     //     cout << s[i][j] << " ";
    //     // }
    //     cout << (s[i] + 1) << endl;
    // }
    memset(a, 0, sizeof(a));
    memset(b, 0, sizeof(b));
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (s[i][j] == 'M') {
                // supermarket
                // update value from range i-d to i+d, j-d to j+d
                int x1 = max(1, i-d);
                int x2 = min(m, i+d);
                int y1 = max(1, j-d);
                int y2 = min(n, j+d);
                b[x1][y1] += 1;
                b[x1][y2+1] -= 1;
                b[x2+1][y1] -= 1;
                b[x2+1][y2+1] += 1;
            }
            if (s[i][j] == 'P') {
                // residential area
            }
        }
    }
    int cnt = 0;
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            a[i][j] = a[i-1][j] + a[i][j-1] - a[i-1][j-1] + b[i][j];
            if (a[i][j] >= k and s[i][j] == 'P') {
                cnt += 1;
                // cout << i << " " << j << endl;
            }
        }
    }
    cout << cnt << endl;

    return 0;
}
// g++ -std=c++14 -o a bvd_khudancu.cpp && ./a < a.in