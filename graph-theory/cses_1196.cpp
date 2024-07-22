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

struct State {
    long long cost;
    int node;
    int steps;
    bool operator>(const State& other) const {
        return cost > other.cost;
    }
};


vector<long long> find_k_shortest_paths(int n, int k, vector<vector<Edge>>& graph) {
    vector<long long> result;
    priority_queue<State, vector<State>, greater<State>> pq;
    vector<vector<long long>> dist(n + 1, vector<long long>(k, INF));
    
    pq.push({0, 1, 0});
    dist[1][0] = 0;
    
    while (!pq.empty() && result.size() < k) {
        auto [current_cost, u, steps] = pq.top();
        pq.pop();
        
        if (u == n) {
            result.push_back(current_cost);
            continue;
        }
        
        if (steps >= k) continue;
        
        for (const auto& edge : graph[u]) {
            int v = edge.to;
            long long weight = edge.cost;
            
            if (current_cost + weight < dist[v][steps + 1]) {
                dist[v][steps + 1] = current_cost + weight;
                pq.push({current_cost + weight, v, steps + 1});
            }
        }
    }
    
    return result;
}

int main() {
    int n, m, k;
    cin >> n >> m >> k;
    
    vector<vector<Edge>> graph(n + 1);
    
    for (int i = 0; i < m; ++i) {
        int a, b;
        long long c;
        cin >> a >> b >> c;
        graph[a].push_back({b, c});
    }
    
    vector<long long> k_shortest_paths = find_k_shortest_paths(n, k, graph);
    
    for (const auto& cost : k_shortest_paths) {
        cout << cost << " ";
    }
    cout << endl;
    
    return 0;
}
