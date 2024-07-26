#include <iostream>
#include <vector>
#include <stack>

using namespace std;

int main() {
    int n;
    cin >> n;
    
    vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }
    
    vector<int> result(n);
    stack<int> s;
    
    for (int i = 0; i < n; ++i) {
        // Pop elements from the stack until we find a smaller element or the stack is empty
        while (!s.empty() && arr[s.top()] >= arr[i]) {
            s.pop();
        }
        // If stack is not empty, the top of the stack is the nearest smaller element
        if (!s.empty()) {
            result[i] = s.top() + 1;  // Convert to 1-based index
        } else {
            result[i] = 0;
        }
        // Push the current index onto the stack
        s.push(i);
    }
    
    // Print the result
    for (int i = 0; i < n; ++i) {
        cout << result[i] << " ";
    }
    cout << endl;
    
    return 0;
}
