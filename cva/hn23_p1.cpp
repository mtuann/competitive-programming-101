#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#define ll long long
#define pii pair<int, int>
#define fi first
#define se second
using namespace std;
int n;
int sptmax = 0;
int l = -1, r, dd;

// void update(int& l, int& r, int& dd, int& sptmax, int u1, int mink, int p) {
//     l = u1;
//     r = u1 + mink * (p - 1);
//     dd = mink;
//     sptmax = p;
// }

void process(int p, int sum) {
    // cout << p << " " << sum << " " << sum % p << endl;
    int tbc = sum / p;
    if (p % 2 == 1) {
        // 1 4 7; tbc = 4
        int lv = p / 2; // ll = 1
        // find k that tbc - k * ll > 0
        int mink = (tbc - 1) / lv;
        if (mink <= 0) return;
        int u1 = tbc - mink * lv;
        // cout << lv << " " << u1 << " " << mink << endl;
        // return;
        if (u1 < 1) return;
        
        if (p > sptmax) {
            sptmax = p;
            l = u1;
            r = u1 + mink * (p - 1);
            dd = mink;
        } else if (p == sptmax) {
            if (u1 < l) {
                l = u1;
                r = u1 + mink * (p - 1);
                dd = mink;
            }
        }
    } else {
        if (sum % p) {
            // cout << "ppppp = " << p << " sum = " << sum << endl;
            // 1 6 11 16; tbc = 8.5
            int lv = p / 2; // kk = lv - 0.5; tbc - (kk * mink >= 1)
            int mink = double( (double)sum/p - 1) / double(double(lv) - 0.5); // 7.5 / 1.5 = 5;
            // cout << double( (double)sum/p - 1) << " " << double(double(lv) - 0.5) << endl;
            // cout << "mink = " << mink << endl;
            
            // cout << double(tbc - 1) << double(double(lv) - 0.5) << endl;
             // 7.5 / 1.5 = 5;
            // cout << "lv = " << lv << " mink = " << mink << endl;
            // if (mink <= 0) return;
            if (mink % 2 == 0) mink -= 1;
            if (mink <= 0) return;
            int u1 = double((double)sum/p) - mink * ((double)lv - 0.5);
        
            if (u1 < 1) return;
            if (p > sptmax) {
                sptmax = p;
                l = u1;
                r = u1 + mink * (p - 1);
                dd = mink;
            } else if (p == sptmax) {
                if (u1 < l) {
                    l = u1;
                    r = u1 + mink * (p - 1);
                    dd = mink;
                }
            }
        } else {
            // cout << "TBC = " << tbc << endl;
            // 2 4 6 8
            // 1 3 5 7
            // tbc = 3; 12, p 0 2 4 6
            int lv = p / 2; // kk = lv - 0.5; tbc - (kk * mink >= 1)
            int mink = double(tbc - 1) / double(double(lv) - 0.5); // 7.5 / 1.5 = 5;
            
            if (mink <= 0) return;
            // cout << "mink = " << mink << endl;
            int u1;
            if (mink % 2 == 1) {
                mink += 1;
                u1 = tbc - mink * ((double)lv - 0.5);
                if (u1 < 1 && mink > 2) mink -= 2;
            }
            // u1 = tbc - mink * ((double)lv - 0.5);
            u1 = tbc - mink * ((double)lv - 0.5);
            if (u1 < 1) return;

            if (p > sptmax) {
                sptmax = p;
                l = u1;
                r = u1 + mink * (p - 1);
                dd = mink;
            } else if (p == sptmax) {
                if (u1 < l) {
                    l = u1;
                    r = u1 + mink * (p - 1);
                    dd = mink;
                }
            }
        }
    }
}


void process2(int p, int sum) {
    for (int u1 = 1; u1 <= sum; ++u1) {
        int up = (sum * 2) / p - u1;
        if (up <= u1) continue;
        if ( (up - u1) % ( p - 1 ) != 0) continue;
        // cout << "u1: " <<  u1 << " " << up << endl;
        if (sptmax < p) {
            sptmax = p;
            l = u1;
            r = up;
            dd = (up - u1) / (p - 1);
        } else if (sptmax == p) {
            if (u1 < l) {
                l = u1;
                r = up;
                dd = (up - u1) / (p - 1);
            }
        }
    }
}

int main() {
    freopen("DCD.INP", "r", stdin);
    freopen("DCD.OUT", "w", stdout);
    cin.tie(0)->sync_with_stdio(0);
    // cin >> n;
    for (int ii = 1000304; ii < 1000304 + 1; ++ii) {
        cin >> n;
        // n = ii;
        // cout << "N = " << n << endl;

    
    sptmax = 0;
    l = -1;
    r = 0;
    dd = 0; 
    for (int num = 3; num * num <= 2 * n; ++num) {
        // if (num != 808) {
        //     continue;
        // }
        if (2 * n % num != 0) continue;

        // cout << num << endl;

        int num1 = num;
        int num2 = 2 * n / num;

        process(num1, n);
        process(num2, n);

    }
    // int ans1 = l;
    if (l == -1) {
        cout << "-1\n";
        // return 0;
    } else {
        // cout << sptmax << " " << l << " " << r << " " << dd << endl;
        for (int u1 = l; u1 <= r; u1 += dd) cout << u1 << " ";
        // cout << endl;
        // cout << endl;
    }
    // cout << l << " " << r << endl;
    // return 0;
    

    // sptmax = 0;
    // l = -1;
    // r = 0;
    // dd = 0;
    // for (int num = 3; num * num <= 2 * n; ++num) {
    //     if (2 * n % num != 0) continue;
    //     // cout << num << endl;
    //     int num1 = num;
    //     int num2 = 2 * n / num;

    //     process2(num1, n);
    //     process2(num2, n);

    // }
    // int ans2 = l;
    // if (ans1 != ans2) {
    //     cout << "DIFFERENT" << " n = " << n << endl;
    //     cout << ans1 << " " << ans2 << endl;
    //     // return 0;
    // }
    // if (l == -1) {
    //     cout << "-1";
    //     // return 0;
    // } else {
    //     cout << sptmax << " " << l << " " << r << " " << dd << endl;
    //     for (int u1 = l; u1 <= r; u1 += dd) cout << u1 << " ";
    //     cout << endl;
    //     cout << endl;
    // }
    // break;
    }
    

    return 0;
}


// g++ -std=c++11 -O2 -Wall hn23_p1.cpp -o a && ./a < a.in