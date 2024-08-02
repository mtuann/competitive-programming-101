#include <iostream>
#include <vector>
#include <cmath>
#include <string>

using namespace std;

char findDigitAtPosition(long long k) {
    long long length = 1;  // Length of the numbers (1, 2, 3, ...)
    long long count = 9;   // Number of numbers with 'length' digits
    long long start = 1;   // The smallest number with 'length' digits
    
    // Determine the length of the number containing the digit at position k
    while (k > length * count) {
        k -= length * count;
        length++;
        count *= 10;
        start *= 10;
    }
    
    // Find the exact number containing the k-th digit
    long long startNumber = start + (k - 1) / length;
    int digitIndex = (k - 1) % length;
    
    // Convert the number to a string and get the specific digit
    string numberStr = to_string(startNumber);
    return numberStr[digitIndex];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int q;
    cin >> q;
    
    vector<long long> queries(q);
    for (int i = 0; i < q; ++i) {
        cin >> queries[i];
    }
    
    for (long long k : queries) {
        cout << findDigitAtPosition(k) << '\n';
    }

    return 0;
}
