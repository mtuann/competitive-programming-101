#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> tree;
vector<bool> visited;

pair<int, int> dfs(int node) {
    visited[node] = true;
    pair<int, int> farthest = {0, node};  // {distance, node}
    
    for (int neighbor : tree[node]) {
        if (!visited[neighbor]) {
            pair<int, int> dist = dfs(neighbor);
            dist.first += 1;  // Increase distance by 1 for the current edge
            if (dist.first > farthest.first) {
                farthest = dist;
            }
        }
    }
    
    return farthest;
}

int main() {
    int n;
    cin >> n;

    tree.resize(n + 1);
    visited.resize(n + 1, false);

    // Reading edges
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        tree[a].push_back(b);
        tree[b].push_back(a);
    }

    // First DFS to find the farthest node from an arbitrary node (let's use node 1)
    pair<int, int> first = dfs(1);

    // Reset visited array
    fill(visited.begin(), visited.end(), false);

    // Second DFS from the farthest node found to determine the diameter
    pair<int, int> second = dfs(first.second);

    // Output the diameter of the tree
    cout << second.first << endl;

    return 0;
}
