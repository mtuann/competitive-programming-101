#include <iostream>
using namespace std;

void determinePosition(long long x1, long long y1, long long x2, long long y2, long long x3, long long y3) {
    // Calculate the cross product
    long long cross_product = (x2 - x1) * (y3 - y1) - (y2 - y1) * (x3 - x1);
    cout << '(' << x1 << ',' << y1 << ") -> (" << x2 << ',' << y2 << ") -> (" << x3 << ',' << y3 << ") -> " << cross_product << " \n ";
    // Determine the position of p3 with respect to the line
    if (cross_product > 0) {
        cout << "LEFT" << endl;
    } else if (cross_product < 0) {
        cout << "RIGHT" << endl;
    } else {
        cout << "TOUCH" << endl;
    }
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        long long x1, y1, x2, y2, x3, y3;
        cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
        determinePosition(x1, y1, x2, y2, x3, y3);
    }
    return 0;
}

// g++ -std=c++14 -o a cses2189.cpp && ./a < a.in