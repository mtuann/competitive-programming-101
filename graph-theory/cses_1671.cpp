#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <climits>
using namespace std;

const long long INF = LLONG_MAX;

struct Edge {
    int to;
    long long cost;
};

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<Edge>> graph(n + 1);
    for (int i = 0; i < m; ++i) {
        int a, b;
        long long c;
        cin >> a >> b >> c;
        graph[a].push_back({b, c});
    }

    vector<long long> dist(n + 1, INF);
    dist[1] = 0;

    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
    pq.push({0, 1});

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        if (d > dist[u]) continue;

        for (auto& edge : graph[u]) {
            int v = edge.to;
            long long cost = edge.cost;

            if (dist[u] + cost < dist[v]) {
                dist[v] = dist[u] + cost;
                pq.push({dist[v], v});
            }
        }
    }

    for (int i = 1; i <= n; ++i) {
        cout << dist[i] << " ";
    }
    cout << endl;

    return 0;
}
