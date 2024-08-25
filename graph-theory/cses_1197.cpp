#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <climits>
 
using namespace std;
 
const long long INF = 1LL<<62;
 
int main() {
    int n, m;
    cin >> n >> m;
    
    vector<tuple<int, int, long long>> edges;
    vector<long long> distance(n + 1, INF);
    vector<int> predecessor(n + 1, -1);
 
    for (int i = 0; i < m; ++i) {
        int a, b;
        long long c;
        cin >> a >> b >> c;
        edges.push_back({a, b, c});
    }
 
    // distance[1] = 0;
    int x = -1;
 
    for (int i = 0; i < n; ++i) {
        x = -1;
        for (const auto& [a, b, c] : edges) {
            // if (distance[a] != INF && distance[a] + c < distance[b]) {
            if (distance[a] + c < distance[b]) {
                distance[b] = distance[a] + c;
                predecessor[b] = a;
                x = b;
            }
        }
    }
 
    if (x == -1) {
        cout << "NO" << endl;
    } else {
        // There is a negative cycle, now find the cycle
        for (int i = 0; i < n; ++i) {
            x = predecessor[x];
        }
 
        vector<int> cycle;
        for (int v = x; ; v = predecessor[v]) {
            cycle.push_back(v);
            if (v == x && cycle.size() > 1) break;
        }
 
        reverse(cycle.begin(), cycle.end());
 
        cout << "YES" << endl;
        for (int v : cycle) {
            cout << v << " ";
        }
        cout << endl;
    }
    // cout << INF << " " << LLONG_MAX << " " << LLONG_MAX + 1 << endl;
    return 0;
}
// g++ -std=c++20 -o a cses_1197.cpp && ./a < a.in