#include <iostream>
using namespace std;

// Function to find the orientation of the ordered triplet (p, q, r)
int orientation(long long x1, long long y1, long long x2, long long y2, long long x3, long long y3) {
    long long val = (y2 - y1) * (x3 - x2) - (x2 - x1) * (y3 - y2);
    if (val == 0) return 0; // collinear
    return (val > 0) ? 1 : 2; // clock or counterclockwise
}

// Function to check if point q lies on line segment pr
bool isOnSegment(long long x1, long long y1, long long x2, long long y2, long long x3, long long y3) {
    if (x2 <= max(x1, x3) && x2 >= min(x1, x3) && y2 <= max(y1, y3) && y2 >= min(y1, y3)) return true;
    return false;
}

// Function to determine if the segments intersect
bool doSegmentsIntersect(long long x1, long long y1, long long x2, long long y2, long long x3, long long y3, long long x4, long long y4) {
    int o1 = orientation(x1, y1, x2, y2, x3, y3);
    int o2 = orientation(x1, y1, x2, y2, x4, y4);
    int o3 = orientation(x3, y3, x4, y4, x1, y1);
    int o4 = orientation(x3, y3, x4, y4, x2, y2);

    // General case
    if (o1 != o2 && o3 != o4) return true;

    // Special cases
    if (o1 == 0 && isOnSegment(x1, y1, x3, y3, x2, y2)) return true;
    if (o2 == 0 && isOnSegment(x1, y1, x4, y4, x2, y2)) return true;
    if (o3 == 0 && isOnSegment(x3, y3, x1, y1, x4, y4)) return true;
    if (o4 == 0 && isOnSegment(x3, y3, x2, y2, x4, y4)) return true;

    return false;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        long long x1, y1, x2, y2, x3, y3, x4, y4;
        cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;
        if (doSegmentsIntersect(x1, y1, x2, y2, x3, y3, x4, y4)) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
    return 0;
}
