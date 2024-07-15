#include <iostream>
#include <vector>
using namespace std;

// Function to check orientation of the triplet (p, q, r)
int orientation(long long px, long long py, long long qx, long long qy, long long rx, long long ry) {
    long long val = (qy - py) * (rx - qx) - (qx - px) * (ry - qy);
    if (val == 0) return 0; // collinear
    return (val > 0) ? 1 : 2; // clockwise or counterclockwise
}

// Function to check if point q lies on line segment pr
bool onSegment(long long px, long long py, long long qx, long long qy, long long rx, long long ry) {
    if (qx <= max(px, rx) && qx >= min(px, rx) && qy <= max(py, ry) && qy >= min(py, ry)) return true;
    return false;
}

// Function to check if point p lies inside the polygon
string pointInPolygon(vector<pair<long long, long long>>& polygon, int n, long long x, long long y) {
    // Check if the point is on any of the polygon's edges
    for (int i = 0; i < n; i++) {
        long long x1 = polygon[i].first;
        long long y1 = polygon[i].second;
        long long x2 = polygon[(i + 1) % n].first;
        long long y2 = polygon[(i + 1) % n].second;

        if (orientation(x1, y1, x, y, x2, y2) == 0 && onSegment(x1, y1, x, y, x2, y2)) {
            return "BOUNDARY";
        }
    }

    // Ray-casting algorithm
    int count = 0;
    for (int i = 0; i < n; i++) {
        long long x1 = polygon[i].first;
        long long y1 = polygon[i].second;
        long long x2 = polygon[(i + 1) % n].first;
        long long y2 = polygon[(i + 1) % n].second;

        // Ensure y1 <= y2
        if (y1 > y2) {
            swap(x1, x2);
            swap(y1, y2);
        }

        // Check if the point is within the y-range of the edge and to the left of the edge
        if (y > y1 && y <= y2 && (x < (x2 - x1) * (y - y1) / (y2 - y1) + x1)) {
            count++;
        }
    }

    return (count % 2 == 1) ? "INSIDE" : "OUTSIDE";
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<pair<long long, long long>> polygon(n);
    for (int i = 0; i < n; i++) {
        cin >> polygon[i].first >> polygon[i].second;
    }

    for (int i = 0; i < m; i++) {
        long long x, y;
        cin >> x >> y;
        cout << pointInPolygon(polygon, n, x, y) << endl;
    }

    return 0;
}


// WA: still failing on test case 1