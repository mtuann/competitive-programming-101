#include <iostream>
#include <vector>
using namespace std;

const int MAXX = 1e6 + 1;

int main() {
    int n;
    cin >> n;
    vector<int> arr(n);
    vector<int> freq(MAXX, 0);

    // Reading the input array and counting frequencies
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
        freq[arr[i]]++;
    }

    // We will check each possible GCD from 1 to MAXX
    int result = 1;  // The minimum possible GCD is 1
    for (int g = 1; g < MAXX; ++g) {
        int count = 0;
        // Count how many numbers are divisible by g
        for (int multiple = g; multiple < MAXX; multiple += g) {
            count += freq[multiple];
        }
        // If there are at least two multiples of g, update the result
        if (count >= 2) {
            result = g;
        }
    }

    cout << result << endl;
    return 0;
}
