#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;

    long long expectedSum = (static_cast<long long>(n) * (n + 1)) / 2;
    long long actualSum = 0;
    int number;

    for (int i = 0; i < n - 1; ++i) {
        cin >> number;
        actualSum += number;
    }

    cout << (expectedSum - actualSum) << endl;

    return 0;
}
