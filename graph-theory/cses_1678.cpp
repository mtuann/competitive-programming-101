#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

const int MAX_N = 100000;

vector<int> graph[MAX_N];
vector<bool> visited;
vector<int> parent;
stack<int> path_stack;
int cycle_start, cycle_end;

bool dfs(int v) {
    visited[v] = true;
    path_stack.push(v);
    
    for (int u : graph[v]) {
        if (!visited[u]) {
            parent[u] = v;
            if (dfs(u)) return true;
        } else if (find(path_stack.begin(), path_stack.end(), u) != path_stack.end()) {
            cycle_start = u;
            cycle_end = v;
            return true;
        }
    }
    
    path_stack.pop();
    return false;
}

int main() {
    int n, m;
    cin >> n >> m;
    
    visited.assign(n + 1, false);
    parent.assign(n + 1, -1);
    
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
    }
    
    cycle_start = -1;
    
    for (int i = 1; i <= n; i++) {
        if (!visited[i] && dfs(i)) break;
    }
    
    if (cycle_start == -1) {
        cout << "IMPOSSIBLE" << endl;
    } else {
        vector<int> cycle;
        cycle.push_back(cycle_start);
        for (int v = cycle_end; v != cycle_start; v = parent[v]) {
            cycle.push_back(v);
        }
        cycle.push_back(cycle_start);
        reverse(cycle.begin(), cycle.end());
        
        cout << cycle.size() << endl;
        for (int v : cycle) {
            cout << v << " ";
        }
        cout << endl;
    }
    
    return 0;
}
