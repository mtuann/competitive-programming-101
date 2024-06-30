// https://oj.vnoi.info/problem/graph_
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 100005;
vector<int> adj[MAXN];
bool visited[MAXN];
int disc[MAXN], low[MAXN], parent[MAXN];
bool articulation_point[MAXN];
vector<pair<int, int>> bridges;

int time_counter;

void dfs(int u) {
    printf("dfs(%d)\n", u);
    visited[u] = true;
    disc[u] = low[u] = ++time_counter;
    int children = 0;

    for (int v : adj[u]) {
        if (!visited[v]) {
            children++;
            parent[v] = u;
            printf("  dfs(%d)\n", v);
            dfs(v);

            low[u] = min(low[u], low[v]);

            // If u is an articulation point
            if (parent[u] == -1 && children > 1)
                articulation_point[u] = true;

            if (parent[u] != -1 && low[v] >= disc[u])
                articulation_point[u] = true;

            // If u-v is a bridge
            if (low[v] > disc[u])
                bridges.push_back({u, v});
        }
        else if (v != parent[u]) {
            low[u] = min(low[u], disc[v]);
        }
    }
}

void findArticulationPointsAndBridges(int n) {
    time_counter = 0;
    fill(visited, visited + n, false);
    fill(disc, disc + n, -1);
    fill(low, low + n, -1);
    fill(parent, parent + n, -1);
    fill(articulation_point, articulation_point + n, false);
    bridges.clear();

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            dfs(i);
        }
    }

    // cout << "Articulation points:\n";
    int cnt_articulation_points = 0;
    for (int i = 0; i < n; i++) {
        if (articulation_point[i]) {
            // cout << i + 1<< " ";
            cnt_articulation_points++;
        }
    }
    // cout << "\n";
    cout << cnt_articulation_points << " " << bridges.size() << "\n";

    
    // int cnt_bridges = bridges.size();
    // cout << cnt_bridges << "\n";
    cout << "Bridges:\n";
    for (auto &bridge : bridges) {
        cout << bridge.first + 1 << " - " << bridge.second + 1<< "\n";
    }
    // print disc, low and parent
    for (int i = 0; i < n; i++) {
        cout << "disc[" << i + 1 << "] = " << disc[i] << ", low[" << i + 1 << "] = " << low[i] << ", parent[" << i + 1 << "] = " << parent[i] + 1 << "\n";
    }

}

int main() {

    int n, m;
    // cout << "Enter number of vertices and edges: ";
    cin >> n >> m;

    // cout << "Enter the edges (u v):\n";
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    findArticulationPointsAndBridges(n);

    return 0;
}
// g++ -std=c++17 -o a articulation_points_and_bridges.cpp && ./a < a.in
