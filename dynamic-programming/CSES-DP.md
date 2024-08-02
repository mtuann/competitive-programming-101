https://cses.fi/problemset/task/1633

Dice Combinations
=================
To solve this problem, we can use dynamic programming. Let's denote `dp[i]` as the number of ways to achieve the sum `i` using the outcomes of the dice. The recursive relation will be:

\[ dp[i] = dp[i-1] + dp[i-2] + dp[i-3] + dp[i-4] + dp[i-5] + dp[i-6] \]

This relation comes from the fact that to achieve a sum `i`, the last dice throw could have been any of the numbers 1 through 6. Thus, we can add the ways to achieve `i-1`, `i-2`, `i-3`, `i-4`, `i-5`, and `i-6`.

We initialize `dp[0] = 1` because there's exactly one way to achieve the sum 0: by not throwing the dice at all.

Here's the C++ code implementing this approach:

```cpp
#include <iostream>
#include <vector>

const int MOD = 1e9 + 7;

int main() {
    int n;
    std::cin >> n;

    std::vector<int> dp(n + 1, 0);
    dp[0] = 1;  // Base case: there's one way to get the sum 0

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= 6; ++j) {
            if (i - j >= 0) {
                dp[i] = (dp[i] + dp[i - j]) % MOD;
            }
        }
    }

    std::cout << dp[n] << std::endl;
    return 0;
}
```

### Explanation:
1. **Initialization**: We initialize `dp[0]` to 1 because there's exactly one way to achieve the sum 0: by not rolling the dice at all.
2. **DP Table Calculation**:
   - For each `i` from 1 to `n`, we calculate the number of ways to get the sum `i` by considering the last dice throw to be any of the values from 1 to 6.
   - We ensure we don't access out-of-bounds by checking `if (i - j >= 0)`.
   - We use modulo `10^9 + 7` to keep the results within the range of integer values and prevent overflow.
3. **Result**: Finally, we print the value `dp[n]`, which contains the number of ways to achieve the sum `n`.

This approach ensures that we efficiently compute the number of ways to construct the sum `n` by leveraging dynamic programming and avoiding redundant calculations.

---

https://cses.fi/problemset/task/1634/

To solve this problem, we can use dynamic programming. The idea is to maintain an array `dp` where `dp[i]` represents the minimum number of coins required to make a sum `i`.

### Steps:
1. Initialize `dp[0]` to 0 because no coins are needed to make the sum 0.
2. Initialize all other entries in `dp` to a large number (representing infinity) since initially, we assume we can't make any sum other than 0.
3. For each coin value, update the `dp` array.
4. For each sum from the coin value up to the desired sum `x`, update the `dp` value as the minimum of its current value and the value `dp[j - coin] + 1`.

### C++ Code:

```cpp
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
```

### Explanation:
1. **Initialization**:
   - We read the number of coins `n` and the desired sum `x`.
   - We read the coin values into the vector `coins`.
   - We initialize a vector `dp` of size `x + 1` with all values set to `INF` except `dp[0]` which is set to 0 because 0 coins are needed to make the sum 0.

2. **DP Table Calculation**:
   - For each coin in the `coins` vector, we iterate through all possible sums from the coin value up to `x`.
   - For each sum `j`, we update `dp[j]` to be the minimum of its current value and `dp[j - coin] + 1` (if `dp[j - coin]` is not `INF`), which represents using one more coin of the current denomination.

3. **Output**:
   - If `dp[x]` is still `INF`, it means it's not possible to make the sum `x` with the given coins, so we print `-1`.
   - Otherwise, we print `dp[x]`, the minimum number of coins required to make the sum `x`.

This solution ensures that we find the minimum number of coins required to produce the desired sum efficiently using dynamic programming.

---

https://cses.fi/problemset/task/1636
To solve this problem, we need to count the number of distinct ways to produce a sum `x` using the given coins. We can achieve this using dynamic programming.

We'll use a DP array `dp` where `dp[i]` represents the number of ways to make the sum `i` using the available coins. The idea is to iterate through each coin and for each coin, update the `dp` array for all possible sums that can be formed by adding that coin.

### Steps:
1. Initialize `dp[0]` to 1 because there's exactly one way to form the sum 0 (by not using any coins).
2. For each coin, update the `dp` array for all sums from the coin value up to `x`.
3. For each sum `i`, add the number of ways to form the sum `i - coin` to `dp[i]`.

### C++ Code:

```cpp
#include <iostream>
#include <vector>

using namespace std;

const int MOD = 1e9 + 7;

int main() {
    int n, x;
    cin >> n >> x;

    vector<int> coins(n);
    for (int i = 0; i < n; ++i) {
        cin >> coins[i];
    }

    vector<int> dp(x + 1, 0);
    dp[0] = 1;  // Base case: there's one way to get the sum 0

    for (int coin : coins) {
        for (int i = coin; i <= x; ++i) {
            dp[i] = (dp[i] + dp[i - coin]) % MOD;
        }
    }

    cout << dp[x] << endl;

    return 0;
}
```

### Explanation:
1. **Initialization**:
   - We read the number of coins `n` and the desired sum `x`.
   - We read the coin values into the vector `coins`.
   - We initialize a vector `dp` of size `x + 1` with all values set to 0 except `dp[0]` which is set to 1 because there's one way to get the sum 0.

2. **DP Table Calculation**:
   - For each coin in the `coins` vector, we iterate through all possible sums from the coin value up to `x`.
   - For each sum `i`, we update `dp[i]` to include the number of ways to form the sum `i - coin`.

3. **Modulo Operation**:
   - We use modulo `10^9 + 7` to keep the results within the range of integer values and prevent overflow.

4. **Output**:
   - We print the value `dp[x]`, which contains the number of ways to achieve the sum `x`.

This approach ensures that we efficiently compute the number of distinct ways to produce the desired sum using dynamic programming.

---

https://cses.fi/problemset/task/1637


