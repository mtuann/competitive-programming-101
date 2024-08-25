#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<int> find_cycles(int n, const vector<int>& teleporters, vector<int>& in_cycle) {
    vector<int> visited(n, -1);
    vector<int> cycle_map(n, -1);
    vector<int> stack;
    int cycle_id = 0;

    auto dfs = [&](int start) {
        stack.clear();
        int node = start;
        while (visited[node] == -1) {
            visited[node] = stack.size();
            stack.push_back(node);
            node = teleporters[node];
        }
        if (visited[node] != -2 && visited[node] < stack.size()) {
            for (int i = visited[node]; i < stack.size(); ++i) {
                cycle_map[stack[i]] = cycle_id;
                in_cycle[stack[i]] = true;
            }
            cycle_id++;
        }
        for (int i = 0; i < stack.size(); ++i) {
            visited[stack[i]] = -2;
        }
    };

    for (int i = 0; i < n; ++i) {
        if (visited[i] == -1) {
            dfs(i);
        }
    }

    return cycle_map;
}

vector<int> bfs_distances(int n, const vector<int>& teleporters, const vector<int>& cycle_map, const vector<int>& in_cycle) {
    vector<int> dist(n, -1);
    queue<int> q;

    for (int i = 0; i < n; ++i) {
        if (in_cycle[i]) {
            dist[i] = 0;
            q.push(i);
        }
    }

    while (!q.empty()) {
        int node = q.front();
        q.pop();
        int next_node = teleporters[node];
        if (dist[next_node] == -1) {
            dist[next_node] = dist[node] + 1;
            q.push(next_node);
        }
    }

    return dist;
}

void solve(int n, int q, const vector<int>& teleporters, const vector<pair<int, int>>& queries) {
    vector<int> in_cycle(n, false);
    vector<int> cycle_map = find_cycles(n, teleporters, in_cycle);
    vector<int> dist = bfs_distances(n, teleporters, cycle_map, in_cycle);

    for (const auto& query : queries) {
        int a = query.first - 1;
        int b = query.second - 1;

        if (in_cycle[a] && in_cycle[b]) {
            if (cycle_map[a] == cycle_map[b]) {
                int steps = (dist[a] - dist[b]) % n;
                if (steps < 0) steps += n;
                cout << steps << "\n";
            } else {
                cout << -1 << "\n";
            }
        } else if (!in_cycle[a] && dist[b] != -1) {
            int result = dist[a] != -1 ? dist[a] + dist[b] : -1;
            cout << result << "\n";
        } else {
            cout << -1 << "\n";
        }
    }
}

int main() {
    int n, q;
    cin >> n >> q;

    vector<int> teleporters(n);
    for (int i = 0; i < n; ++i) {
        cin >> teleporters[i];
        teleporters[i]--; // make 0-indexed
    }

    vector<pair<int, int>> queries(q);
    for (int i = 0; i < q; ++i) {
        cin >> queries[i].first >> queries[i].second;
    }

    solve(n, q, teleporters, queries);

    return 0;
}
