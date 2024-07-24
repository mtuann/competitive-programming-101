#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

const int MAXN = 100000;
vector<int> adj[MAXN + 1];
vector<int> circuit;
bool visited[MAXN + 1];
int degree[MAXN + 1];

void find_eulerian_circuit(int u) {
    stack<int> curr_path;
    vector<int> temp_path;
    curr_path.push(u);
    
    while (!curr_path.empty()) {
        int v = curr_path.top();
        if (adj[v].empty()) {
            temp_path.push_back(v);
            curr_path.pop();
        } else {
            int next_v = adj[v].back();
            adj[v].pop_back();
            // Remove edge v-next_v from adj[next_v]
            adj[next_v].erase(find(adj[next_v].begin(), adj[next_v].end(), v));
            curr_path.push(next_v);
        }
    }
    
    circuit.assign(temp_path.rbegin(), temp_path.rend());
}

bool is_connected(int n) {
    // Check if all vertices with non-zero degree are connected
    fill(visited, visited + n + 1, false);
    
    // Find the first vertex with non-zero degree
    int start = 1;
    for (int i = 1; i <= n; i++) {
        if (degree[i] > 0) {
            start = i;
            break;
        }
    }
    
    // Perform DFS to check connectivity
    stack<int> stk;
    stk.push(start);
    visited[start] = true;
    
    while (!stk.empty()) {
        int u = stk.top();
        stk.pop();
        
        for (int v : adj[u]) {
            if (!visited[v]) {
                visited[v] = true;
                stk.push(v);
            }
        }
    }
    
    // Check if all vertices with non-zero degree are visited
    for (int i = 1; i <= n; i++) {
        if (degree[i] > 0 && !visited[i]) {
            return false;
        }
    }
    return true;
}

bool is_eulerian_circuit_possible(int n) {
    // Check if all vertices have an even degree
    for (int i = 1; i <= n; i++) {
        if (degree[i] % 2 != 0) {
            return false;
        }
    }
    return is_connected(n);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
        degree[a]++;
        degree[b]++;
    }
    
    if (!is_eulerian_circuit_possible(n)) {
        cout << "IMPOSSIBLE" << endl;
        return 0;
    }
    
    find_eulerian_circuit(1);
    
    for (int v : circuit) {
        cout << v << " ";
    }
    cout << endl;
    
    return 0;
}


// #include <iostream>
// #include <vector>
// #include <stack>
// #include <algorithm>

// using namespace std;

// const int MAXN = 100000;
// vector<int> adj[MAXN + 1];
// vector<int> circuit;
// bool visited[MAXN + 1];
// int degree[MAXN + 1];

// void find_eulerian_circuit(int u) {
//     stack<int> curr_path;
//     vector<int> temp_path;
//     curr_path.push(u);
    
//     while (!curr_path.empty()) {
//         int v = curr_path.top();
//         if (adj[v].empty()) {
//             temp_path.push_back(v);
//             curr_path.pop();
//         } else {
//             int next_v = adj[v].back();
//             adj[v].pop_back();
//             // Remove edge v-next_v from adj[next_v]
//             adj[next_v].erase(find(adj[next_v].begin(), adj[next_v].end(), v));
//             curr_path.push(next_v);
//         }
//     }
    
//     circuit.assign(temp_path.rbegin(), temp_path.rend());
// }

// bool is_connected(int n) {
//     // Check if all vertices with non-zero degree are connected
//     fill(visited, visited + n + 1, false);
    
//     // Find the first vertex with non-zero degree
//     int start = 1;
//     for (int i = 1; i <= n; i++) {
//         if (degree[i] > 0) {
//             start = i;
//             break;
//         }
//     }
    
//     // Perform DFS to check connectivity
//     stack<int> stk;
//     stk.push(start);
//     visited[start] = true;
    
//     while (!stk.empty()) {
//         int u = stk.top();
//         stk.pop();
        
//         for (int v : adj[u]) {
//             if (!visited[v]) {
//                 visited[v] = true;
//                 stk.push(v);
//             }
//         }
//     }
    
//     // Check if all vertices with non-zero degree are visited
//     for (int i = 1; i <= n; i++) {
//         if (degree[i] > 0 && !visited[i]) {
//             return false;
//         }
//     }
//     return true;
// }

// bool is_eulerian_circuit_possible(int n) {
//     // Check if all vertices have an even degree
//     for (int i = 1; i <= n; i++) {
//         if (degree[i] % 2 != 0) {
//             return false;
//         }
//     }
//     return is_connected(n);
// }

// int main() {
//     ios::sync_with_stdio(false);
//     cin.tie(0);

//     int n, m;
//     cin >> n >> m;
    
//     for (int i = 0; i < m; i++) {
//         int a, b;
//         cin >> a >> b;
//         adj[a].push_back(b);
//         adj[b].push_back(a);
//         degree[a]++;
//         degree[b]++;
//     }
    
//     if (!is_eulerian_circuit_possible(n)) {
//         cout << "IMPOSSIBLE" << endl;
//         return 0;
//     }
    
//     find_eulerian_circuit(1);
    
//     for (int v : circuit) {
//         cout << v << " ";
//     }
//     cout << endl;
    
//     return 0;
// }
