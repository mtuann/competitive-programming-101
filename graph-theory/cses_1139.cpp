#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

const int MAXN = 200005;

vector<int> adj[MAXN];
int color[MAXN];
int result[MAXN];

void dfs(int node, int parent, vector<set<int>>& color_sets) {
    color_sets[node].insert(color[node]);
    
    for (int child : adj[node]) {
        if (child == parent) continue;
        
        dfs(child, node, color_sets);
        
        // Always merge the smaller set into the larger set
        if (color_sets[child].size() > color_sets[node].size()) {
            swap(color_sets[child], color_sets[node]);
        }
        
        for (int c : color_sets[child]) {
            color_sets[node].insert(c);
        }
        color_sets[child].clear(); // Clear the child set to save memory
    }
    
    result[node] = color_sets[node].size();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int n;
    cin >> n;
    
    for (int i = 1; i <= n; i++) {
        cin >> color[i];
    }
    
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    
    vector<set<int>> color_sets(n + 1);
    
    dfs(1, -1, color_sets);
    
    for (int i = 1; i <= n; i++) {
        cout << result[i] << " ";
    }
    
    return 0;
}
