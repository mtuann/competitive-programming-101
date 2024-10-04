#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

struct Point {
    long long x, y;
};

// Function to calculate cross product of vectors OA and OB
// A positive cross product means counter-clockwise turn, negative means clockwise
long long crossProduct(const Point& O, const Point& A, const Point& B) {
    return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}

// Function to compute the polar angle of point B relative to origin O
double polarAngle(const Point& O, const Point& B) {
    return atan2(B.y - O.y, B.x - O.x);
}

int main() {
    // ifstream infile("DIVPOINT.INP");
    // ofstream outfile("DIVPOINT.OUT");

    int N;
    cin >> N;

    vector<Point> points(N);

    for (int i = 0; i < N; ++i) {
        cin >> points[i].x >> points[i].y;
    }
    sort(points.begin(), points.end(), [](const Point& A, const Point& B) {
        return A.x < B.x || (A.x == B.x && A.y < B.y);
    });

    // Arbitrary choice of first point as reference
    Point ref = points[0];
    
    // Create a vector of angles for the other points
    vector<pair<double, int>> angles;
    for (int i = 1; i < N; ++i) {
        angles.push_back({polarAngle(ref, points[i]), i});
    }
    
    // Sort points based on their polar angle
    sort(angles.begin(), angles.end());

    // We will consider each line formed by ref and another point
    // and check the division of points on each side
    for (int i = 0; i < N - 1; ++i) {
        // Left and right partition size
        int leftCount = i;
        int rightCount = N - 2 - leftCount;

        // We need |leftCount - rightCount| <= 1
        if (abs(leftCount - rightCount) <= 1) {
            // The line formed by ref and points[angles[i].second] satisfies the condition
            // Write the result to the output file
            cout << ref.x << " " << ref.y << " " << points[angles[i].second].x << " " << points[angles[i].second].y << endl;
            break;
        }
    }



    return 0;
}



// g++ -std=c++11 -O2 -Wall divide_set.cpp -o a && ./a < a.in