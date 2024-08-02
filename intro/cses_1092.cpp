#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;

    // Calculate the sum of the first n natural numbers
    long long sum = (n * (n + 1)) / 2;

    // Check if the sum is even
    if (sum % 2 != 0) {
        cout << "NO" << endl;
        return 0;
    }

    long long target = sum / 2;
    vector<int> set1, set2;
    long long current_sum = 0;

    // Use a greedy approach to find the first set
    for (int i = n; i >= 1; --i) {
        if (current_sum + i <= target) {
            current_sum += i;
            set1.push_back(i);
        } else {
            set2.push_back(i);
        }
    }

    cout << "YES" << endl;
    cout << set1.size() << endl;
    for (int num : set1) {
        cout << num << " ";
    }
    cout << endl;

    cout << set2.size() << endl;
    for (int num : set2) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}
