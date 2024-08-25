#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n, q;
    cin >> n >> q;

    vector<vector<int>> forest(n + 1, vector<int>(n + 1, 0));
    vector<vector<int>> prefix(n + 1, vector<int>(n + 1, 0));

    // Reading the forest map
    for (int i = 1; i <= n; ++i) {
        string row;
        cin >> row;
        for (int j = 1; j <= n; ++j) {
            forest[i][j] = (row[j-1] == '*');
        }
    }

    // Building the prefix sum array
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            prefix[i][j] = forest[i][j] + prefix[i-1][j] + prefix[i][j-1] - prefix[i-1][j-1];
        }
    }

    // Answering the queries
    while (q--) {
        int y1, x1, y2, x2;
        cin >> y1 >> x1 >> y2 >> x2;

        int result = prefix[y2][x2] - prefix[y1-1][x2] - prefix[y2][x1-1] + prefix[y1-1][x1-1];
        cout << result << endl;
    }

    return 0;
}
