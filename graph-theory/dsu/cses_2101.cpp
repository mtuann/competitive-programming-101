#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2e5 + 5;

vector<int> parent(MAXN), sz(MAXN);

// Initialize the union-find structure
void initUnionFind(int n) {
    for (int i = 0; i < n; i++) {
        parent[i] = i;  // Every node is its own parent
        sz[i] = 1;    // Each component initially has sz 1
    }
}

// Find the root of a set with path compression
int findRoot(int x) {
    if (parent[x] == x)
        return x;
    return parent[x] = findRoot(parent[x]); // Path compression
}

// Union two sets by sz
void unionSets(int x, int y) {
    x = findRoot(x);
    y = findRoot(y);
    if (x != y) {
        if (sz[x] < sz[y])
            swap(x, y);
        parent[y] = x;
        sz[x] += sz[y];
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, m, t; 
    cin >> n >> m >> t;

    vector<pair<int, int>> roads(m);  // List of roads (edges)
    vector<pair<int, int>> queries(t);  // List of queries (city pairs)

    // Input roads
    for (auto &[u, v] : roads) {
        cin >> u >> v;
    }

    // Input queries
    for (auto &[city1, city2] : queries) {
        cin >> city1 >> city2;
    }

    // Binary search range for each query
    vector<pair<int, int>> queryRange(t, {0, m});
    vector<int> answers(t, -1); // Initialize all answers as -1 (no connection yet)

    while (true) {
        initUnionFind(n + 1); // Reset union-find for each binary search iteration
        vector<pair<int, int>> midpoints; // Store the midpoint of binary search range

        // Collect midpoints where the range has not yet converged
        for (int i = 0; i < t; i++) {
            if (queryRange[i].first <= queryRange[i].second) {
                int mid = (queryRange[i].first + queryRange[i].second) / 2;
                midpoints.push_back({mid, i});
            }
        }

        // If no more midpoints, we're done
        if (midpoints.empty()) 
            break;

        // Sort midpoints by the number of roads to check
        sort(midpoints.begin(), midpoints.end());

        int roadIndex = 0;

        // Process roads and evaluate queries
        for (int i = 0; i <= m; i++) {
            if (i > 0) {
                unionSets(roads[i - 1].first, roads[i - 1].second); // Join cities by adding a road
            }

            // Process queries at this number of roads
            while (roadIndex < midpoints.size() && midpoints[roadIndex].first == i) {
                int queryIndex = midpoints[roadIndex].second;
                int city1 = queries[queryIndex].first;
                int city2 = queries[queryIndex].second;

                // Check if the cities in the query are connected
                if (findRoot(city1) == findRoot(city2)) {
                    answers[queryIndex] = i; // Record the earliest moment they are connected
                    queryRange[queryIndex].second = i - 1; // Search in the earlier range
                } else {
                    queryRange[queryIndex].first = i + 1; // Search in the later range
                }
                roadIndex++;
            }
        }
    }

    // Output the results for each query
    for (int answer : answers) {
        cout << answer << '\n';
    }

    return 0;
}
