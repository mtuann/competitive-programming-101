#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <climits>
using namespace std;

const long long INF = 1e18;
const int MOD = 1e9 + 7;

struct Edge {
    int to;
    long long cost;
};

int main() {
    int n, m;
    cin >> n >> m;
    
    vector<vector<Edge>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        int a, b;
        long long c;
        cin >> a >> b >> c;
        adj[a].push_back({b, c});
    }
    
    vector<long long> dist(n + 1, INF);
    vector<long long> ways(n + 1, 0);
    vector<int> min_flights(n + 1, INT_MAX);
    vector<int> max_flights(n + 1, 0);

    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> pq;
    dist[1] = 0;
    ways[1] = 1;
    min_flights[1] = 0;
    max_flights[1] = 0;
    pq.push({0, 1});
    
    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d != dist[u]) continue;

        for (auto& edge : adj[u]) {
            int v = edge.to;
            long long new_dist = d + edge.cost;

            if (new_dist < dist[v]) {
                dist[v] = new_dist;
                ways[v] = ways[u];
                min_flights[v] = min_flights[u] + 1;
                max_flights[v] = max_flights[u] + 1;
                pq.push({new_dist, v});
            } else if (new_dist == dist[v]) {
                ways[v] = (ways[v] + ways[u]) % MOD;
                min_flights[v] = min(min_flights[v], min_flights[u] + 1);
                max_flights[v] = max(max_flights[v], max_flights[u] + 1);
            }
        }
    }

    cout << dist[n] << " " << ways[n] << " " << min_flights[n] << " " << max_flights[n] << endl;

    return 0;
}
