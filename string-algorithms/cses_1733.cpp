// Problem: https://usaco.org/index.php?page=viewproblem2&cpid=529

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

void solve(int n, char s[]) {
    for (int i = 1; i <= n; i++) {
        bool ok = true;
        for (int j = i; j <= n; j += i) {
            // cout << i << " " << j << endl;
            // xet tu ki tu j + 1 den ki tu n
            int max_len = min(i, n - j);
            Hash h1 = get_hash(1, max_len);
            Hash h2 = get_hash(j + 1, j + max_len);
            // cout << h1.value[0] << " " << h2.value[0] << endl;
            if (!(h1 == h2)) {
                ok = false;
                break;
            }
        }

        if (ok) {
            cout << i << " ";
        }
    }
}

int main() {

    scanf("%s", s);
    int n = strlen(s);
    init(s, n);
    solve(n, s);

    return 0;
}
// g++ -std=c++14 -o a cses_1733.cpp && ./a < a.in