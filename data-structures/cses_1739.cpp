#include <iostream>
#include <vector>

using namespace std;

class FenwickTree2D {
public:
    vector<vector<int>> bit;
    int n;

    FenwickTree2D(int size) : n(size) {
        bit.assign(n + 1, vector<int>(n + 1, 0));
    }

    // Add 'value' to cell (y, x)
    void update(int y, int x, int value) {
        for (int i = y; i <= n; i += i & -i) {
            for (int j = x; j <= n; j += j & -j) {
                bit[i][j] += value;
            }
        }
    }

    // Query the sum of trees in the rectangle from (1, 1) to (y, x)
    int query(int y, int x) {
        int sum = 0;
        for (int i = y; i > 0; i -= i & -i) {
            for (int j = x; j > 0; j -= j & -j) {
                sum += bit[i][j];
            }
        }
        return sum;
    }

    // Query the sum of trees in the rectangle (y1, x1) to (y2, x2)
    int query(int y1, int x1, int y2, int x2) {
        return query(y2, x2) - query(y1 - 1, x2) - query(y2, x1 - 1) + query(y1 - 1, x1 - 1);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    // Read the initial grid
    vector<vector<int>> forest(n + 1, vector<int>(n + 1, 0));
    FenwickTree2D fenwick(n);

    for (int i = 1; i <= n; ++i) {
        string line;
        cin >> line;
        for (int j = 1; j <= n; ++j) {
            if (line[j - 1] == '*') {
                forest[i][j] = 1;
                fenwick.update(i, j, 1);  // Initial population of the BIT
            }
        }
    }

    // Process queries
    while (q--) {
        int type;
        cin >> type;

        if (type == 1) {
            int y, x;
            cin >> y >> x;

            // Toggle the value at (y, x)
            if (forest[y][x] == 1) {
                fenwick.update(y, x, -1);  // Tree to empty
                forest[y][x] = 0;
            } else {
                fenwick.update(y, x, 1);   // Empty to tree
                forest[y][x] = 1;
            }
        } else if (type == 2) {
            int y1, x1, y2, x2;
            cin >> y1 >> x1 >> y2 >> x2;

            // Query the number of trees in the rectangle (y1, x1) to (y2, x2)
            cout << fenwick.query(y1, x1, y2, x2) << "\n";
        }
    }

    return 0;
}
