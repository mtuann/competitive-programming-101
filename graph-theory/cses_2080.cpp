#include <iostream>
#include <vector>
#include <map>
using namespace std;

const int MAXN = 200005;

vector<int> adj[MAXN];
int n, k;
long long result = 0;

void dfs(int u, int parent, map<int, int>& dp) {
    dp[0] = 1; // There is 1 way to have a path of length 0

    for (int v : adj[u]) {
        if (v == parent) continue;

        map<int, int> dp_child;
        dfs(v, u, dp_child);

        // Combine paths from dp and dp_child to form paths of length k
        for (auto [length, count] : dp_child) {
            if (length + 1 <= k) {
                result += count * dp[k - length - 1];
            }
        }

        // Update dp to include paths ending at u from v
        for (auto [length, count] : dp_child) {
            dp[length + 1] += count;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> k;

    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    map<int, int> dp;
    dfs(1, -1, dp);

    cout << result << "\n";

    return 0;
}
