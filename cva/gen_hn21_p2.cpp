// https://oj.vnoi.info/contest/cvahn_dev22021_k116/ranking/
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <numeric>
#include <ctime>

using namespace std;

int main() {
    freopen("a.in", "w", stdout);
    int n;
    srand(time(0));
    n = rand() % 100 + 1;
    // random unique array containing n elements in range (1, 1e6)

    vector<int> v(n);
    for (int i = 0; i < n; i++) {
        if (i == 0) {
            v[i] = rand() % 10 + 1;
        } else {
            v[i] = v[i - 1] + rand() % 10 + 1;
        }
    }
    random_shuffle(v.begin(), v.end());
    cout << n << endl;
    for (int i = 0; i < n; i++) {
        int sc = rand() % 4 + 1;
        cout << v[i] << " " << sc << endl;
    }
    return 0;
}

// g++ -std=c++11 -O2 -Wall gen_hn21_12.cpp -o a && ./a < a.in
