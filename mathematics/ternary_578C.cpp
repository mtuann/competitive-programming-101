#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

typedef long double ld;  // Use long double for higher precision

const ld EPS = 1e-9;  // Adjust precision

// Function to calculate the maximum poorness for a given x
ld calculate_weakness(const vector<ld>& a, ld x) {
    ld max_sum = 0, min_sum = 0;
    ld cur_max = 0, cur_min = 0;
    
    for (int i = 0; i < a.size(); i++) {
        ld val = a[i] - x;
        cur_max = max(val, cur_max + val);
        cur_min = min(val, cur_min + val);
        max_sum = max(max_sum, cur_max);
        min_sum = min(min_sum, cur_min);
    }
    
    return max(fabsl(max_sum), fabsl(min_sum));  // Use fabsl for long double
}

// Ternary search to find the optimal x
ld ternary_search(const vector<ld>& a, ld low, ld high) {
    while (high - low > EPS) {
        ld mid1 = low + (high - low) / 3;
        ld mid2 = high - (high - low) / 3;

        ld weakness1 = calculate_weakness(a, mid1);
        ld weakness2 = calculate_weakness(a, mid2);

        if (weakness1 > weakness2) {
            low = mid1;
        } else {
            high = mid2;
        }
    }
    return low;
}

int main() {
    int n;
    cin >> n;
    
    vector<ld> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    // Ternary search between min(a) and max(a)
    // ld low = *min_element(a.begin(), a.end());
    // ld high = *max_element(a.begin(), a.end());
    ld low = -1e9, high = 1e9;  // Set the range manually

    ld result = ternary_search(a, low, high);
    cout.precision(10);
    cout << fixed << calculate_weakness(a, result) << endl;  // Print the optimal x directly

    return 0;
}
