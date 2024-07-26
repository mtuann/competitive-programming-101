#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n, x;
    cin >> n >> x;
    
    vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }
    
    int count = 0;
    int current_sum = 0;
    int start = 0;
    
    for (int end = 0; end < n; ++end) {
        current_sum += arr[end];
        
        // Shrink the window from the left if the current_sum is greater than x
        while (current_sum > x && start <= end) {
            current_sum -= arr[start];
            ++start;
        }
        
        // Check if the current_sum is exactly x
        if (current_sum == x) {
            ++count;
        }
    }
    
    cout << count << endl;
    
    return 0;
}
