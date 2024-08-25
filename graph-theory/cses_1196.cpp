#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

typedef long long ll;
typedef pair<ll, int> pli;

// const ll INF = 1e18;

int main() {
    // https://en.wikipedia.org/wiki/K_shortest_path_routing
    int n, m, k;
    cin >> n >> m >> k;

    vector<vector<pli>> adj(n + 1); // adjacency list with pairs (cost, destination)
    for (int i = 0; i < m; i++) {
        int a, b;
        ll c;
        cin >> a >> b >> c;
        adj[a].emplace_back(c, b);
    }

    // Min-heap priority queue (cost, node)
    priority_queue<pli, vector<pli>, greater<pli>> pq;
    vector<vector<ll>> dist(n + 1); // dist[i] stores the k shortest distances to node i
    
    pq.push({0, 1}); // start from city 1 with cost 0
    
    while (!pq.empty()) {
        ll cost = pq.top().first;
        int u = pq.top().second;
        pq.pop();
        
        // If we've already found k paths to this city, continue
        if ((int)dist[u].size() >= k) continue;
        
        dist[u].push_back(cost);
        
        // Explore neighbors
        for (auto &[nextCost, v] : adj[u]) {
            ll newCost = cost + nextCost;
            if (dist[v].size() < k) {
                pq.push({newCost, v});
            }
        }
    }
    
    // Output the k shortest paths to node n
    for (ll d : dist[n]) {
        cout << d << " ";
    }
    cout << endl;

    return 0;
}
// g++ -std=c++17 -O2 -Wall cses_1196.cpp -o a  && ./a < a.in