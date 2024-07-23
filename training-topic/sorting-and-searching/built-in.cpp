#include <iostream>

using namespace std;

int main() {
    int a[] = {1, 2, 2, 4, 4, 4, 5};
    int n = sizeof(a) / sizeof(a[0]);
    int x = 3;
    int lower = lower_bound(a, a + n, x) - a;
    x = 4;
    int upper = upper_bound(a, a + n, x) - a;
    cout << lower << " " << upper << endl; // Output: 3 3
    return 0;
}
// g++ built-in.cpp -o a && ./a