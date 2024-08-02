#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> arr(n);

    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }

    long long moves = 0;

    // Ensure the array is non-decreasing
    for (int i = 1; i < n; ++i) {
        if (arr[i] < arr[i - 1]) {
            moves += arr[i - 1] - arr[i];
            arr[i] = arr[i - 1]; // Update current element to be non-decreasing
        }
    }

    cout << moves << endl;

    return 0;
}
