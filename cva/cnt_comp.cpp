#include <iostream>
#include <vector>
#include <set>
using namespace std;

const int MAXN = 20001;

vector<int> graph[MAXN];
bool visited[MAXN];
int original_components;

void dfs(int node) {
    visited[node] = true;
    for (int neighbor : graph[node]) {
        if (!visited[neighbor]) {
            dfs(neighbor);
        }
    }
}

int countComponents(int n) {
    int components = 0;
    fill(visited, visited + n + 1, false);
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            dfs(i);
            components++;
        }
    }
    return components;
}

int main() {
    int n, m;
    cin >> n >> m;

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    original_components = countComponents(n);

    for (int i = 1; i <= n; i++) {
        set<int> unique_components;
        visited[i] = true; // Mark vertex i as "removed"
        for (int neighbor : graph[i]) {
            if (!visited[neighbor]) {
                unique_components.insert(neighbor);
                dfs(neighbor);
            }
        }
        visited[i] = false; // Unmark the vertex

        int new_components = original_components - 1 + unique_components.size();
        cout << new_components << endl;
    }

    return 0;
}
