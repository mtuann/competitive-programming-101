#include <iostream>
#include <queue>
#include <unordered_set>
#include <string>

using namespace std;

int minStepsToZero(int n) {
    queue<pair<int, int>> q;
    unordered_set<int> visited;

    q.push({n, 0});
    visited.insert(n);

    while (!q.empty()) {
        auto [current, steps] = q.front();
        q.pop();

        if (current == 0) {
            return steps;
        }

        string numStr = to_string(current);
        for (char digitChar : numStr) {
            int digit = digitChar - '0';
            int next = current - digit;

            if (next >= 0 && visited.find(next) == visited.end()) {
                q.push({next, steps + 1});
                visited.insert(next);
            }
        }
    }

    return -1;  // This should never happen for valid inputs
}

int main() {
    int n;
    cin >> n;
    cout << minStepsToZero(n) << endl;
    return 0;
}
