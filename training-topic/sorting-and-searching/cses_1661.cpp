#include <iostream>
#include <vector>
#include <chrono>
#include <unordered_map>

using namespace std;
struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};


int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, x;
    cin >> n >> x;
    
    vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }
    
    unordered_map<long long, int, custom_hash> prefix_sum_count;
    long long current_sum = 0;
    long long count = 0;
    
    // Initialize the map with prefix sum 0 having count 1 (to handle the case when subarray starts from index 0)
    prefix_sum_count[0] = 1;
    
    for (int i = 0; i < n; ++i) {
        current_sum += arr[i];
        
        // Check if there is a prefix sum such that (current_sum - prefix_sum) == x
        if (prefix_sum_count.find(current_sum - x) != prefix_sum_count.end()) {
            count += prefix_sum_count[current_sum - x];
        }
        
        // Update the map with the current prefix sum
        prefix_sum_count[current_sum]++;
    }
    
    cout << count << endl;
    
    return 0;
}
