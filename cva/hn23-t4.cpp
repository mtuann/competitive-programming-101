#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <cstring>
#include <algorithm>
#include <climits>
using namespace std;

const int MAXN = 2e5 + 10;
vector<int> adj[MAXN];
int child[MAXN];
int depth[MAXN];
int salary[MAXN];
int boss[MAXN];
int n, q;
int dp[MAXN][2];
int gtln[MAXN][2];
int bat[MAXN];
bool meoco = 0;
bool issub2() {
    for (int i = 2; i <= n; i++) {
        if (salary[boss[i]] < salary[i]) return 0;
    }
    return 1;
}
bool issub1() {
    return (n <= 15 && q == 1);
}
bool issub3() {
    for (int i = 2; i <= n; i++) {
        if (boss[i] != i-1) return 0;
    }
    return 1;
}

void dfs1(int u) {
    if (adj[u].size() == 0) {
        return;
    }
    for (int i = 0; i < adj[u].size(); i++) {
        int v = adj[u][i];
        depth[v] = depth[u] + 1;
        dfs1(v);
        child[u] += child[v];
    }
    return;
}
void dfs2(int u) {
    if (adj[u].size() == 0) {
        dp[u][1] = 1;
        dp[u][0] = 0;
        gtln[u][1] = salary[u];
        gtln[u][0] = 0;
        return;
    }
    for (int i = 0; i < adj[u].size(); i++) {
        int v = adj[u][i];
        dfs2(v);
        if (salary[u] > gtln[v][1]) {
        }
    }

}
namespace sub1 {
    void solve() {
        int kq = 1;
        int x;
        cin >> x;
        for (int mask = 0; mask < (1 << n); mask++) {
            bool co = 1;
            for (int i = 0; i < n; i++) {
                if ((1 << i) & mask) {
                    int node = i + 1;
                    if (depth[node] <= depth[x] && node != x) {
                        co = 0;
                        break;
                    }
                    if (1 << (x-1) & mask && salary[x] < salary[node]) {
                        co = 0;
                        break;
                    }
                    int gt = salary[node];
                    while (depth[node] > depth[x]) {
                        if ((1 << (node - 1)) & mask) {
                            if (salary[node] < gt) {
                                co = 0;
                                break;
                            }
                            gt = salary[node];
                        }
                        node = boss[node];
                    }
                    if (node != x) {
                        co = 0;
                        break;
                    }
                }
            }
            if (co == 1) {
                kq = max(kq, __builtin_popcount(mask));
            }
        }
        cout << kq;
        return;
    }

}
namespace sub2 {
    void solve() {
        for (int i = 0; i < q; i++) {
            int x;
            cin >> x;
            cout << child[x] << endl;
        }
        return;
    }
}
namespace sub3 {

    int binarySearch(int arr[], int size, int value) {
        int low = 0, high = size - 1;
        while (low <= high) {
            int mid = (low + high) / 2;
            if (arr[mid] >= value)
                high = mid - 1;
            else
                low = mid + 1;
        }
        return low; // returns the position where `value` should be inserted
    }


    void solve() {
        int dp[MAXN];
        int LIS[MAXN]; // This will store the elements of the LIS
        int length = 0;  // Current length of the LIS

        fill(dp, dp + n + 1, 1);

        // for (int i = n; i >= 1; i--) {
        //     for (int j = i + 1; j <= n; j++) {
        //         if (salary[i] >= salary[j]) {
        //             dp[i] = max(dp[i], dp[j] + 1);
        //         }
        //     }
        // }

        for (int i = n; i >= 1; --i) {
            int pos = binarySearch(LIS, length, salary[i]);
            
            if (pos == length) {
                // If the position is at the end of the current LIS, extend the LIS
                LIS[length++] = salary[i];
            } else {
                // Replace the found position with the current value
                LIS[pos] = salary[i];
            }
        
            // dp[i] = distance(LIS.begin(), it) + 1;
            dp[i] = pos + 1;
            // cout << i << " " << dp[i] << endl;
        }
        // cout << "END" << endl;

        for (int i = 0; i < q; i++) {
            int x;
            cin >> x;
            cout << dp[x] << endl;
        }

    }


}
int main() {
    // freopen("CONGTY.INP", "r", stdin);
    // freopen("CONGTY.OUT", "w", stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> q;
    fill(child, child + n + 1, 1);
    for (int i = 1; i <= n; i++) {
        cin >> salary[i];
    }
    for (int i = 2; i <= n; i++) {
        int x;
        cin >> x;
        boss[i] = x;
        adj[x].push_back(i);
    }
    depth[1] = 0;
    dfs1(1);
    // if (issub1()) {sub1::solve(); return 0;}
    // if (issub2()) {sub2::solve(); return 0;}
    if (issub3()) {sub3::solve(); return 0;}
    return 0;
}
// g++ -std=c++14 -o a hn23-t4.cpp && ./a < a.in
