#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> sticks(n);

    for (int i = 0; i < n; ++i) {
        cin >> sticks[i];
    }

    // Sort the stick lengths to find the median
    sort(sticks.begin(), sticks.end());

    // Find the median
    int median = sticks[n / 2];

    // Calculate the total cost to make all sticks equal to the median
    long long total_cost = 0;
    for (int i = 0; i < n; ++i) {
        total_cost += abs(sticks[i] - median);
    }

    cout << total_cost << endl;

    return 0;
}
