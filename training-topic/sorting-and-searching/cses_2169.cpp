#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

struct Range {
    int x, y, index;
};

bool compareRanges(const Range &a, const Range &b) {
    if (a.x != b.x)
        return a.x < b.x;
    return a.y > b.y;
}

class FenwickTree {
public:
    FenwickTree(int n) : data(n + 1, 0) {}

    void update(int index, int value) {
        for (; index < data.size(); index += index & -index)
            data[index] += value;
    }

    int query(int index) const {
        int sum = 0;
        for (; index > 0; index -= index & -index)
            sum += data[index];
        return sum;
    }

    int rangeQuery(int left, int right) const {
        return query(right) - query(left - 1);
    }

private:
    vector<int> data;
};

int main() {
    int n;
    cin >> n;

    vector<Range> ranges(n);
    vector<int> contains(n, 0), containedBy(n, 0);
    vector<int> ys(n);

    for (int i = 0; i < n; ++i) {
        cin >> ranges[i].x >> ranges[i].y;
        ranges[i].index = i;
        ys[i] = ranges[i].y;
    }

    // Sort ranges by x and then by y descending
    sort(ranges.begin(), ranges.end(), compareRanges);

    // Coordinate compression of y values
    sort(ys.begin(), ys.end());
    ys.erase(unique(ys.begin(), ys.end()), ys.end());
    map<int, int> yCompressed;
    for (int i = 0; i < ys.size(); ++i) {
        yCompressed[ys[i]] = i + 1;
    }

    FenwickTree bit(ys.size());

    // Counting "contains"
    for (int i = n - 1; i >= 0; --i) {
        int yComp = yCompressed[ranges[i].y];
        // cout << ranges[i].x << " " << ranges[i].y << " " << yComp << endl;
        contains[ranges[i].index] = bit.query(yComp);
        bit.update(yComp, 1);
        // cout << ranges[i].index << " " << contains[ranges[i].index] << endl;
    }

   
    bit = FenwickTree(ys.size());  // Reset BIT for "contained by" calculation
    
    int max_y = ys.size();
    // cout << max_y << endl;
    // Counting "contained by"
    for (int i = 0; i < n; ++i) {
        int yComp = yCompressed[ranges[i].y];
        // cout << ranges[i].x << " " << ranges[i].y << " " << yComp << " " << ranges[i].index << endl;
        containedBy[ranges[i].index] = bit.rangeQuery(yComp, max_y);
        bit.update(yComp, 1);
    }

    // Output the results
    for (int i = 0; i < n; ++i) {
        cout << contains[i] << " ";
    }
    cout << endl;
    for (int i = 0; i < n; ++i) {
        cout << containedBy[i] << " ";
    }
    cout << endl;

    return 0;
}
// g++ -std=c++14 -O2 -Wall cses_2169.cpp -o a && ./a < a.in