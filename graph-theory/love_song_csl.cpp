// http://csloj.ddns.net/contest/87/problem/3

#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

const int INF = 1e9;

class BipartiteGraph {
private:
    int num_left;
    int num_right;
    vector<vector<int>> adjacency_list;
    vector<int> pair_u, pair_v, dist;
    
    bool bfs() {
        queue<int> q;
        dist.assign(num_left + 1, INF);
        
        for (int u = 1; u <= num_left; ++u) {
            if (pair_u[u] == 0) {
                dist[u] = 0;
                q.push(u);
            }
        }
        
        bool found_augmenting_path = false;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            if (dist[u] < INF) {
                for (int v : adjacency_list[u]) {
                    if (pair_v[v] == 0) {
                        found_augmenting_path = true;
                    } else if (dist[pair_v[v]] == INF) {
                        dist[pair_v[v]] = dist[u] + 1;
                        q.push(pair_v[v]);
                    }
                }
            }
        }
        
        return found_augmenting_path;
    }
    
    bool dfs(int u) {
        if (u != 0) {
            for (int v : adjacency_list[u]) {
                if (pair_v[v] == 0 || (dist[pair_v[v]] == dist[u] + 1 && dfs(pair_v[v]))) {
                    pair_u[u] = v;
                    pair_v[v] = u;
                    return true;
                }
            }
            dist[u] = INF;
            return false;
        }
        return true;
    }
    
public:
    BipartiteGraph(int num_left, int num_right) {
        this->num_left = num_left;
        this->num_right = num_right;
        adjacency_list.resize(num_left + 1);
        pair_u.assign(num_left + 1, 0);
        pair_v.assign(num_right + 1, 0);
        dist.resize(num_left + 1);
    }
    
    void add_edge(int u, int v) {
        adjacency_list[u].push_back(v);
    }
    
    int hopcroft_karp() {
        int matching_size = 0;
        while (bfs()) {
            for (int u = 1; u <= num_left; ++u) {
                if (pair_u[u] == 0) {
                    dist.assign(num_left + 1, INF);
                    if (dfs(u)) {
                        ++matching_size;
                    }
                }
            }
        }
        return matching_size;
    }

    vector<pair<int, int>> get_matching_pairs() {
        vector<pair<int, int>> matching_pairs;
        for (int u = 1; u <= num_left; ++u) {
            if (pair_u[u] != 0) {
                matching_pairs.emplace_back(u, pair_u[u]);
            }
        }
        return matching_pairs;
    }
};

int num_left, num_right, num_edges;
int a[10010], b[10010];

int main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

    cin >> num_left;
    cin >> num_right;
    for (int i = 1; i <= num_left; ++i) {
        cin >> a[i];
    }
    for (int i = 1; i <= num_right; ++i) {
        cin >> b[i];
    }
    
    BipartiteGraph graph(num_left, num_right);

    for (int i = 1; i <= num_left; ++i) {
        for (int j = 1; j <= num_right; ++j) {
            if (a[i] != b[j]) {
                num_edges++;
                graph.add_edge(i, j);

            }
        }
    }
    
    int max_matching_size = graph.hopcroft_karp();
    cout << max_matching_size << endl;
    

    vector<pair<int, int>> matching_pairs = graph.get_matching_pairs();
    for (auto& p : matching_pairs) {
        cout << p.first << " " << p.second << endl;
    }

    return 0;
}
// Time complexity: O(V * E)
// Space complexity: O(V + E)
// V: number of vertices, E: number of edges
// g++ -std=c++17 -o a love_song_csl.cpp && ./a < a.in
