
## https://cses.fi/problemset/task/2189
To determine whether the point \( p_3 \) is on the left, right, or exactly on the line defined by \( p_1 \) and \( p_2 \), we can use the cross product of vectors. Specifically, for points \( p_1 = (x_1, y_1) \), \( p_2 = (x_2, y_2) \), and \( p_3 = (x_3, y_3) \), the relative position of \( p_3 \) with respect to the line from \( p_1 \) to \( p_2 \) can be determined by the sign of the following expression:

\[ \text{cross\_product} = (x_2 - x_1) \cdot (y_3 - y_1) - (y_2 - y_1) \cdot (x_3 - x_1) \]

- If `cross_product > 0`, \( p_3 \) is on the left side.
- If `cross_product < 0`, \( p_3 \) is on the right side.
- If `cross_product == 0`, \( p_3 \) is on the line (i.e., it touches the line).

Here's the C++ code to implement this logic:

```cpp
#include <iostream>
using namespace std;

void determinePosition(long long x1, long long y1, long long x2, long long y2, long long x3, long long y3) {
    // Calculate the cross product
    long long cross_product = (x2 - x1) * (y3 - y1) - (y2 - y1) * (x3 - x1);
    
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
```

### Explanation:
1. **Input Handling**: Read the number of test cases \( t \).
2. **Processing Each Test Case**:
   - For each test case, read the coordinates of \( p_1 \), \( p_2 \), and \( p_3 \).
   - Calculate the cross product to determine the relative position of \( p_3 \).
3. **Output**:
   - Print "LEFT" if \( p_3 \) is on the left.
   - Print "RIGHT" if \( p_3 \) is on the right.
   - Print "TOUCH" if \( p_3 \) touches the line.

This implementation is efficient and works within the given constraints.


The cross product is a mathematical operation that is widely used in vector algebra and has important applications in physics, engineering, and computer graphics. In the context of determining the relative position of a point with respect to a directed line segment, the cross product helps us understand whether a point lies to the left, right, or directly on the line.

### Definition of Cross Product

For two vectors \(\mathbf{a}\) and \(\mathbf{b}\) in three-dimensional space, the cross product \(\mathbf{a} \times \mathbf{b}\) is a vector that is perpendicular to both \(\mathbf{a}\) and \(\mathbf{b}\). Its magnitude is given by:

\[ \|\mathbf{a} \times \mathbf{b}\| = \|\mathbf{a}\| \|\mathbf{b}\| \sin(\theta) \]

where \(\theta\) is the angle between \(\mathbf{a}\) and \(\mathbf{b}\).

The direction of the cross product vector follows the right-hand rule, meaning if you point your right hand's index finger along \(\mathbf{a}\) and your middle finger along \(\mathbf{b}\), your thumb points in the direction of \(\mathbf{a} \times \mathbf{b}\).

### 2D Cross Product for Point Orientation

In two dimensions, we use a simplified version of the cross product that yields a scalar value, which helps in determining the relative orientation of three points.

Given three points \( p_1 = (x_1, y_1) \), \( p_2 = (x_2, y_2) \), and \( p_3 = (x_3, y_3) \), we form two vectors:

1. Vector from \( p_1 \) to \( p_2 \): \(\mathbf{v_1} = (x_2 - x_1, y_2 - y_1)\)
2. Vector from \( p_1 \) to \( p_3 \): \(\mathbf{v_2} = (x_3 - x_1, y_3 - y_1)\)

The cross product of these vectors in 2D is given by:

\[ \text{cross\_product} = (x_2 - x_1) \cdot (y_3 - y_1) - (y_2 - y_1) \cdot (x_3 - x_1) \]

### Interpretation of the Result

- **If \(\text{cross\_product} > 0\)**:
  - The point \( p_3 \) is on the left side of the line as we move from \( p_1 \) to \( p_2 \).
- **If \(\text{cross\_product} < 0\)**:
  - The point \( p_3 \) is on the right side of the line.
- **If \(\text{cross\_product} = 0\)**:
  - The point \( p_3 \) lies exactly on the line (collinear with \( p_1 \) and \( p_2 \)).

### Geometric Intuition

The 2D cross product measures the signed area of the parallelogram formed by the vectors \(\mathbf{v_1}\) and \(\mathbf{v_2}\). 

- A positive area (positive cross product) means that as you look from \( p_1 \) to \( p_2 \), \( p_3 \) is to your left.
- A negative area (negative cross product) means \( p_3 \) is to your right.
- A zero area (zero cross product) means \( p_3 \) is directly on the line extending from \( p_1 \) to \( p_2 \).

This mathematical tool is highly efficient for solving geometric problems involving the relative positions of points and lines in a plane.

## https://cses.fi/problemset/task/2190

To determine if two line segments intersect, we can use the orientation test, which is based on the cross product we discussed earlier. The idea is to check the relative orientation of the points to determine if the segments straddle each other. 

### Orientation Function
For three points \( p = (x_p, y_p) \), \( q = (x_q, y_q) \), and \( r = (x_r, y_r) \), the orientation of the triplet (p, q, r) can be:
- 0 if p, q, r are collinear,
- 1 if they are oriented clockwise,
- 2 if they are oriented counterclockwise.

The orientation is computed as:
\[ \text{val} = (y_q - y_p) \cdot (x_r - x_q) - (x_q - x_p) \cdot (y_r - y_q) \]

- \(\text{val} = 0\) -> collinear
- \(\text{val} > 0\) -> clockwise
- \(\text{val} < 0\) -> counterclockwise

### On-Segment Function
To check if a point \( q \) lies on the line segment \( pr \):
\[ \text{isOnSegment}(p, q, r) \]

### General and Special Case Checks
- General case: Segments straddle each other.
- Special cases: Collinear points that overlap.

Here's the C++ code to implement the solution:

```cpp
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
```

### Explanation:

1. **Orientation Calculation**: The `orientation` function determines if three points are collinear, clockwise, or counterclockwise.
2. **On-Segment Check**: The `isOnSegment` function checks if a point lies on a segment.
3. **Intersection Check**: The `doSegmentsIntersect` function checks the general and special cases to see if two segments intersect.
4. **Main Function**: Reads the number of test cases, processes each case, and prints "YES" or "NO" based on the intersection check. 

This approach efficiently handles the problem within the given constraints.

The orientation test using the cross product helps determine the relative direction of three points. In the context of the cross product, the direction is typically considered as follows:

- **Clockwise** if the points make a right turn.
- **Counterclockwise** if the points make a left turn.

The cross product formula used in the code:
\[ \text{val} = (y_2 - y_1) \cdot (x_3 - x_2) - (x_2 - x_1) \cdot (y_3 - y_2) \]

This formula is derived from the determinant of the matrix formed by the vectors, which gives the signed area of the parallelogram formed by the points. The sign of this value determines the relative direction:

- **Positive value**: Indicates a counterclockwise turn (left turn).
- **Negative value**: Indicates a clockwise turn (right turn).
- **Zero**: Indicates collinearity.

The mistake in the previous explanation was stating that a positive value indicates a clockwise turn. Actually, a positive cross product indicates a counterclockwise turn, and a negative cross product indicates a clockwise turn. Let's correct the explanation and the function accordingly:

### Corrected Orientation Function
Here's the correct interpretation:

- If the cross product is positive, the triplet \( (x1, y1), (x2, y2), (x3, y3) \) is counterclockwise (left turn).
- If the cross product is negative, the triplet is clockwise (right turn).
- If the cross product is zero, the points are collinear.

Here's the corrected C++ code:

```cpp
#include <iostream>
using namespace std;

// Function to find the orientation of the ordered triplet (p, q, r)
int orientation(long long x1, long long y1, long long x2, long long y2, long long x3, long long y3) {
    long long val = (y2 - y1) * (x3 - x2) - (x2 - x1) * (y3 - y2);
    if (val == 0) return 0; // collinear
    return (val > 0) ? 2 : 1; // counterclockwise (left) if val > 0, clockwise (right) if val < 0
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
```

### Explanation:

1. **Orientation Calculation**: The `orientation` function now correctly identifies the orientation of the triplet \( (x1, y1), (x2, y2), (x3, y3) \). A positive value indicates a counterclockwise turn (left turn), and a negative value indicates a clockwise turn (right turn).
2. **On-Segment Check**: The `isOnSegment` function checks if a point lies on a segment.
3. **Intersection Check**: The `doSegmentsIntersect` function checks the general and special cases to see if two segments intersect.
4. **Main Function**: Reads the number of test cases, processes each case, and prints "YES" or "NO" based on the intersection check. 

This approach ensures the correct handling of the problem within the given constraints.


## https://cses.fi/problemset/task/2192
To solve the problem of determining whether a point is inside, outside, or on the boundary of a polygon, we can use the ray-casting algorithm to check if a point is inside a polygon and additional checks to determine if a point is on the boundary.

Here's a detailed approach in C++:

1. **Ray-casting algorithm**: To determine if a point is inside a polygon, we cast a ray from the point and count how many times it intersects the edges of the polygon. If the count is odd, the point is inside; if even, it is outside.

2. **Boundary check**: To check if a point is on the boundary, we use the orientation test and the on-segment check from the previous problem.

Here is the complete code:

```cpp
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

        if (y == y1 && y == y2 && x >= min(x1, x2) && x <= max(x1, x2)) {
            return "BOUNDARY";
        }

        if (y1 > y2) {
            swap(x1, x2);
            swap(y1, y2);
        }

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
```

### Explanation

1. **Orientation Calculation**: The `orientation` function determines the orientation of three points (collinear, clockwise, counterclockwise).

2. **On-Segment Check**: The `onSegment` function checks if a point lies on a line segment.

3. **Point in Polygon Check**: The `pointInPolygon` function uses the ray-casting algorithm to count intersections of a horizontal ray starting from the point to the right. Additionally, it checks if the point lies on any edge of the polygon using the orientation and on-segment checks.

4. **Main Function**: Reads the number of vertices and points, the vertices of the polygon, and the coordinates of each point. For each point, it determines whether the point is inside, outside, or on the boundary of the polygon and prints the result.

This approach ensures the correct handling of points within the given constraints.

## https://cses.fi/problemset/task/2193

## https://cses.fi/problemset/task/2194
To solve the problem of finding the minimum squared Euclidean distance between any two distinct points from a set of points on a 2D plane, we can use an efficient algorithm to handle the constraints. Given that \( n \) can be as large as \( 2 \times 10^5 \), a brute-force solution with \( O(n^2) \) complexity is not feasible due to time constraints.

Instead, we use a divide-and-conquer approach, similar to the one used in the Closest Pair of Points problem. This approach works in \( O(n \log n) \) time, which is suitable for large values of \( n \).

Here’s the C++ code implementing this approach:

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <limits>
using namespace std;

typedef long long ll;

// Function to compute the squared Euclidean distance between two points
ll squaredDistance(pair<int, int> a, pair<int, int> b) {
    ll dx = a.first - b.first;
    ll dy = a.second - b.second;
    return dx * dx + dy * dy;
}

// Merge function for the divide and conquer approach
ll merge(vector<pair<int, int>>& points, vector<pair<int, int>>& temp, int left, int mid, int right, ll minDist) {
    int i = left, j = mid + 1;
    int k = left;
    while (i <= mid && j <= right) {
        if (points[i].second <= points[j].second) {
            temp[k++] = points[i++];
        } else {
            temp[k++] = points[j++];
        }
    }
    while (i <= mid) temp[k++] = points[i++];
    while (j <= right) temp[k++] = points[j++];
    for (int i = left; i <= right; i++) points[i] = temp[i];

    vector<pair<int, int>> strip;
    for (int i = left; i <= right; i++) {
        for (int j = 0; j < strip.size(); j++) {
            if ((points[i].second - strip[j].second) * (points[i].second - strip[j].second) >= minDist) break;
            minDist = min(minDist, squaredDistance(points[i], strip[j]));
        }
        strip.push_back(points[i]);
    }
    return minDist;
}

// Recursive function to find the minimum distance
ll closestPair(vector<pair<int, int>>& points, vector<pair<int, int>>& temp, int left, int right) {
    if (left >= right) return LLONG_MAX;

    int mid = (left + right) / 2;
    ll minDist = min(closestPair(points, temp, left, mid), closestPair(points, temp, mid + 1, right));
    minDist = min(minDist, merge(points, temp, left, mid, right, minDist));

    return minDist;
}

int main() {
    int n;
    cin >> n;
    vector<pair<int, int>> points(n);
    for (int i = 0; i < n; i++) {
        cin >> points[i].first >> points[i].second;
    }

    sort(points.begin(), points.end()); // Sort by x-coordinate

    vector<pair<int, int>> temp(n);
    ll minDist = closestPair(points, temp, 0, n - 1);

    cout << minDist << endl;
    return 0;
}
```

### Explanation:

1. **Data Structures**:
   - `vector<pair<int, int>> points`: Stores the input points.
   - `vector<pair<int, int>> temp`: Temporary storage for the merge operation.

2. **Sorting**:
   - Points are sorted by their x-coordinates to prepare for the divide-and-conquer approach.

3. **Divide and Conquer**:
   - **`closestPair` Function**:
     - Recursively divides the set of points into two halves.
     - Finds the minimum distance in each half and then merges the results.
   - **`merge` Function**:
     - Combines results from the two halves.
     - Checks for possible smaller distances between points that lie across the dividing line but are close to each other in the y-dimension.

4. **Distance Calculation**:
   - **`squaredDistance` Function**:
     - Computes the squared Euclidean distance to avoid floating-point precision issues.

5. **Main Function**:
   - Reads input points, sorts them, and calls the `closestPair` function.
   - Outputs the minimum squared distance found.

### How It Works:

1. **Sorting**: Points are sorted by x-coordinates to divide them into two halves.
2. **Recursion**: The `closestPair` function recursively solves the problem for each half.
3. **Merging**: During merging, the `merge` function checks distances between points close to the dividing line and updates the minimum distance.
4. **Result**: The smallest distance found during the process is printed.

### Performance:

- **Time Complexity**: The approach has a time complexity of \( O(n \log n) \), which is efficient for \( n \leq 200{,}000 \).
- **Space Complexity**: The space complexity is \( O(n) \) for the temporary storage used in the merge process.

This code efficiently handles the constraints provided and ensures the correct computation of the minimum squared Euclidean distance.



## https://cses.fi/problemset/task/2195


Calculating the convex hull can be a bit tricky due to precision errors and handling edge cases correctly. Some implementations of convex hull algorithms, such as Andrew's monotone chain algorithm (which is an efficient O(n log n) algorithm), compute the lower and upper hulls separately and then combine them. In certain edge cases, reversing the array of points can help ensure all points on the hull are correctly identified. Here's an explanation of why this might be necessary:

### Why Reversing the Array Might be Necessary

1. **Numerical Precision**: Numerical precision issues can cause certain points that lie on the boundary to be misclassified, especially when dealing with collinear points or very close points. By reversing the array, the algorithm might avoid some of these precision errors by processing the points in a different order.

2. **Collinear Points**: Handling collinear points can be tricky. Depending on the order of processing, some algorithms might discard collinear points incorrectly. By reversing the array, the order in which the points are processed changes, ensuring that collinear points are correctly included or excluded from the hull.

3. **Algorithm Robustness**: Reversing the array and running the algorithm again can act as a robustness check. If both runs (original and reversed) give the same result, it increases confidence in the correctness of the output.

4. **Implementation Details**: Some specific implementations might have subtle bugs or edge cases that are mitigated by processing the points in a different order. Reversing the array is a simple way to potentially catch these issues.

### How the Convex Hull Algorithm Works

Here's a high-level overview of Andrew's monotone chain algorithm, which is a common approach to compute the convex hull:

1. **Sort the Points**: Sort the points by x-coordinate (and by y-coordinate if x-coordinates are the same).

2. **Build the Lower Hull**:
   - Start with an empty list for the lower hull.
   - Iterate through the sorted points.
   - For each point, while the last two points in the lower hull and the current point do not form a counter-clockwise turn, remove the last point from the lower hull.
   - Add the current point to the lower hull.

3. **Build the Upper Hull**:
   - Start with an empty list for the upper hull.
   - Iterate through the sorted points in reverse order.
   - For each point, while the last two points in the upper hull and the current point do not form a counter-clockwise turn, remove the last point from the upper hull.
   - Add the current point to the upper hull.

4. **Combine the Hulls**: The convex hull is the combination of the lower and upper hulls.

### Example C++ Code

Here’s an example of computing the convex hull using Andrew’s monotone chain algorithm. This version includes reversing the points to ensure correctness.

```cpp
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
        while (lower.size() >= 2 && cross(lower[lower.size() - 2], lower.back(), p) <= 0)
            lower.pop_back();
        lower.push_back(p);
    }

    for (int i = n - 1; i >= 0; i--) {
        const Point &p = P[i];
        while (upper.size() >= 2 && cross(upper[upper.size() - 2], upper.back(), p) <= 0)
            upper.pop_back();
        upper.push_back(p);
    }

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
```

### Explanation of the Code

1. **Point Structure**: Defines a point with `x` and `y` coordinates.
2. **Cross Product Function**: Calculates the cross product to determine the turn direction.
3. **Convex Hull Function**: Implements the convex hull algorithm using the monotone chain method.
4. **Main Function**: Reads input points, computes the convex hull, and prints the result.

### Additional Considerations

- **Precision**: Ensure that operations involving large numbers are handled with adequate precision, particularly when working with integer coordinates in the range \([-10^9, 10^9]\).
- **Boundary Points**: Make sure all points on the boundary are correctly included. Handling collinear points properly is crucial.
- **Edge Cases**: Test the implementation with various edge cases, such as all points being collinear, to ensure robustness.

By understanding and implementing these considerations, you can develop a more robust convex hull algorithm that handles a wide range of input scenarios effectively.