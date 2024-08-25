#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> tree;
vector<bool> visited;
int max_matching = 0;

void dfs(int node, int parent) {    
    for (int neighbor : tree[node]) {
        if (neighbor == parent) continue;
        dfs(neighbor, node);
        if (!visited[neighbor] && !visited[node]) {
            max_matching++;
            visited[neighbor] = true;
            visited[node] = true;
        }
    }
    
}

int main() {
    int n;
    cin >> n;

    tree.resize(n + 1);
    visited.resize(n + 1, false);

    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        tree[a].push_back(b);
        tree[b].push_back(a);
    }

    // Start DFS from the root node (1)
    dfs(1, -1);

    // Output the maximum matching found
    cout << max_matching << endl;

    return 0;
}
