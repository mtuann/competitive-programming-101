#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int INF = 1e9; // A large number representing infinity

int main() {
    int n, x;
    cin >> n >> x;
    
    vector<int> coins(n);
    for (int i = 0; i < n; ++i) {
        cin >> coins[i];
    }
    
    vector<int> dp(x + 1, INF);
    dp[0] = 0; // Base case: no coins are needed to make the sum 0
    
    for (int coin : coins) {
        for (int j = coin; j <= x; ++j) {
            if (dp[j - coin] != INF) {
                dp[j] = min(dp[j], dp[j - coin] + 1);
            }
        }
    }
    
    if (dp[x] == INF) {
        cout << -1 << endl;
    } else {
        cout << dp[x] << endl;
    }
    
    return 0;
}
