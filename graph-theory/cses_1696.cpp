#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <climits>

using namespace std;

const int MAXN = 500;

vector<int> adj[MAXN + 1];
int pairU[MAXN + 1], pairV[MAXN + 1];
int dist[MAXN + 1];
int n, m;

bool bfs() {
    queue<int> Q;
    for (int u = 1; u <= n; u++) {
        if (pairU[u] == 0) {
            dist[u] = 0;
            Q.push(u);
        } else {
            dist[u] = INT_MAX;
        }
    }
    dist[0] = INT_MAX;

    while (!Q.empty()) {
        int u = Q.front();
        Q.pop();

        if (dist[u] < dist[0]) {
            for (int v : adj[u]) {
                if (dist[pairV[v]] == INT_MAX) {
                    dist[pairV[v]] = dist[u] + 1;
                    Q.push(pairV[v]);
                }
            }
        }
    }
    return dist[0] != INT_MAX;
}

bool dfs(int u) {
    if (u != 0) {
        for (int v : adj[u]) {
            if (dist[pairV[v]] == dist[u] + 1) {
                if (dfs(pairV[v])) {
                    pairV[v] = u;
                    pairU[u] = v;
                    return true;
                }
            }
        }
        dist[u] = INT_MAX;
        return false;
    }
    return true;
}

int hopcroft_karp() {
    memset(pairU, 0, sizeof(pairU));
    memset(pairV, 0, sizeof(pairV));
    memset(dist, 0, sizeof(dist));

    int matching = 0;
    while (bfs()) {
        for (int u = 1; u <= n; u++) {
            if (pairU[u] == 0 && dfs(u)) {
                matching++;
            }
        }
    }
    return matching;
}

int main() {
    int k;
    cin >> n >> m >> k;

    for (int i = 0; i < k; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
    }

    int max_matching = hopcroft_karp();
    cout << max_matching << endl;

    for (int u = 1; u <= n; u++) {
        if (pairU[u] != 0) {
            cout << u << " " << pairU[u] << endl;
        }
    }

    return 0;
}
