#include <iostream>
#include <vector>
using namespace std;

int n;
int idx[200010];

int main() {
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        idx[x] = i + 1;
    }
    int ans = 1, pos = 1;
    for (int i = 1; i <= n; ++i) {
        if (pos > idx[i]) {
            ++ans;
        }
        pos = idx[i];
    }
    cout << ans << endl;
    return 0;
}

// g++ -std=c++14 -O2 -Wall cses_2216.cpp -o a && ./a < a.in