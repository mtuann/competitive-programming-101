#include <iostream>
using namespace std;

bool canEmptyPiles(long long a, long long b) {
    // Check if the total number of coins is divisible by 3
    if ((a + b) % 3 != 0) return false;
    
    // Check if neither pile exceeds twice the size of the other
    if (a > 2 * b || b > 2 * a) return false;
    
    return true;
}

int main() {
    int t;
    cin >> t;
    
    while (t--) {
        long long a, b;
        cin >> a >> b;
        
        if (canEmptyPiles(a, b)) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
    
    return 0;
}
