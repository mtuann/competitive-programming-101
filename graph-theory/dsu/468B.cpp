// https://codeforces.com/problemset/problem/468/B
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <cstring>

using namespace std;

const int N = 1e5 + 5;
int n, a, b;
int p[N];
map<int, int> mp;
vector<int> g[N];
int deg[N];
int ans[N];
bool vis[N];
bool special[N];

void dfs(int u, vector<int> &chain) {
    // cout << "dfs " << u << "\n";
    vis[u] = 1;
    for (int v : g[u]) {
        if (vis[v]) continue;
        deg[v]--;
        chain.push_back(v);
        // cout << "v " << v << " deg " << deg[v] << "\n";
        if (deg[v] == 1) {
            dfs(v, chain);
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> a >> b;
    memset(deg, 0, sizeof deg);
    memset(ans, 0xff, sizeof ans);
    memset(vis, 0, sizeof vis);

    for (int i = 0; i < n; i++) {
        cin >> p[i];
        mp[p[i]] = i;
    }
    int cnt = 0;
    // if (a > b) swap(a, b);
    if (a == b) {
        // process special case
        for (int i = 0; i < n; i++) {
            if (!mp.count(a - p[i])) {
                cout << "NO\n";
                return 0;
            }            
        }
        
        cout << "YES\n";
        for (int i = 0; i < n; i++) {
            cout << 0 << " ";
        }
        return 0;
    }
    
    for (int i = 0; i < n; i++) {

        int u = p[i];
        int au = a - u;
        int bu = b - u;

        if (mp.count(au)) {
            g[i].push_back(mp[au]);
            cnt++;
            deg[i]++;
        }
        if (mp.count(bu)) {
            g[i].push_back(mp[bu]);
            cnt++;
            deg[i]++;
        }

        if (u * 2 == a || u * 2 == b) {
            special[i] = 1;
        } else {
            special[i] = 0;
        }
    }

    for (int i = 0; i < n; i++) {
        if (deg[i] == 0) {
            cout << "NO\n";
            return 0;
        }
    }

    for (int i = 0; i < n; i++) {
        
        if (special[i]) {
            // cout << i << " special " << "deg " << deg[i] << "\n";
            if (deg[i] == 1) {
                if (a - p[i] == p[i]) {
                    ans[i] = 0;
                    continue;
                } else if (b - p[i] == p[i]) {
                    ans[i] = 1;
                    continue;
                } else {
                    vector<int> chain;
                    chain.push_back(i);
                    dfs(i, chain);
                    for (int j = 0; j < int(chain.size()); j+=2) {
                        if (p[chain[j]] + p[chain[j + 1]] == a) {
                            ans[chain[j]] = 0;
                            ans[chain[j + 1]] = 0;
                        } else {
                            ans[chain[j]] = 1;
                            ans[chain[j + 1]] = 1;
                        }
                        vis[chain[j]] = vis[chain[j + 1]] = 1;
                    }

                }
                
            }
        } else {
            
            if (deg[i] == 1 && !vis[i]) {
                vector<int> chain;
                chain.push_back(i);
                        
                dfs(i, chain);
                // cout << int(chain.size()) << "\n";
                if (int(chain.size()) % 2 == 1) {
                    cout << "NO\n";
                    return 0;
                }
                
                for (int j = 0; j < int(chain.size()); j+=2) {
                    if (p[chain[j]] + p[chain[j + 1]] == a) {
                        ans[chain[j]] = 0;
                        ans[chain[j + 1]] = 0;
                    } else {
                        ans[chain[j]] = 1;
                        ans[chain[j + 1]] = 1;
                    }
                    vis[chain[j]] = vis[chain[j + 1]] = 1;
                }
            }

        }

        
    }

    cout << "YES\n";
    for (int i = 0; i < n; i++) {
        cout << ans[i] << " ";
    }
    
    return 0;
}

// g++ -std=c++17 -o a 468B.cpp && ./a < a.in
// https://codeforces.com/blog/entry/130227