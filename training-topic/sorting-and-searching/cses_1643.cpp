#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<long long> array(n);
    for (int i = 0; i < n; ++i) {
        cin >> array[i];
    }

    long long current_sum = array[0];
    long long max_sum = array[0];

    for (int i = 1; i < n; ++i) {
        current_sum = max(array[i], current_sum + array[i]);
        max_sum = max(max_sum, current_sum);
    }

    cout << max_sum << endl;

    return 0;
}
