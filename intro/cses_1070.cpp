#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;
    
    // If n is 2 or 1, handle special cases
    if (n == 1) {
        cout << "1" << endl;
        return 0;
    }
    if (n == 2 || n == 3) {
        cout << "NO SOLUTION" << endl;
        return 0;
    }

    // Output even numbers first
    for (int i = 2; i <= n; i += 2) {
        cout << i << " ";
    }

    // Output odd numbers next
    for (int i = 1; i <= n; i += 2) {
        cout << i << " ";
    }
    
    cout << endl;

    return 0;
}
