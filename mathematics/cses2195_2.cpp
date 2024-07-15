#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <cmath>
using namespace std;

typedef pair<int, int> Point;

// Global variable for the base point
Point p0;

// Function to calculate the cross product of vectors (p1-p0) x (p2-p0)
int crossProduct(Point p0, Point p1, Point p2) {
    return (p1.first - p0.first) * (p2.second - p0.second) - (p1.second - p0.second) * (p2.first - p0.first);
}

// Comparator function to sort points by polar angle with respect to the base point
bool compare(Point p1, Point p2) {
    int cp = crossProduct(p0, p1, p2);
    if (cp == 0) {
        // If the points are collinear, sort by distance from the base point
        return (p1.first - p0.first) * (p1.first - p0.first) + (p1.second - p0.second) * (p1.second - p0.second) <
               (p2.first - p0.first) * (p2.first - p0.first) + (p2.second - p0.second) * (p2.second - p0.second);
    }
    return cp > 0;  // Sort by the orientation (counter-clockwise for convex hull)
}



// Function to check if a point is on a segment
bool onSegment(Point p, Point q, Point r) {
    if (q.first <= max(p.first, r.first) && q.first >= min(p.first, r.first) &&
        q.second <= max(p.second, r.second) && q.second >= min(p.second, r.second)) {
        return true;
    }
    return false;
}

// Function to compute the convex hull using Graham Scan
vector<Point> convexHull(vector<Point>& points) {
    // Find the point with the smallest y-coordinate (and smallest x-coordinate in case of ties)
    p0 = *min_element(points.begin(), points.end(), [](const Point& a, const Point& b) {
        return a.second < b.second || (a.second == b.second && a.first < b.first);
    });

    // Sort points by polar angle with respect to the base point p0
    sort(points.begin(), points.end(), compare);

    // Initialize the convex hull with the base point
    vector<Point> hull;
    hull.push_back(p0);

    for (const Point& p : points) {
        while (hull.size() >= 2 && crossProduct(hull[hull.size() - 2], hull.back(), p) <= 0) {
            hull.pop_back();  // Remove the last point if it forms a non-left turn
        }
        hull.push_back(p);
    }

    // Print all points in the convex hull including segments
    set<Point> printedPoints;  // To keep track of the points already printed
    vector<Point> allPointsOnHull;

    for (size_t i = 0; i < hull.size(); ++i) {
        Point a = hull[i];
        Point b = hull[(i + 1) % hull.size()];

        // Add all points that are on the segment between a and b
        for (const Point& p : points) {
            if (p != a && p != b && onSegment(a, p, b)) {
                allPointsOnHull.push_back(p);
            }
        }

        // Add the endpoints of the segment to the list if not already added
        if (printedPoints.find(a) == printedPoints.end()) {
            allPointsOnHull.push_back(a);
            printedPoints.insert(a);
        }
        if (printedPoints.find(b) == printedPoints.end()) {
            allPointsOnHull.push_back(b);
            printedPoints.insert(b);
        }
    }

    // Remove duplicates and sort
    sort(allPointsOnHull.begin(), allPointsOnHull.end(), [](const Point& a, const Point& b) {
        return a < b;
    });
    allPointsOnHull.erase(unique(allPointsOnHull.begin(), allPointsOnHull.end()), allPointsOnHull.end());

    // Output the number of points on the convex hull
    cout << allPointsOnHull.size() << endl;

    // Output the points on the convex hull
    for (const Point& p : allPointsOnHull) {
        cout << p.first << " " << p.second << endl;
    }

    return hull;
}

int main() {
    int n;
    cin >> n;
    vector<Point> points(n);

    for (int i = 0; i < n; i++) {
        cin >> points[i].first >> points[i].second;
    }

    convexHull(points);

    return 0;
}
