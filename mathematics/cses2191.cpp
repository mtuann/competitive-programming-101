#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// Function to calculate the doubled area of the polygon using the Shoelace formula
long long doubledArea(const vector<pair<long long, long long>>& vertices) {
    int n = vertices.size();
    long long area = 0;

    for (int i = 0; i < n - 1; ++i) {
        area += vertices[i].first * vertices[i + 1].second;
        area -= vertices[i].second * vertices[i + 1].first;
    }

    // Add the last term (xn * y1 - yn * x1)
    area += vertices[n - 1].first * vertices[0].second;
    area -= vertices[n - 1].second * vertices[0].first;

    // Return the absolute value of the doubled area
    return abs(area);
}

int main() {
    int n;
    cin >> n;
    vector<pair<long long, long long>> vertices(n);

    for (int i = 0; i < n; ++i) {
        cin >> vertices[i].first >> vertices[i].second;
    }

    cout << doubledArea(vertices) << endl;
    return 0;
}
