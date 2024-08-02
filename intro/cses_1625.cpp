#include <iostream>
#include <vector>

using namespace std;

// Define the directions
const int dx[] = {1, -1, 0, 0};
const int dy[] = {0, 0, -1, 1};
const char directions[] = {'D', 'U', 'L', 'R'};

int main() {
    string description;
    cin >> description;
    
    int n = 7; // Size of the grid
    int steps = description.size();
    
    // Initialize the DP table
    vector<vector<vector<long long>>> dp(n, vector<vector<long long>>(n, vector<long long>(steps + 1, 0)));
    dp[0][0][0] = 1; // Starting point
    
    for (int step = 0; step < steps; ++step) {
        char ch = description[step];
        vector<vector<vector<long long>>> new_dp(n, vector<vector<long long>>(n, vector<long long>(steps + 1, 0)));
        
        for (int x = 0; x < n; ++x) {
            for (int y = 0; y < n; ++y) {
                if (dp[x][y][step] > 0) {
                    for (int d = 0; d < 4; ++d) {
                        int nx = x + dx[d];
                        int ny = y + dy[d];
                        if (nx >= 0 && nx < n && ny >= 0 && ny < n) {
                            if (ch == '?' || ch == directions[d]) {
                                new_dp[nx][ny][step + 1] += dp[x][y][step];
                            }
                        }
                    }
                }
            }
        }
        dp = new_dp;
    }
    
    // The result is the number of ways to reach (6, 0) at step 48
    cout << dp[6][0][steps] << endl;

    return 0;
}
