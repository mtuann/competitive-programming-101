// Source template from PVH: https://ideone.com/iEeYmj
// Problem: https://usaco.org/index.php?page=viewproblem2&cpid=529

#include <iostream>
#include <vector>
#include <cmath>
#include <cstring>
#define ll long long

#define NMOD 4
const int BASE = 256;
const int MAXN = (int)2e6 + 10;
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
            value[i] = int(c); // - '0';
        }
    }

    Hash operator + (const Hash &other) const {
        Hash res;
        for (int i = 0; i < NMOD; i++) {
            res.value[i] = (1LL * value[i] * BASE + other.value[i]) % MOD[i];
        }
        return res;
    }

    // friend operate + with length of other, param: h1, h2, len
    Hash concat(const Hash &other, int len) const {
        Hash res;
        for (int i = 0; i < NMOD; i++) {
            res.value[i] = (1LL * value[i] * pw[i][len] + other.value[i]) % MOD[i];
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

void solve(char s[], int n) {

    if (n % 2 == 0) {
        cout << "NOT POSSIBLE" << endl;
        return;
    }

    int cnt = 0, ans_index = -1;
    int mid = int(n / 2);
    Hash hash1, hash2;
    // cout << "N: " << n << " mid: " << mid << endl;
    for (int i = 1; i <= n; i++) {
        // remove the ith character, split the string into 2 parts with the length of n / 2
        // find the hash of the first part and the second part
        if (i == mid + 1) {
            hash1 = get_hash(1, mid - 1);
            hash2 = get_hash(mid + 1, n);
        }
        else if (i < mid + 1) {
            hash1 = get_hash(1, i - 1).concat(get_hash(i + 1, mid + 1), mid - i + 1);
            hash2 = get_hash(mid + 2, n);
            // cout << get_hash(1, i - 1).value[0] << " " << get_hash(i + 1, mid + 1).value[0] << " " << get_hash(mid + 2, n).value[0] << endl;
        }
        else if (i > mid + 1) {
            hash1 = get_hash(1, mid);
            hash2 = get_hash(mid + 1, i - 1).concat(get_hash(i + 1, n), n - i);
            //  + get_hash(i + 1, n); n - (i + 1) + 1 
            // cout << get_hash(1, mid).value[0] << " " << get_hash(mid + 1, i - 1).value[0] << " " << get_hash(i + 1, n).value[0] << endl;
        }

        // print hash1 and hash2
        // cout << "hash1: ";
        // for (int i = 0; i < NMOD; i++) {
        //     cout << hash1.value[i] << " ";
        // }
        // cout << endl;
        // cout << "hash2: ";
        // for (int i = 0; i < NMOD; i++) {
        //     cout << hash2.value[i] << " ";
        // }

        if (hash1 == hash2) {
            // cout << "cnt: " << cnt << " i: " << i << endl;
            cnt += 1;
            ans_index = i;
        }
    }
    if (cnt == 0) {
        cout << "NOT POSSIBLE" << endl;
    }
    else if (cnt == 1) {
        int len = 0;
        for (int i = 1; i <= n; i++) {
            if (i == ans_index) continue;
            len += 1;
            cout << s[i - 1];
            if (len == mid) break;
        }
    }
    else {
        cout << "NOT UNIQUE" << endl;
    }

}

int main() {

    scanf("%s", s);
    int n = strlen(s);
    init(s, n);
    solve(s, n);

    return 0;
}
// g++ -std=c++14 -o a cf-hash4.cpp && ./a < a.in