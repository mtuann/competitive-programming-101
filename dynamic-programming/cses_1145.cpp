#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int lengthOfLIS(const vector<int>& nums) {
    if (nums.empty()) return 0;

    vector<int> tails;

    for (int num : nums) {
        auto it = lower_bound(tails.begin(), tails.end(), num);
        if (it == tails.end()) {
            tails.push_back(num);
        } else {
            *it = num;
        }
    }

    return tails.size();
}

int main() {
    int n;
    cin >> n;
    vector<int> nums(n);

    for (int i = 0; i < n; ++i) {
        cin >> nums[i];
    }

    cout << lengthOfLIS(nums) << endl;

    return 0;
}
