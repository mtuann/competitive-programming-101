#include <iostream>
#include <vector>
#include <limits.h>

using namespace std;

struct Edge {
    int from, to, weight;
};

int main() {
    int n, m;
    cin >> n >> m;

    vector<Edge> edges(m);
    vector<long long> dist(n + 1, LLONG_MIN);
    // cout << dist[1] << endl;
    dist[1] = 0;

    for (int i = 0; i < m; i++) {
        cin >> edges[i].from >> edges[i].to >> edges[i].weight;
    }

    // Bellman-Ford algorithm to calculate the longest path
    for (int i = 1; i < n; i++) { // n-1 relaxations
        for (int j = 0; j < m; j++) {
            int u = edges[j].from;
            int v = edges[j].to;
            int w = edges[j].weight;
            if (dist[u] != LLONG_MIN && dist[u] + w > dist[v]) {
                dist[v] = dist[u] + w;
            }
        }
    }

    // Check for positive-weight cycles
    for (int i = 0; i < m; i++) {
        int u = edges[i].from;
        int v = edges[i].to;
        int w = edges[i].weight;
        if (dist[u] != LLONG_MIN && dist[u] + w > dist[v]) {
            cout << "u = " << u << ", v = " << v << ", w = " << w << endl;
            // If there's a positive-weight cycle reachable from room 1
            vector<bool> visited(n + 1, false);
            // Check if we can reach node n from this cycle
            vector<int> stack;
            stack.push_back(u);
            visited[u] = true;

            while (!stack.empty()) {
                int current = stack.back();
                stack.pop_back();

                if (current == n) {
                    cout << -1 << endl;
                    return 0;
                }

                for (int j = 0; j < m; j++) {
                    if (edges[j].from == current && !visited[edges[j].to]) {
                        visited[edges[j].to] = true;
                        stack.push_back(edges[j].to);
                    }
                }
            }
        }
    }

    cout << dist[n] << endl;

    return 0;
}

// g++ -std=c++20 -o a cses_1673.cpp && ./a < a.in