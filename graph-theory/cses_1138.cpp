#include <iostream>
#include <vector>
using namespace std;

const int MAXN = 200005;
vector<int> adj[MAXN];  // adjacency list
int start[2 * MAXN], values[MAXN], euler[2 * MAXN], end_time[2 * MAXN];
long long segtree[8 * MAXN];  // Segment Tree array
int timer = 0;

// Segment Tree Operations
void build_segment_tree(int idx, int l, int r) {
    if (l == r) {
        segtree[idx] = euler[l];  // Initialize leaf with Euler tour value
    } else {
        int mid = (l + r) / 2;
        build_segment_tree(2 * idx, l, mid);
        build_segment_tree(2 * idx + 1, mid + 1, r);
        segtree[idx] = segtree[2 * idx] + segtree[2 * idx + 1];  // Sum the children
    }
}

// Update the value in the segment tree at position `pos` (1-indexed)
void segment_tree_update(int idx, int l, int r, int pos, int new_value) {
    if (l == r) {
        segtree[idx] = new_value;  // Update the leaf node
    } else {
        int mid = (l + r) / 2;
        if (pos <= mid) {
            segment_tree_update(2 * idx, l, mid, pos, new_value);
        } else {
            segment_tree_update(2 * idx + 1, mid + 1, r, pos, new_value);
        }
        segtree[idx] = segtree[2 * idx] + segtree[2 * idx + 1];  // Recalculate the sum
    }
}

// Query the sum in the range [ql, qr] (1-indexed)
long long segment_tree_query(int idx, int l, int r, int ql, int qr) {
    if (ql > r || qr < l) return 0;  // No overlap
    if (ql <= l && qr >= r) return segtree[idx];  // Complete overlap
    int mid = (l + r) / 2;
    long long left_sum = segment_tree_query(2 * idx, l, mid, ql, qr);
    long long right_sum = segment_tree_query(2 * idx + 1, mid + 1, r, ql, qr);
    return left_sum + right_sum;  // Sum both sides
}

// DFS to generate the Euler Tour and calculate entry times
void dfs(int node, int parent) {
    start[node] = ++timer;
    euler[timer] = values[node];  // save the value of node in the Euler tour array
    
    for (int neighbor : adj[node]) {
        if (neighbor != parent) {
            dfs(neighbor, node);
        }
    }
    end_time[node] = ++timer;
    euler[timer] = -values[node];  // save the negative value of node in the Euler tour array
}

// Update the value of a node in the Segment Tree
void update_value(int node, int new_value, int n) {
    segment_tree_update(1, 1, 2 * n, start[node], new_value);
    segment_tree_update(1, 1, 2 * n, end_time[node], -new_value);
    values[node] = new_value;
}

// Query the sum from the root to node `s`
long long query_sum(int node, int n) {
    return segment_tree_query(1, 1, 2 * n, 1, start[node]);  // Query from start[1] to start[node]
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, q;
    cin >> n >> q;

    // Read the values of nodes
    for (int i = 1; i <= n; i++) {
        cin >> values[i];
    }

    // Read the edges and create the adjacency list
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // Run DFS to create the Euler Tour and initialize the entry times
    dfs(1, -1);

    // Build the segment tree based on the Euler tour values
    build_segment_tree(1, 1, 2 * n);

    // Process queries
    while (q--) {
        int type;
        cin >> type;

        if (type == 1) {
            // Update the value of a node
            int s, x;
            cin >> s >> x;
            update_value(s, x, n);
        } else if (type == 2) {
            // Query the sum from root to node `s`
            int s;
            cin >> s;
            cout << query_sum(s, n) << endl;
        }
    }

    return 0;
}

// #include <iostream>
// #include <vector>
// using namespace std;

// const int MAXN = 200005;
// vector<int> adj[MAXN];  // adjacency list
// int start[MAXN], finish[MAXN], euler[MAXN], values[MAXN];
// int fenwick[MAXN], timer = 0;

// // Fenwick Tree (Binary Indexed Tree) operations
// void fenwick_update(int idx, int delta, int n) {
//     while (idx <= n) {
//         fenwick[idx] += delta;
//         idx += idx & -idx;
//     }
// }

// int fenwick_query(int idx) {
//     int sum = 0;
//     while (idx > 0) {
//         sum += fenwick[idx];
//         idx -= idx & -idx;
//     }
//     return sum;
// }

// // DFS to generate the Euler Tour and calculate entry and exit times
// void dfs(int node, int parent) {
//     start[node] = ++timer;
//     euler[timer] = values[node];  // save the value of node in the Euler tour array
    
//     for (int neighbor : adj[node]) {
//         if (neighbor != parent) {
//             dfs(neighbor, node);
//         }
//     }
//     // euler[timer] = values[node];  // save the value of node in the Euler tour array
    
//     finish[node] = ++timer;
// }

// // Update the value of a node in the Fenwick Tree
// void update_value(int node, int new_value, int n) {
//     int diff = new_value - values[node];//  euler[start[node]];
//     // euler[start[node]] = new_value
//     values[node] = new_value;
//     fenwick_update(start[node], diff, n);
//     fenwick_update(finish[node], -diff, n);
// }

// // Query the sum from the root to node `s`
// int query_sum(int node) {
//     // return sum from st[1] to st[start[node]]
//     return fenwick_query(start[node]);
// }

// int main() {
//     int n, q;
//     cin >> n >> q;

//     // Read the values of nodes
//     for (int i = 1; i <= n; i++) {
//         cin >> values[i];
//     }

//     // Read the edges and create the adjacency list
//     for (int i = 0; i < n - 1; i++) {
//         int u, v;
//         cin >> u >> v;
//         adj[u].push_back(v);
//         adj[v].push_back(u);
//     }

//     // Run DFS to create the Euler Tour and initialize the entry and exit times
//     dfs(1, -1);

//     // Initialize the Fenwick Tree with initial values in the Euler Tour
//     for (int i = 1; i <= n; i++) {
//         // fenwick_update(i, euler[i], n);
//         fenwick_update(start[i], values[i], n);
//         fenwick_update(finish[i], -values[i], n);
//     }
//     // for (int i = 1; i <= n; i++) {
//     //     cout << i << " " << start[i] << " " << finish[i] << endl;
//     // }

//     // for (int i = 1; i <= n; i++) {
//     //     cout << euler[i] << " ";
//     // }
//     // cout << endl;

//     // Process queries
//     while (q--) {
//         int type;
//         cin >> type;

//         if (type == 1) {
//             // Update the value of a node
//             int s, x;
//             cin >> s >> x;
//             update_value(s, x, n);
//         } else if (type == 2) {
//             // Query the sum from root to node `s`
//             int s;
//             cin >> s;
//             cout << query_sum(s) << endl;
//         }
//     }

//     return 0;
// }

// // g++ -std=c++11 -O2 -Wall cses_1138.cpp -o a && ./a < a.in