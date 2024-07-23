#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

const int MAXN = 200000;
vector<int> teleporter(MAXN);
vector<int> result(MAXN, 0);
vector<int> visited(MAXN, -1);
vector<int> steps(MAXN, -1);

void dfs(int start) {
    int current = start;
    int count = 0;
    vector<int> path;

    while (true) {
        if (visited[current] == start) {
            // Found a cycle
            int cycle_start = find(path.begin(), path.end(), current) - path.begin();
            int cycle_length = count - cycle_start;
            for (int node : path) {
                if (find(path.begin(), path.end(), node) >= path.begin() + cycle_start) {
                    result[node] = cycle_length;
                }
            }
            break;
        }
        if (visited[current] != -1) {
            // Reached a node already processed in a different path
            if (visited[current] == start) {
                // We are revisiting a node in the current path
                int cycle_start = find(path.begin(), path.end(), current) - path.begin();
                int cycle_length = count - cycle_start;
                for (int node : path) {
                    if (find(path.begin(), path.end(), node) >= path.begin() + cycle_start) {
                        result[node] = cycle_length;
                    }
                }
            }
            break;
        }

        // Continue traversal
        visited[current] = start;
        path.push_back(current);
        steps[current] = count;
        count++;
        current = teleporter[current] - 1;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        cin >> teleporter[i];
    }

    for (int i = 0; i < n; ++i) {
        if (visited[i] == -1) {
            dfs(i);
        }
    }

    for (int i = 0; i < n; ++i) {
        cout << result[i] << ' ';
    }
    cout << '\n';

    return 0;
}
