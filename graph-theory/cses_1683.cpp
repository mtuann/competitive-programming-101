#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

const int MAXN = 100000;
vector<int> graph[MAXN], reverseGraph[MAXN];
vector<int> scc[MAXN];
bool visited[MAXN];
stack<int> nodesStack;
int component[MAXN];
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
        --a; --b; // Convert to 0-based indexing
        graph[a].push_back(b);
        reverseGraph[b].push_back(a);
    }

    // Step 1: Perform DFS to get finishing times
    fill(visited, visited + n, false);
    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            dfs1(i);
        }
    }

    // Step 2: Reverse DFS using finish times to find SCCs
    fill(visited, visited + n, false);
    int compCount = 0;
    while (!nodesStack.empty()) {
        int u = nodesStack.top();
        nodesStack.pop();
        if (!visited[u]) {
            dfs2(u, compCount++);
        }
    }

    // Output results
    cout << compCount << endl;
    for (int i = 0; i < n; ++i) {
        cout << component[i] + 1 << " "; // Convert back to 1-based indexing
    }
    cout << endl;

    return 0;
}
