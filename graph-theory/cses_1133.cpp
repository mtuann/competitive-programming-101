#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> tree;
vector<int> subtree_size;
vector<long long> distance_sum;

void dfs1(int node, int parent) {
    subtree_size[node] = 1; // Start with size 1 for the node itself
    distance_sum[node] = 0;

    for (int neighbor : tree[node]) {
        if (neighbor == parent) continue;
        dfs1(neighbor, node);
        subtree_size[node] += subtree_size[neighbor];
        distance_sum[node] += distance_sum[neighbor] + subtree_size[neighbor];
    }
}

void dfs2(int node, int parent, int n) {
    for (int neighbor : tree[node]) {
        if (neighbor == parent) continue;
        // Recalculate the distance sum for the child node
        distance_sum[neighbor] = distance_sum[node] + (n - subtree_size[neighbor]) - subtree_size[neighbor];
        dfs2(neighbor, node, n);
    }
}

int main() {
    int n;
    cin >> n;

    tree.resize(n + 1);
    subtree_size.resize(n + 1);
    distance_sum.resize(n + 1);

    // Reading edges
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        tree[a].push_back(b);
        tree[b].push_back(a);
    }

    // Initial DFS to calculate subtree sizes and sum of distances for root node (1)
    dfs1(1, -1);

    // Second DFS to propagate the sum of distances from the root to all nodes
    dfs2(1, -1, n);

    // Output the sum of distances for each node
    for (int i = 1; i <= n; i++) {
        cout << distance_sum[i] << " ";
    }
    cout << endl;

    return 0;
}
