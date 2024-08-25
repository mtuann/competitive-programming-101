#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Range {
    int x, y, index;
};

bool compareRanges(const Range &a, const Range &b) {
    if (a.x != b.x)
        return a.x < b.x;
    return a.y > b.y;
}

int main() {
    int n;
    cin >> n;
    
    vector<Range> ranges(n);
    vector<int> contains(n, 0), is_contained(n, 0);
    
    for (int i = 0; i < n; ++i) {
        cin >> ranges[i].x >> ranges[i].y;
        ranges[i].index = i;
    }
    
    // Sort ranges by x and by y in descending order for ties
    sort(ranges.begin(), ranges.end(), compareRanges);
    
    // Checking if any range is contained by another
    int max_y = -1;
    for (int i = 0; i < n; ++i) {
        if (ranges[i].y <= max_y) {
            is_contained[ranges[i].index] = 1;
        }
        max_y = max(max_y, ranges[i].y);
    }
    
    // Checking if any range contains another
    int min_y = 1e9 + 1;
    for (int i = n - 1; i >= 0; --i) {
        if (ranges[i].y >= min_y) {
            contains[ranges[i].index] = 1;
        }
        min_y = min(min_y, ranges[i].y);
    }
    
    // Output the results
    for (int i = 0; i < n; ++i) {
        cout << contains[i] << " ";
    }
    cout << endl;
    for (int i = 0; i < n; ++i) {
        cout << is_contained[i] << " ";
    }
    cout << endl;
    
    return 0;
}
