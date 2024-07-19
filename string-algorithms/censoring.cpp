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

char s[MAXN];
char t[MAXN];
char res[MAXN];

Hash get_hash(int l, int r) {
    Hash res;
    for (int i = 0; i < NMOD; i++) {
        res.value[i] = (hs[r].value[i] - (1LL * hs[l - 1].value[i] * pw[i][r - l + 1] % MOD[i])) % MOD[i];
        if (res.value[i] < 0) res.value[i] += MOD[i];
    }
    return res;
}

void solve(int n, int m, char s[], char t[]) {
    Hash ht;
    for (int i = 0; i < m; i++) {
        ht = ht + Hash(t[i]);
        // cout << Hash(t[i]).value[0] << " ";
    }

    int cur_len = 0;
    for (int i = 0; i < n; i++) {
        hs[cur_len + 1] = hs[cur_len] + Hash(s[i]);
        res[cur_len] = s[i];
        cur_len++;

        if (cur_len < m) continue;
        
        Hash cur_hs = get_hash(cur_len - m + 1, cur_len);
        // cout << cur_len << " " << cur_hs.value[0] << "\n";
        if (cur_hs == ht)  cur_len -= m;

    }

    for (int i = 0; i < cur_len; i++) {
        cout << res[i];
    }

}

int main() {
    freopen("censor.in", "r", stdin);
    freopen("censor.out", "w", stdout);

    scanf("%s", s);
    int n = strlen(s);
    init(s, n);
    scanf("%s", t);
    int m = strlen(t);
    solve(n, m, s, t);

    return 0;
}
// g++ -std=c++14 -o a censoring.cpp && ./a < a.in