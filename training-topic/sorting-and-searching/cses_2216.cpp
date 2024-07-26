#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int longestIncreasingSubsequence(const vector<int>& arr) {
    vector<int> lis;
    for (int x : arr) {
        auto it = upper_bound(lis.begin(), lis.end(), x);
        if (it == lis.end()) {
            lis.push_back(x);
        } else {
            *it = x;
        }
    }
    return lis.size();
}

int main() {
    int n;
    cin >> n;
    
    vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }
    
    // Reverse the array
    reverse(arr.begin(), arr.end());
    
    // Find the length of LIS in the reversed array
    int rounds = longestIncreasingSubsequence(arr);
    
    cout << rounds << endl;
    return 0;
}

// g++ -std=c++14 -O2 -Wall cses_2216.cpp -o a && ./a < a.in