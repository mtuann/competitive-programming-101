// https://www.spoj.com/problems/KOPC12A/
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

typedef long long ll;

ll compute_cost(const vector<int>& heights, const vector<int>& costs, int target_height) {
    ll total_cost = 0;
    for (int i = 0; i < heights.size(); i++) {
        total_cost += abs(heights[i] - target_height) * (ll)costs[i];
    }
    return total_cost;
}

ll ternary_search(const vector<int>& heights, const vector<int>& costs, int low, int high) {
    while (high - low > 2) {
        int mid1 = low + (high - low) / 3;
        int mid2 = high - (high - low) / 3;

        ll cost1 = compute_cost(heights, costs, mid1);
        ll cost2 = compute_cost(heights, costs, mid2);

        if (cost1 > cost2) {
            low = mid1;
        } else {
            high = mid2;
        }
    }

    // Brute force check the final few possible heights
    ll min_cost = compute_cost(heights, costs, low);
    for (int i = low + 1; i <= high; i++) {
        min_cost = min(min_cost, compute_cost(heights, costs, i));
    }
    return min_cost;
}

int main() {
    int T;
    cin >> T;
    
    while (T--) {
        int n;
        cin >> n;

        vector<int> heights(n);
        vector<int> costs(n);

        for (int i = 0; i < n; i++) {
            cin >> heights[i];
        }

        for (int i = 0; i < n; i++) {
            cin >> costs[i];
        }

        // Apply ternary search between the minimum and maximum height in the input
        int min_height = *min_element(heights.begin(), heights.end());
        int max_height = *max_element(heights.begin(), heights.end());

        ll result = ternary_search(heights, costs, min_height, max_height);
        cout << result << endl;
    }

    return 0;
}
