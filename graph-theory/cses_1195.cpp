#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <algorithm>
#include <cmath>

using namespace std;

const long long INF = 1e18;

struct Edge {
    int to;
    long long cost;
};

struct State {
    long long cost;
    int node;
    bool used_discount;
    bool operator>(const State &other) const {
        return cost > other.cost;
    }
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

    vector<long long> dist_without(n + 1, INF);
    vector<long long> dist_with(n + 1, INF);
    
    priority_queue<State, vector<State>, greater<State>> pq;
    dist_without[1] = 0;
    pq.push({0, 1, false});

    while (!pq.empty()) {
        State curr = pq.top();
        pq.pop();

        long long current_cost = curr.cost;
        int current_node = curr.node;
        bool used_discount = curr.used_discount;

        if (used_discount && current_cost > dist_with[current_node]) continue;
        if (!used_discount && current_cost > dist_without[current_node]) continue;

        for (const Edge &edge : graph[current_node]) {
            int next_node = edge.to;
            long long next_cost = current_cost + edge.cost;

            // Case 1: Not using the discount
            if (!used_discount && next_cost < dist_without[next_node]) {
                dist_without[next_node] = next_cost;
                pq.push({next_cost, next_node, false});
            }

            // Case 2: Using the discount
            long long discounted_cost = current_cost + floor(edge.cost / 2);
            if (!used_discount && discounted_cost < dist_with[next_node]) {
                dist_with[next_node] = discounted_cost;
                pq.push({discounted_cost, next_node, true});
            }

            // Case 3: Already used the discount
            if (used_discount && next_cost < dist_with[next_node]) {
                dist_with[next_node] = next_cost;
                pq.push({next_cost, next_node, true});
            }
        }
    }

    cout << min(dist_without[n], dist_with[n]) << endl;

    return 0;
}
