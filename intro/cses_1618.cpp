#include <iostream>
using namespace std;

int countTrailingZeros(int n) {
    int count = 0;
    // Count factors of 5
    while (n >= 5) {
        n /= 5;
        count += n;
    }
    return count;
}

int main() {
    int n;
    cin >> n;

    // Compute the number of trailing zeros in n!
    int result = countTrailingZeros(n);

    // Print the result
    cout << result << endl;

    return 0;
}
