// Problem: https://cses.fi/165/task/B

#include <iostream>
#include <vector>
#include <cmath>
#include <cstring>
#define ll long long

#define NMOD 2
const int BASE = 256;
const int MAXN = (int)1e6 + 10;
const int MOD[] = {(int)1e9 + 2277, (int)1e9 + 5277, (int)1e9 + 8277, (int)1e9 + 9277};
using namespace std;

int pw[NMOD][MAXN];

struct Hash {
    int value[NMOD];
    Hash() {
        memset(value, 0, sizeof(value));
    }

    Hash(char c) {
        for (int i = 0; i < NMOD; i++) {
            value[i] = c;
        }
    }

    Hash operator + (const Hash &other) const {
        Hash res;
        for (int i = 0; i < NMOD; i++) {
            res.value[i] = (1LL * value[i] * BASE + other.value[i]) % MOD[i];
        }
        return res;
    }

    bool operator == (const Hash &other) const {
        for (int i = 0; i < NMOD; i++) {
            if (value[i] != other.value[i]) return false;
        }
        return true;
    }

};

Hash hs[MAXN];

void init(char s[], int n) {
    for (int i = 0; i < NMOD; i++) {
        pw[i][0] = 1;
        for (int j = 1; j < MAXN; j++) {
            pw[i][j] = 1LL * pw[i][j - 1] * BASE % MOD[i];
        }
    }
    for (int i = 1; i <= n; i++) {
        hs[i] = hs[i - 1] + Hash(s[i - 1]);
    }
}


Hash get_hash(int l, int r) {
    Hash res;
    for (int i = 0; i < NMOD; i++) {
        res.value[i] = (hs[r].value[i] - (1LL * hs[l - 1].value[i] * pw[i][r - l + 1] % MOD[i])) % MOD[i];
        if (res.value[i] < 0) res.value[i] += MOD[i];
    }
    return res;
}

char s[MAXN];

void solve(int li, int ri, int& cnt) {
    if (li > ri) {
        return;
    }
    int max_len = ri - li + 1;
    for (int len = 1; len <= max_len; len++) {
        Hash hash_li = get_hash(li, li + len - 1);
        Hash hash_ri = get_hash(ri - len + 1, ri);
        if (hash_li == hash_ri) {
            // cout << li << " " << ri << " " << len << endl;
            if (len != max_len) {
                cnt += 2;
            } else {
                cnt++;
            }
            solve(li + len, ri - len, cnt);
            break;
        }
    }
    
}

int main() {

    int nTest;
    scanf("%d\n", &nTest);
    while (nTest--) {
        scanf("%s\n", s);
        int n = strlen(s);
        init(s, n);
        int ans = 0;
        solve(1, n, ans);
        cout << ans << endl;
        // return 0;
    }
    return 0;
}
// g++ -std=c++14 -o a cses_165B.cpp && ./a < a.in