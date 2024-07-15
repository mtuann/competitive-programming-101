#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <climits>
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
