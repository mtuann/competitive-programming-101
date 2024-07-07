#include <iostream>

using namespace std;

int main() {
    freopen("product.inp", "r", stdin);
    freopen("product.ans", "w", stdout);

    long long a, b;
    cin >> a >> b;
    long long sum = 0;
    for (int i = 0; i < a; ++i) {
        sum += b;
    }
    cout << sum << endl;
    return 0;
}