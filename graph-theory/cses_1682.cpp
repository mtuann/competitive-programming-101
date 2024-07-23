#include <iostream>
#include <vector>
#include <stack>

using namespace std;

const int MAXN = 100000;
vector<int> graph[MAXN], reverseGraph[MAXN];
vector<int> scc[MAXN];
bool visited[MAXN];
int component[MAXN];
stack<int> nodesStack;
int n, m;

void dfs1(int u) {
    visited[u] = true;
    for (int v : graph[u]) {
        if (!visited[v]) {
            dfs1(v);
        }
    }
    nodesStack.push(u);
}

void dfs2(int u, int comp) {
    visited[u] = true;
    component[u] = comp;
    scc[comp].push_back(u);
    for (int v : reverseGraph[u]) {
        if (!visited[v]) {
            dfs2(v, comp);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;

    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        --a; --b; // 0-based indexing
        graph[a].push_back(b);
        reverseGraph[b].push_back(a);
    }

    // Step 1: First DFS to order vertices by finish times
    fill(visited, visited + n, false);
    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            dfs1(i);
        }
    }

    // Step 2: Second DFS in reverse order of finishing times
    fill(visited, visited + n, false);
    int compCount = 0;
    while (!nodesStack.empty()) {
        int u = nodesStack.top();
        nodesStack.pop();
        if (!visited[u]) {
            dfs2(u, compCount++);
        }
    }

    // Check if the graph is strongly connected
    if (compCount == 1) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
        // Find two nodes in different SCCs
        int u = 0, v = 0;
        for (int i = 0; i < n; ++i) {
            if (scc[0].size() > 0 && scc[component[i]].size() > 0 && component[i] != component[0]) {
                u = scc[0][0] + 1; // Convert back to 1-based indexing
                v = i + 1; // Convert back to 1-based indexing
                break;
            }
        }
        cout << u << " " << v << "\n";
    }

    return 0;
}
