#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> tree;
vector<int> dist_from_A;
vector<int> dist_from_B;

void dfs(int node, int parent, vector<int>& dist) {
    for (int neighbor : tree[node]) {
        if (neighbor != parent) {
            dist[neighbor] = dist[node] + 1;
            dfs(neighbor, node, dist);
        }
    }
}

int main() {
    int n;
    cin >> n;

    tree.resize(n + 1);
    dist_from_A.resize(n + 1, 0);
    dist_from_B.resize(n + 1, 0);

    // Reading edges
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        tree[a].push_back(b);
        tree[b].push_back(a);
    }

    // First DFS to find the farthest node from an arbitrary node (let's use node 1)
    dfs(1, -1, dist_from_A);
    int A = max_element(dist_from_A.begin(), dist_from_A.end()) - dist_from_A.begin();

    // Second DFS from the farthest node A to find the farthest node B
    fill(dist_from_A.begin(), dist_from_A.end(), 0);
    dfs(A, -1, dist_from_A);
    int B = max_element(dist_from_A.begin(), dist_from_A.end()) - dist_from_A.begin();

    // Third DFS from node B to get distances from B
    dfs(B, -1, dist_from_B);

    // Output the maximum of distances from A and B for each node
    for (int i = 1; i <= n; i++) {
        cout << max(dist_from_A[i], dist_from_B[i]) << " ";
    }
    cout << endl;

    return 0;
}
