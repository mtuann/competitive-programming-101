#include <iostream>
#include <vector>
#include <queue>

using namespace std;

void findCourseOrder(int n, int m, vector<pair<int, int>> &edges) {
    vector<vector<int>> graph(n + 1);
    vector<int> in_degree(n + 1, 0);
    
    // Build the graph and in-degree array
    for (auto edge : edges) {
        int a = edge.first;
        int b = edge.second;
        graph[a].push_back(b);
        in_degree[b]++;
    }
    
    queue<int> q;
    vector<int> order;
    
    // Add all nodes with in-degree 0 to the queue
    for (int i = 1; i <= n; i++) {
        if (in_degree[i] == 0) {
            q.push(i);
        }
    }
    
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        order.push_back(node);
        
        for (int neighbor : graph[node]) {
            in_degree[neighbor]--;
            if (in_degree[neighbor] == 0) {
                q.push(neighbor);
            }
        }
    }
    
    // If we processed all nodes, we have a valid topological order
    if (order.size() == n) {
        for (int course : order) {
            cout << course << " ";
        }
        cout << endl;
    } else {
        cout << "IMPOSSIBLE" << endl;
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> edges(m);
    
    for (int i = 0; i < m; i++) {
        cin >> edges[i].first >> edges[i].second;
    }
    
    findCourseOrder(n, m, edges);
    
    return 0;
}
