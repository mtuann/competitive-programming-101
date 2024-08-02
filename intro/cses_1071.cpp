#include <iostream>
#include <cmath>

using namespace std;

long long findNumber(int y, int x) {
    int layer = max(y, x);
    long long start = (long long)(layer - 1) * (layer - 1) + 1;
    // long long end = layer * layer;
    
    if (layer % 2 == 0) {
        // For even layer, starting from top-right
        if (x == layer) {
            return start + (y - 1);
        } else {
            return start + (layer - 1) * 2 - (x - 1);
        }
    } else {
        // For odd layer, starting from bottom-left
        if (y == layer) {
            return start + (x - 1);
        } else {
            return start + (layer - 1) * 2 - (y - 1);
        }
    }
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        int y, x;
        cin >> y >> x;
        cout << findNumber(y, x) << endl;
    }
    return 0;
}
