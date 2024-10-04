#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <numeric>

using namespace std;

int n;
int m;
int colors[500005];
struct query {
    int l, r, color;
};
int a[500005];
int final_colors[500005];

query queries[500005];

int main() {
    cin >> n >> m;

    for (int i = 0; i < m; ++i) {
        cin >> queries[i].l >> queries[i].r >> queries[i].color;
    }
    for (int i = 1; i <= n; ++i) cin >> final_colors[i];

    for (int i = 0; i < m; ++i) a[i] = i;

    do {
        for (int i = 0; i < m; ++i) {
            for (int j = queries[a[i]].l; j <= queries[a[i]].r; ++j) {
                colors[j] = queries[a[i]].color;
            }
        }

        int cnt = 0;
        for (int i = 1; i <= n; ++i) {
            if (colors[i] == final_colors[i]) cnt++;
        }

        if (cnt == n) {
            // cout << "YES" << endl;
            for (int i = 0; i < m; ++i) {
                cout << a[i] + 1 << " ";
            }
            cout << endl;
            return 0;
        }

    } while (next_permutation(a, a + m));
    
    cout << "-1" << endl;
    
    return 0;
}

// g++ -std=c++11 -O2 -Wall hn21_p7.cpp -o a && ./a < a.in
