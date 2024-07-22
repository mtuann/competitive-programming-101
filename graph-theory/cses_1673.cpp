#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <climits>

using namespace std;

const long long INF = LLONG_MAX;

int main() {
    int n, m;
    cin >> n >> m;

    vector<tuple<int, int, int>> edges;
    for (int i = 0; i < m; ++i) {
        int a, b, x;
        cin >> a >> b >> x;
        edges.emplace_back(a, b, x);
    }

    vector<long long> dist(n + 1, -INF);
    dist[1] = 0;

    for (int i = 1; i <= n - 1; ++i) {
        for (auto [a, b, x] : edges) {
            if (dist[a] != -INF && dist[a] + x > dist[b]) {
                dist[b] = dist[a] + x;
            }
        }
    }

    // Check for positive cycles
    for (int i = 1; i <= n - 1; ++i) {
        for (auto [a, b, x] : edges) {
            if (dist[a] != -INF && dist[a] + x > dist[b]) {
                // If a positive cycle is reachable from node 1 and affects node n, then it can generate an infinite score
                if (dist[a] + x > dist[b]) {
                    vector<bool> visited(n + 1, false);
                    vector<bool> stack(n + 1, false);

                    function<bool(int)> dfs = [&](int node) {
                        if (stack[node]) return true;
                        if (visited[node]) return false;

                        visited[node] = stack[node] = true;
                        for (auto [u, v, w] : edges) {
                            if (u == node && dfs(v)) return true;
                        }
                        stack[node] = false;
                        return false;
                    };

                    for (int i = 1; i <= n; ++i) {
                        if (dist[i] != -INF && dfs(i)) {
                            cout << -1 << endl;
                            return 0;
                        }
                    }
                }
            }
        }
    }

    cout << dist[n] << endl;
    return 0;
}
