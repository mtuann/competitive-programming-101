#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <unordered_set>
#include <numeric>
#include <map>
#define ll long long
#define pii pair<int, int>
#define fi first
#define se second
using namespace std;


const int MAXN = 1e6 + 10;
unordered_set<int> b;
int chon[MAXN];
ll ans = 0;

namespace sub1_3 {
    void solve(int l, int r) {

        for (int i = 1; i * i <= MAXN; i++) {
            for (int j = i; j < MAXN; j += i) {
                if (l <= j && j <= r) {
                    if (chon[i] == 0) {
                        ans += i;
                        chon[i] = 1;
                    }
                    if (chon[j / i] == 0 && i * i != j) {
                        ans += j / i;
                        chon[j / i] = 1;
                    }
                }
            }
        }
        cout << ans << endl;
    }
}
namespace sub2 {
    void solve(int l, int r) {
        for (int i = l; i <= r; i++) {
            for (int k = 1; k * k <= i; k++) {
                if (i % k == 0) {
                    if (b.find(k) == b.end()) {
                        ans += k;
                        b.insert(k);
                    }
                    if (b.find(i / k) == b.end()) {
                        ans += i / k;
                        b.insert(i / k);
                    }
                }
            }
        }
        cout << ans << endl;
    }
}

int main() {
    int l, r;
    cin >> l >> r;
    if (r <= 1e6) {sub1_3::solve(l, r); return 0;}
    else {sub2::solve(l, r); return 0;}
    return 0;
}

//  g++ -std=c++11 -O2 -Wall hn21_p1_brute.cpp -o a && ./a < a.in