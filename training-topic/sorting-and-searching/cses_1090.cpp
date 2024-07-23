#include <iostream>
#include <algorithm>
using namespace std;

const int MAX_N = 10 + 200000;  // maximum number of children

int weights[MAX_N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, x;
    cin >> n >> x;

    for (int i = 0; i < n; ++i) {
        cin >> weights[i];
    }

    // Sort the weights of the children
    sort(weights, weights + n);

    int i = 0; // Index for the lightest child
    int j = n - 1; // Index for the heaviest child
    int gondolas = 0;

    while (i <= j) {
        if (weights[i] + weights[j] <= x) {
            // If the lightest and the heaviest child can share a gondola
            i++;
        }
        // Move to the next heaviest child
        j--;
        // One gondola used
        gondolas++;
    }

    cout << gondolas << endl;

    return 0;
}
