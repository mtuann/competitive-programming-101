#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj(n + 1);
    vector<int> dist(n + 1, -1);
    vector<int> prev(n + 1, -1);

    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    queue<int> q;
    q.push(1);
    dist[1] = 1; // Starting node distance is 1 because we include the start node in the count

    while (!q.empty()) {
        int node = q.front();
        q.pop();

        for (int neighbor : adj[node]) {
            if (dist[neighbor] == -1) { // If the neighbor has not been visited
                dist[neighbor] = dist[node] + 1;
                prev[neighbor] = node;
                q.push(neighbor);

                // If we reached the target node, we can stop early
                if (neighbor == n) {
                    break;
                }
            }
        }
    }

    if (dist[n] == -1) {
        cout << "IMPOSSIBLE" << endl;
    } else {
        cout << dist[n] << endl;
        vector<int> path;
        for (int at = n; at != -1; at = prev[at]) {
            path.push_back(at);
        }
        reverse(path.begin(), path.end());
        for (int node : path) {
            cout << node << " ";
        }
        cout << endl;
    }

    return 0;
}
