#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

vector<vector<int>> adj;
vector<int> visited, parent;
int start, end_cycle;

bool dfs(int v) {
    visited[v] = 1;
    for (int u : adj[v]) {
        if (!visited[u]) {
            parent[u] = v;
            if (dfs(u)) {
                return true;
            }
        } else if (visited[u] == 1) {
            start = u;
            end_cycle = v;
            return true;
        }
    }
    visited[v] = 2;
    return false;
}

int main() {
    int n, m;
    cin >> n >> m;

    adj.resize(n + 1);
    visited.assign(n + 1, 0);
    parent.assign(n + 1, -1);

    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
    }

    start = -1;
    for (int i = 1; i <= n; ++i) {
        if (!visited[i] && dfs(i)) {
            break;
        }
    }

    if (start == -1) {
        cout << "IMPOSSIBLE" << endl;
    } else {
        vector<int> cycle;
        cycle.push_back(start);
        for (int v = end_cycle; v != start; v = parent[v]) {
            cycle.push_back(v);
        }
        cycle.push_back(start);
        reverse(cycle.begin(), cycle.end());

        cout << cycle.size() << endl;
        for (int v : cycle) {
            cout << v << " ";
        }
        cout << endl;
    }

    return 0;
}
// g++ -std=c++17 -O2 -Wall cses_1678.cpp -o a && ./a < a.in