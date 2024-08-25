    // Source template from PVH: https://ideone.com/iEeYmj
    // Problem: https://usaco.org/index.php?page=viewproblem2&cpid=529

    #include <iostream>
    #include <vector>
    #include <cmath>
    #include <cstring>
    #define ll long long

    #define NMOD 4
    const int BASE = 256;
    const int MAXN = (int)6e5 + 10;
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
                value[i] = int (c); //c - '0';
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
                res.value[i] = (1LL * value[i] * pw[i][len]  % MOD[i] + other.value[i]) % MOD[i];
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

    Hash hs[MAXN], ht[MAXN];

    void init(char s[], char t[], int n) {
        for (int i = 0; i < NMOD; i++) {
            pw[i][0] = 1;
            for (int j = 1; j < MAXN; j++) {
                pw[i][j] = 1LL * pw[i][j - 1] * BASE % MOD[i];
            }
        }
        for (int i = 1; i <= n; i++) {
            hs[i] = hs[i - 1] + Hash(s[i - 1]);
        }
        for (int i = 1; i <= n; i++) {
            ht[i] = ht[i - 1] + Hash(t[i - 1]);
        }
    }

    int n;
    char s[MAXN];
    char t[MAXN];
    char res[MAXN];

    Hash get_hash(int l, int r, Hash hs[]) {
        Hash res;
        if (l > r) return res;
        for (int i = 0; i < NMOD; i++) {
            res.value[i] = (hs[r].value[i] - (1LL * hs[l - 1].value[i] * pw[i][r - l + 1] % MOD[i])) % MOD[i];
            if (res.value[i] < 0) res.value[i] += MOD[i];
        }
        return res;
    }

    void solve(int nn) {
        for (int i = nn; i > n; --i) {
            Hash h1 = get_hash(1, n, hs).concat(get_hash(i + 1, nn, hs), nn - i);
            Hash h2 = get_hash(1, nn - i, ht).concat(get_hash(n + 1, nn, ht), nn - n );
            // Hash h2 = get_hash(n + 1, nn, ht); //.concat(get_hash(n + 1, nn, ht), nn - n );
            // i + 1, nn
            // 1, nn nn + 1 - 
            // , i + 1
            // cout << i << " " << h1.value[0] << " " << h2.value[0] << endl;
            if (h1 == h2) {
                for (int j = 1; j <= n; j++) {
                    printf("%c", s[j - 1]);
                }
                for (int j = i + 1; j <= nn; j++) {
                    printf("%c", s[j - 1]);
                }
                printf("\n");
                return;
            }
        }
        cout << s << endl;
    }

    int main() {

        scanf("%s", s);
        n = strlen(s);
        int n2 = n * 2;
        // append s to ss
        for (int i = 0; i < n; i++) {
            s[n + i] = s[n - i - 1];
        }
        s[n2] = '\0';
        // reverse s -> t
        for (int i = 0; i < n2; i++) {
            t[i] = s[n2 - i - 1];
            // cout << i << " " << t[i] << endl;
        }
        t[n2] = '\0';
        // cout << s << endl;
        // cout << t << endl;
        init(s, t, n2);

        solve(n2);

        return 0;
    }
    // g++ -std=c++14 -o a cf-hashC.cpp && ./a < a.in