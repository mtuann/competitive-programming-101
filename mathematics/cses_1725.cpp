#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

const int MAX_SUM = 600;  // Since the maximum sum with 100 dice is 600 (100 * 6)

int main() {
    int n, a, b;
    cin >> n >> a >> b;

    // dp[i][j] represents the probability of getting sum j with i dice rolls
    vector<vector<double>> dp(n + 1, vector<double>(MAX_SUM + 1, 0.0));

    // Base case: There's one way to get sum 0 with 0 dice rolls (probability = 1.0)
    dp[0][0] = 1.0;

    // Dynamic programming: fill the dp table
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= 6 * (i - 1); ++j) {
            for (int k = 1; k <= 6; ++k) {
                if (j + k <= MAX_SUM) {
                    dp[i][j + k] += dp[i-1][j] / 6.0;
                }
            }
        }
    }

    // Sum the probabilities of achieving a sum between a and b with exactly n dice rolls
    double result = 0.0;
    for (int sum = a; sum <= b; ++sum) {
        result += dp[n][sum];
    }

    // Output the result rounded to 6 decimal places
    cout << fixed << setprecision(6) << result << endl;

    return 0;
}
