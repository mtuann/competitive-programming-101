#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> coins(n);
    for (int i = 0; i < n; ++i) {
        cin >> coins[i];
    }

    sort(coins.begin(), coins.end());

    long long smallest_unreachable_sum = 1;
    for (int i = 0; i < n; ++i) {
        if (coins[i] > smallest_unreachable_sum) {
            break;
        }
        smallest_unreachable_sum += coins[i];
    }

    cout << smallest_unreachable_sum << endl;

    return 0;
}
