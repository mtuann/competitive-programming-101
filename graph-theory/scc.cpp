// https://oj.vnoi.info/problem/tjalg
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

const int MAXN = 100005;
vector<int> adj[MAXN];
bool in_stack[MAXN];
int disc[MAXN], low[MAXN];
stack<int> stk;
int time_counter;

void tarjanDFS(int u, vector<vector<int>>& sccs) {
    printf("dfs(%d)\n", u);
    disc[u] = low[u] = ++time_counter;
    stk.push(u);
    in_stack[u] = true;

    for (int v : adj[u]) {
        if (disc[v] == -1) {
            printf("  dfs(%d) from (%d)\n", v, u);
            tarjanDFS(v, sccs);
            low[u] = min(low[u], low[v]);
        } else if (in_stack[v]) {
        // } else {
            printf("  back edge from %d to %d\n", u, v);
            low[u] = min(low[u], disc[v]);
        }
    }

    if (low[u] == disc[u]) {
        // printf("  SCC found at %d\n", u + 1);
        vector<int> scc;
        int w;
        do {
            w = stk.top();
            stk.pop();
            in_stack[w] = false;
            scc.push_back(w);
        } while (w != u);
        sccs.push_back(scc);
    }
}

vector<vector<int>> findSCCs(int n) {
    vector<vector<int>> sccs;
    time_counter = 0;
    fill(disc, disc + n, -1);
    fill(low, low + n, -1);
    fill(in_stack, in_stack + n, false);

    for (int i = 0; i < n; i++) {
        if (disc[i] == -1) {
            tarjanDFS(i, sccs);
        }
    }
    return sccs;
}

int main() {
    int n, m;
    // cout << "Enter number of vertices and edges: ";
    cin >> n >> m;

    // cout << "Enter the edges (u v):\\n";
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
    }

    vector<vector<int>> sccs = findSCCs(n);
    cout << sccs.size() << "\n";
    cout << "Strongly Connected Components:\n";
    for (const auto& scc : sccs) {
        cout << "SCC: ";
        for (int node : scc) {
            cout << node + 1 << " ";
        }
        cout << "\n";
    }

    return 0;
}

// g++ -std=c++17 -o a scc.cpp && ./a < a.in
// Test check in stack
// 5 7
// 1 2
// 2 3
// 3 1
// 4 2
// 4 3
// 4 5
// 5 4