#include <iostream>
#include <vector>
#include <limits.h>

using namespace std;

void floydWarshall(vector<vector<int>>& graph, int n) {
    vector<vector<int>> dist = graph;

    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX && dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    cout << "The following matrix shows the shortest distances between every pair of vertices:\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (dist[i][j] == INT_MAX) {
                cout << "INF ";
            } else {
                cout << dist[i][j] << " ";
            }
        }
        cout << endl;
    }
}

int main() {
    int n, m;
    cout << "Enter the number of vertices (n): ";
    cin >> n;
    cout << "Enter the number of edges (m): ";
    cin >> m;

    vector<vector<int>> graph(n, vector<int>(n, INT_MAX));

    for (int i = 0; i < n; ++i) {
        graph[i][i] = 0;
    }

    cout << "Enter the edges (u v w) where u and v are vertices (0-based index) and w is the weight:\n";
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u][v] = w;
    }

    floydWarshall(graph, n);

    return 0;
}
