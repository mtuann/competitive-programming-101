#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <algorithm>
#include <climits>

using namespace std;

const long long INF = LLONG_MAX;

struct Edge {
    int to;
    long long cost;
};

void dijkstra(int start, vector<long long>& dist, const vector<vector<Edge>>& graph) {
    dist[start] = 0;
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
    pq.push({0, start});
    
    while (!pq.empty()) {
        auto [current_dist, u] = pq.top();
        pq.pop();
        
        if (current_dist > dist[u]) continue;
        
        for (const auto& edge : graph[u]) {
            int v = edge.to;
            long long weight = edge.cost;
            
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    
    vector<vector<Edge>> graph(n + 1);
    vector<tuple<int, int, long long>> edges;

    for (int i = 0; i < m; ++i) {
        int a, b;
        long long c;
        cin >> a >> b >> c;
        graph[a].push_back({b, c});
        edges.push_back({a, b, c});
    }
    
    vector<long long> dist_from_start(n + 1, INF);
    vector<long long> dist_to_end(n + 1, INF);

    dijkstra(1, dist_from_start, graph);
    vector<vector<Edge>> reversed_graph(n + 1);
    for (const auto& [a, b, c] : edges) {
        reversed_graph[b].push_back({a, c});
    }
    dijkstra(n, dist_to_end, reversed_graph);

    long long min_cost = dist_from_start[n];
    
    for (const auto& [a, b, c] : edges) {
        if (dist_from_start[a] < INF && dist_to_end[b] < INF) {
            long long cost_with_discount = dist_from_start[a] + (c / 2) + dist_to_end[b];
            min_cost = min(min_cost, cost_with_discount);
        }
    }

    cout << min_cost << endl;

    return 0;
}
