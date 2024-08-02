#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;
int n, k;

long long countSubarraysWithAtMostKDistinct(const vector<int>& arr, int k) {
    int n = arr.size();
    unordered_map<int, int> freq;
    int left = 0, right = 0;
    long long count = 0;
    int distinct = 0;

    while (right < n) {
        // Expand the window by adding arr[right]
        if (freq[arr[right]] == 0) {
            distinct++;
        }
        freq[arr[right]]++;
        right++;

        // Shrink the window from the left if it has more than k distinct elements
        while (distinct > k) {
            if (--freq[arr[left]] == 0) {
                distinct--;
            }
            left++;
        }

        // Add the number of valid subarrays ending at 'right - 1'
        // cout << left << " " << right << endl;
        count += (right - left);
    }

    return count;
}

int main() {
    
    cin >> n >> k;
    
    vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }
    
    long long result = countSubarraysWithAtMostKDistinct(arr, k);
    cout << result << endl;

    return 0;
}

// g++ cses_2428.cpp -o a && ./a < a.in