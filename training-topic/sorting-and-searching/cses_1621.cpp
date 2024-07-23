#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 2e5 + 10;

int n;
int values[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        cin >> values[i];
    }

    // Sort the array
    sort(values, values + n);

    // Count distinct values
    int distinct_count = 1; // At least one distinct value if n > 0
    for (int i = 1; i < n; ++i) {
        if (values[i] != values[i-1]) {
            distinct_count++;
        }
    }

    cout << distinct_count << endl;

    return 0;
}
