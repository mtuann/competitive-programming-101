Sure! When participating in competitive programming, having a set of template codes in C++ can significantly speed up your coding process and make your solutions more concise and efficient. Here's a list of commonly used template codes that you might find useful:

### Basic Setup:
1. **Header Files and I/O Optimization:**
   ```cpp
   #include <iostream>
   #include <cstdio>
   #include <vector>
   #include <algorithm>
   #include <cmath>
   using namespace std;

   // Uncomment the lines below for fast input/output
   // #define fast_io ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
   // #define endl '\n'
   ```

2. **Typedefs for Commonly Used Types:**
   ```cpp
   typedef long long ll;
   typedef vector<int> vi;
   typedef pair<int, int> pii;
   ```

### Macros for Shortcuts:
3. **Useful Macros:**
   ```cpp
   #define INF 1000000000                  // Example: Infinity value
   #define FOR(i, a, b) for (int i = (a); i < (b); ++i)
   #define FORR(i, a, b) for (int i = (a); i >= (b); --i)
   #define REP(i, n) FOR(i, 0, n)
   #define REPR(i, n) FORR(i, n, 0)
   #define TR(c, it) for (auto it = (c).begin(); it != (c).end(); ++it)

    // Example: Min and Max macros
    #define MIN(a, b) ((a) < (b) ? (a) : (b))

    #define MAX(a, b) ((a) > (b) ? (a) : (b))

    // Example: Swap macro
    #define SWAP(a, b) { a ^= b; b ^= a; a ^= b; }
    ```

4. **Debugging Macros:**
    ```cpp
    #define DEBUG(x) cerr << #x << " = " << x << endl;
    #define DEBUG_ARRAY(arr, n) { REP(i, n) cerr << arr[i] << " "; cerr << endl; }
    ```

### Common Functions:
5. **Common Functions:**
    ```cpp
    // Example: GCD and LCM functions
    int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }

    int lcm(int a, int b) { return a / gcd(a, b) * b; }
    ```

## Full Template Code:
Here's a complete template code that includes the basic setup, commonly used macros, and common functions:

```cpp
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

// Uncomment the lines below for fast input/output
#define fast_io ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
// #define endl '\n'

typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;

#define INF 1000000000
#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define FORR(i, a, b) for (int i = (a); i >= (b); --i)
#define REP(i, n) FOR(i, 0, n)
#define REPR(i, n) FORR(i, n, 0)
#define TR(c, it) for (auto it = (c).begin(); it != (c).end(); ++it)

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define SWAP(a, b) { a ^= b; b ^= a; a ^= b; }

#define DEBUG(x) cerr << #x << " = " << x << endl;
#define DEBUG_ARRAY(arr, n) { REP(i, n) cerr << arr[i] << " "; cerr << endl; }

int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }
int lcm(int a, int b) { return a / gcd(a, b) * b; }

int main() {
    // adding fast_io for fast input/output
    fast_io;

    // Your code here

    return 0;
}
```
