#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;
int n;

int main() {
    
    cin >> n;
    
    vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }
    
    unordered_map<int, int> remainder_count;
    long long prefix_sum = 0;
    long long count = 0;
    
    // Initialize the map with remainder 0 having count 1 (to handle the case when subarray starts from index 0)
    remainder_count[0] = 1;
    
    for (int i = 0; i < n; ++i) {
        prefix_sum += arr[i];
        int remainder = ((prefix_sum % n) + n) % n;  // Normalize negative remainders
        
        if (remainder_count.find(remainder) != remainder_count.end()) {
            count += remainder_count[remainder];
        }
        
        remainder_count[remainder]++;
    }
    
    cout << count << endl;
    
    return 0;
}
