#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <limits.h>

using namespace std;

const int MAXN = 100000;
vector<int> adj[MAXN + 1];
vector<int> adj_scc[MAXN + 1];
int coins[MAXN + 1];
long long scc_coins[MAXN + 1];
int scc_id[MAXN + 1];
int scc_indegree[MAXN + 1];
bool on_stack[MAXN + 1];
int low[MAXN + 1], disc[MAXN + 1];
int scc_counter, time_counter;
stack<int> stk;

void tarjan(int u) {
    static int time = 0;
    low[u] = disc[u] = ++time;
    stk.push(u);
    on_stack[u] = true;

    for (int v : adj[u]) {
        if (disc[v] == -1) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if (on_stack[v]) {
            low[u] = min(low[u], disc[v]);
        }
    }

    if (low[u] == disc[u]) {
        while (true) {
            int v = stk.top();
            stk.pop();
            on_stack[v] = false;
            scc_id[v] = scc_counter;
            scc_coins[scc_counter] += coins[v];
            if (u == v) break;
        }
        scc_counter++;
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    
    for (int i = 1; i <= n; i++) {
        cin >> coins[i];
    }

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
    }

    // Initialize Tarjan's algorithm variables
    fill(disc, disc + n + 1, -1);
    fill(low, low + n + 1, -1);
    fill(scc_coins, scc_coins + n + 1, 0);
    scc_counter = time_counter = 0;

    // Find all SCCs
    for (int i = 1; i <= n; i++) {
        if (disc[i] == -1) {
            tarjan(i);
        }
    }

    // Build the condensed graph
    for (int u = 1; u <= n; u++) {
        for (int v : adj[u]) {
            if (scc_id[u] != scc_id[v]) {
                adj_scc[scc_id[u]].push_back(scc_id[v]);
                scc_indegree[scc_id[v]]++;
            }
        }
    }

    // Topological sort on the condensed graph
    vector<int> topo_order;
    vector<long long> dp(scc_counter, 0);

    for (int i = 0; i < scc_counter; i++) {
        if (scc_indegree[i] == 0) {
            topo_order.push_back(i);
        }
    }

    for (int i = 0; i < (int)topo_order.size(); i++) {
        int u = topo_order[i];
        for (int v : adj_scc[u]) {
            if (--scc_indegree[v] == 0) {
                topo_order.push_back(v);
            }
        }
    }

    // Dynamic programming to find the maximum coins collectible
    long long max_coins = 0;
    for (int u : topo_order) {
        dp[u] += scc_coins[u];
        max_coins = max(max_coins, dp[u]);
        for (int v : adj_scc[u]) {
            dp[v] = max(dp[v], dp[u]);
        }
    }

    cout << max_coins << endl;

    return 0;
}
