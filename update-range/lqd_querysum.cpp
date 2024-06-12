// https://lqdoj.edu.vn/problem/querysum
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <cstring>

using namespace std;

const int N = 1e5 + 5;
int n, q;
long long a[N];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> q;

    // for (int i = 0; i < n; ++i) {
    //     cin >> a[i];
    // }
    n = 100;
    for (int i = 0; i < n; ++i) {
        cout << i << " " << (i & (-i)) << endl;
    }
    return 0;
}

// g++ -std=c++17 -o a lqd_querysum.cpp && ./a < a.in
