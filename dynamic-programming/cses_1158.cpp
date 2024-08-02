#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
int n, x;

int main() {
    
    cin >> n >> x;
    
    vector<int> prices(n), pages(n);
    
    for (int i = 0; i < n; ++i) {
        cin >> prices[i];
    }
    
    for (int i = 0; i < n; ++i) {
        cin >> pages[i];
    }
    
    vector<int> dp(x + 1, 0);  // DP array to store the max pages for each budget
    
    for (int i = 0; i < n; ++i) {
        int price = prices[i];
        int page = pages[i];
        // Traverse dp array in reverse to prevent recomputation with the same book
        for (int j = x; j >= price; --j) {
            dp[j] = max(dp[j], dp[j - price] + page);
        }
    }
    
    cout << dp[x] << endl;
    
    return 0;
}
