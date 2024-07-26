#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

bool canDivide(const vector<int>& arr, int k, long long max_sum) {
    long long current_sum = 0;
    int subarray_count = 1;  // Start with one subarray

    for (int value : arr) {
        if (current_sum + value > max_sum) {
            // Need to start a new subarray
            ++subarray_count;
            current_sum = value;

            if (subarray_count > k) {
                return false;  // More subarrays than allowed
            }
        } else {
            current_sum += value;
        }
    }
    return true;
}

int main() {
    int n, k;
    cin >> n >> k;
    
    vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }
    
    long long left = *max_element(arr.begin(), arr.end());
    long long right = accumulate(arr.begin(), arr.end(), 0LL);
    long long result = right;
    
    while (left <= right) {
        long long mid = left + (right - left) / 2;
        
        if (canDivide(arr, k, mid)) {
            result = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    
    cout << result << endl;
    
    return 0;
}
