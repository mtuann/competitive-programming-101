#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <climits>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, a, b;
    cin >> n >> a >> b;
    
    vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }

    // Compute prefix sums
    vector<long long> prefix(n + 1, 0);
    for (int i = 0; i < n; ++i) {
        prefix[i + 1] = prefix[i] + arr[i];
    }

    // Deque to store indices of prefix sums
    deque<int> dq;
    long long max_sum = LLONG_MIN;

    for (int i = 0; i <= n; ++i) {
        // Maintain the deque so that the prefix sums are in increasing order
        while (!dq.empty() && dq.front() < i - b) {
            dq.pop_front();
        }
        // Compute the max sum of subarrays with length in the range [a, b]
        if (i >= a) {
            max_sum = max(max_sum, prefix[i] - prefix[dq.front()]);
        }
        // Maintain the deque to have the smallest prefix sum at the back
        while (!dq.empty() && prefix[dq.back()] >= prefix[i]) {
            dq.pop_back();
        }
        dq.push_back(i);
    }

    cout << max_sum << endl;

    return 0;
}
