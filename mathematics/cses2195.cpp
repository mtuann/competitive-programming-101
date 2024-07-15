#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Point {
    int x, y;
};

// Cross product of vectors OA and OB
// A positive cross product indicates a counter-clockwise turn, negative indicates clockwise turn
long long cross(const Point &O, const Point &A, const Point &B) {
    return (A.x - O.x) * (long long)(B.y - O.y) - (A.y - O.y) * (long long)(B.x - O.x);
}

// Function to compute the convex hull
vector<Point> convexHull(vector<Point> P) {
    int n = P.size();
    if (n <= 1) return P;
    sort(P.begin(), P.end(), [](const Point &a, const Point &b) {
        return a.x < b.x || (a.x == b.x && a.y < b.y);
    });

    vector<Point> lower, upper;
    for (const Point &p : P) {
        while (lower.size() >= 2 && cross(lower[lower.size() - 2], lower.back(), p) < 0)
            lower.pop_back();
        // < 0 means that the point is to the right of the line
        // >= 0 means that the point is to the left of the line or on the line
        lower.push_back(p);
        cout << "Lower: " << lower.back().x << " " << lower.back().y << " " << lower.size() << endl;
    }

    for (int i = n - 1; i >= 0; i--) {
        const Point &p = P[i];
        while (upper.size() >= 2 && cross(upper[upper.size() - 2], upper.back(), p) < 0)
            upper.pop_back();
        upper.push_back(p);
        cout << "Upper: " << upper.back().x << " " << upper.back().y << " " << upper.size() << endl;
    }
    cout << "Lower: " << lower.size() << " Upper: " << upper.size() << endl;
    for (int i = 0; i < lower.size(); ++i) {
        cout << lower[i].x << " " << lower[i].y << endl;
    }
    cout << "End of lower" << endl;
    for (int i = 0; i < upper.size(); ++i) {
        cout << upper[i].x << " " << upper[i].y << endl;
    }
    cout << "End of upper" << endl;
    lower.pop_back();
    upper.pop_back();
    lower.insert(lower.end(), upper.begin(), upper.end());
    return lower;
}

int main() {
    int n;
    cin >> n;
    vector<Point> points(n);
    for (int i = 0; i < n; ++i) {
        cin >> points[i].x >> points[i].y;
    }

    vector<Point> hull = convexHull(points);

    cout << hull.size() << endl;
    for (const Point &p : hull) {
        cout << p.x << " " << p.y << endl;
    }

    return 0;
}

// g++ -std=c++14 -o a cses2195.cpp && ./a < a.in