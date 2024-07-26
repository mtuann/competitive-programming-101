# Binary Search
## Finding The Maximum x Such That f(x) = true
Let's say we have a boolean function `f(x)` that is monotonically increasing. We want to find the maximum `x` such that `f(x) = true`. We can use binary search to find this value.
Since `f(x)` satisfies both of following conditions:
1. `f(x) = false` for all `x` such that `x > x0`
2. `f(x) = true` for all `x` such that `x <= x0`
```cpp
int binary_search(int lo, int hi) {
    while (lo < hi) {
        int mid = (lo + hi + 1) / 2;
        if (f(mid)) {
            lo = mid;
        } else {
            hi = mid - 1;
        }
    }
}
```

## Finding The Minimum x Such That f(x) = true

Let's say we have a boolean function `f(x)` that is monotonically decreasing. We want to find the minimum `x` such that `f(x) = true`. We can use binary search to find this value.

Since `f(x)` satisfies both of following conditions:
1. `f(x) = false` for all `x` such that `x < x0`
2. `f(x) = true` for all `x` such that `x >= x0`
```cpp
int binary_search(int lo, int hi) {
    while (lo < hi) {
        int mid = (lo + hi) / 2;
        if (f(mid)) {
            hi = mid;
        } else {
            lo = mid + 1;
        }
    }
}
```

Becareful with following mistakes:
- If none of the values in the range work, check the value at the beginning/ end of the range.
- Infinite loop, $lo = 0$ and $hi = 1$ will cause infinite loop when set the $mid$ to $(lo + hi) / 2$. To fix this, set $mid$ to $(lo + hi + 1) / 2$.
- Not Accounting for Negative Bounds. This is because dividing an odd negative integer by two will round it up instead of down.
- Not Accounting for Integer Overflow ($INT\_MAX$). This is because adding two large integers together may cause an overflow. (e.g. $hi = 2*10^9$ and $lo = -2*10^9$ when calculating $hi - lo$ will cause an overflow)

## Using built-in binary search with lower_bound and upper_bound
- `lower_bound` returns an iterator pointing to the first element in the range [first, last) which has a value not less than val. For example, if we have an array `a = {1, 2, 2, 4, 4, 4, 5}` and we want to find the lower bound of 3, the function will return an iterator pointing to the first 4.
- `upper_bound` returns an iterator pointing to the first element in the range [first, last) which has a value greater than val. For example, if we have an array `a = {1, 2, 2, 4, 4, 4, 5}` and we want to find the upper bound of 4, the function will return an iterator pointing to the 5.
```cpp
int a[] = {1, 2, 2, 4, 4, 4, 5};
int n = sizeof(a) / sizeof(a[0]);
int x = 3;
int lower = lower_bound(a, a + n, x) - a;
x = 4;
int upper = upper_bound(a, a + n, x) - a;
cout << lower << " " << upper << endl; // Output: 3 6

// using vector
vector<int> a = {1, 2, 2, 4, 4, 4, 5};
int x = 3;
int lower = lower_bound(a.begin(), a.end(), x) - a.begin();
x = 4;
int upper = upper_bound(a.begin(), a.end(), x) - a.begin();
cout << lower << " " << upper << endl; // Output: 3 6
// finding in range [l, r)
int l = 1, r = 6;
int lower = lower_bound(a.begin() + l, a.begin() + r, x) - a.begin();
x = 4;
int upper = upper_bound(a.begin() + l, a.begin() + r, x) - a.begin();
cout << lower << " " << upper << endl; // Output: 3 5
```

## [1141 - Playlist](https://cses.fi/problemset/task/1141/)
To solve the problem of finding the longest sequence of successive songs where each song is unique, we can use a sliding window (or two-pointer) approach combined with a hash set for efficient lookups. This method ensures that we efficiently track the longest substring with unique elements while maintaining a linear time complexity.

### Approach:

1. **Sliding Window Technique**:
   - Use two pointers, `start` and `end`, to define the current window of unique songs.
   - Use a hash set to keep track of the unique songs in the current window.

2. **Expand the Window**:
   - Move the `end` pointer to the right, adding new songs to the hash set.

3. **Shrink the Window**:
   - If a duplicate song is encountered (i.e., if the song is already in the hash set), move the `start` pointer to the right until the duplicate song is removed.

4. **Track Maximum Length**:
   - Update the maximum length of the window whenever the window size is increased.

This approach efficiently finds the longest sequence with unique songs by ensuring each song is processed in constant time.

Here’s a Python implementation of the above approach:

```cpp
#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;
const int MAXN = 2e5 + 5;
int n;
int a[MAXN];
int b[MAXN];
int cnt[MAXN];

void coordinate_compression() {
    // vector<int> c(a, a + n);
    // sort(c.begin(), c.end());
    // c.resize(unique(c.begin(), c.end()) - c.begin());
    // for (int i = 0; i < n; i++) {
    //     a[i] = lower_bound(c.begin(), c.end(), a[i]) - c.begin() + 1;
    //     // cout << a[i] << " \n"[i == n - 1];
    // }

    copy(a, a + n, b);
    sort(b, b + n);

    for (int i = 0; i < n; i++) {
        a[i] = lower_bound(b, b + n, a[i]) - b + 1;
        // cout << a[i] << " \n"[i == n - 1];
    }
}


int longestUniqueSubsequence() {
    
    int maxLength = 0;
    int start = 0;

    for (int end = 0; end < n; ++end) {
        // Move start forward until we remove the duplicate song
        while (cnt[a[end]] > 0) {
            cnt[a[start]]--;
            ++start;
        }
        // Add the current song to the set
        cnt[a[end]]++;

        // Update the maximum length
        maxLength = max(maxLength, end - start + 1);
    }

    return maxLength;
}

int main() {
    cin >> n;
    
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    
    coordinate_compression();
    cout << longestUniqueSubsequence() << endl;
    
    return 0;
}
```

### Explanation:

1. **Initialization**:
   - `song_set` keeps track of the unique songs in the current window.
   - `max_length` tracks the maximum length of unique song sequences found.
   - `start` pointer marks the beginning of the current window.

2. **Sliding Window Expansion**:
   - Iterate over the `songs` array with the `end` pointer.
   - If a song at `end` is already in `song_set`, remove songs from the start of the window until the duplicate song is removed.

3. **Update Maximum Length**:
   - After processing each song, update the `max_length` with the size of the current window if it is larger than the previously recorded maximum length.

4. **Efficiency**:
   - The algorithm runs in \( O(n) \) time complexity because each song is added and removed from the hash set at most once.

This approach ensures that we handle up to \( 2 \times 10^5 \) songs efficiently, meeting the problem constraints effectively.

# [1073 - Tower](https://cses.fi/problemset/task/1073)
To solve this problem, we can use a data structure that efficiently supports finding the position of the largest element that is smaller than or equal to the current cube size. A balanced binary search tree or a multiset in C++ can be used for this purpose. Here's a solution using the `multiset` from the C++ Standard Library.

### Approach:

1. Use a `multiset` to maintain the top elements of the towers.
2. For each cube, determine the position where it can be placed:
   - If it can be placed on an existing tower (i.e., there's a top element in the `multiset` which is larger than the current cube), replace that top element.
   - Otherwise, start a new tower by inserting the current cube into the `multiset`.

### Implementation in C++:

```cpp
#include <iostream>
#include <set>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> cubes(n);
    
    for (int i = 0; i < n; ++i) {
        cin >> cubes[i];
    }
    
    multiset<int> towers;
    
    for (int cube : cubes) {
        auto it = towers.upper_bound(cube);
        if (it != towers.end()) {
            towers.erase(it);
        }
        towers.insert(cube);
    }
    
    cout << towers.size() << endl;
    
    return 0;
}
```

### Explanation:

1. **Input Reading**:
   - The number of cubes `n` and the sizes of the cubes are read from the input.

2. **Processing the Cubes**:
   - A `multiset` called `towers` is used to store the top elements of the current towers.
   - For each cube, we use `upper_bound` to find the smallest element in `towers` that is strictly greater than the current cube.
     - If such an element is found, it means the current cube can be placed on top of that tower. We replace the top element of that tower with the current cube.
     - If no such element is found, a new tower is started by inserting the current cube into the `multiset`.

3. **Output**:
   - The size of the `multiset` represents the number of towers, which is printed as the result.

### Complexity:
- The time complexity is \(O(n \log n)\) due to the logarithmic operations (insertion, deletion, and search) on the `multiset` for each cube, making this approach efficient and suitable for the given constraints.


# [1163 - Traffic Lights](https://cses.fi/problemset/task/1163)
To solve this problem efficiently, you can use a balanced binary search tree to keep track of the positions of the traffic lights and the lengths of the segments between them. A `set` in C++ will be useful for this purpose. We also need a `multiset` to keep track of the lengths of the segments between the traffic lights.

### Approach:

1. **Insert the traffic lights into a `set`**: This allows us to efficiently find the positions of the nearest traffic lights to any given position.
2. **Maintain a `multiset` of segment lengths**: This allows us to efficiently find and update the maximum segment length after each traffic light is added.

### Implementation in C++:

```cpp
#include <iostream>
#include <set>
#include <map>
#include <vector>

using namespace std;

int main() {
    int x, n;
    cin >> x >> n;
    vector<int> positions(n);
    
    for (int i = 0; i < n; ++i) {
        cin >> positions[i];
    }
    
    set<int> lights;
    multiset<int> segments;
    
    // Initially, we have one segment from 0 to x
    lights.insert(0);
    lights.insert(x);
    segments.insert(x);
    
    for (int p : positions) {
        auto it = lights.lower_bound(p);
        int right = *it;
        int left = *(--it);
        
        // Remove the current segment
        segments.erase(segments.find(right - left));
        
        // Insert new segments
        segments.insert(p - left);
        segments.insert(right - p);
        
        // Insert the new light position
        lights.insert(p);
        
        // Output the maximum segment length
        cout << *segments.rbegin() << " ";
    }
    
    cout << endl;
    
    return 0;
}
```

### Explanation:

1. **Input Reading**:
   - Read the length of the street `x` and the number of traffic lights `n`.
   - Read the positions of the traffic lights into a vector `positions`.

2. **Initialization**:
   - Use a `set` called `lights` to store the positions of the traffic lights. Initially, insert `0` and `x` to represent the boundaries of the street.
   - Use a `multiset` called `segments` to store the lengths of the segments. Initially, insert `x` since the entire street is one segment.

3. **Processing Each Traffic Light**:
   - For each position `p` of a traffic light:
     - Find the positions of the nearest traffic lights to the left and right using `lower_bound`.
     - Calculate the lengths of the new segments created by adding the traffic light at position `p`.
     - Update the `segments` multiset by removing the old segment length and adding the new segment lengths.
     - Insert the new traffic light position into the `lights` set.
     - Output the length of the longest segment, which is the largest element in the `segments` multiset.

4. **Output**:
   - Print the maximum segment length after each traffic light is added.

This approach ensures that each operation (insertion, deletion, finding bounds) is efficient, with a time complexity of \(O(n \log n)\), making it suitable for the given constraints.

# [2162 - Josephus Problem I](https://cses.fi/problemset/task/2162)
To solve the problem of determining the order in which children are removed from a circle where every other child is removed until none are left, we can use a data structure that efficiently handles removal and traversal operations. Here, a linked list approach or using a Python list with a modular arithmetic method can work well.

### Approach:
1. Use a list to simulate the children in the circle.
2. Keep track of the current position and remove every other child.
3. Continue the process until all children are removed.

### Implementation in C++:

```cpp
#include <iostream>
#include <list>

using namespace std;

int main() {
    int n;
    cin >> n;

    list<int> children;
    for (int i = 1; i <= n; ++i) {
        children.push_back(i);
    }

    auto it = children.begin();
    while (!children.empty()) {
        it = next(it);
        if (it == children.end()) {
            it = children.begin();
        }
        cout << *it << " ";
        it = children.erase(it);
        if (it == children.end()) {
            it = children.begin();
        }
    }

    cout << endl;
    return 0;
}
```

### Explanation:

1. **Initialization**:
   - Read the number of children `n`.
   - Create a list `children` and populate it with numbers from 1 to `n`.

2. **Simulation of the Game**:
   - Use an iterator `it` to traverse the list.
   - In each step, move the iterator to the next child using `next(it)`. If the end of the list is reached, wrap around to the beginning using `it = children.begin()`.
   - Print the current child's number and remove the child from the list using `children.erase(it)`.
   - After removal, adjust the iterator `it` to ensure it is still valid. If it points to the end after removal, wrap it to the beginning again.

3. **Output**:
   - The removed child's number is printed in each iteration until the list is empty.

### Example:
For `n = 7`, the output will be:
```
2 4 6 1 5 3 7
```

This solution efficiently simulates the game using a linked list, ensuring that each removal and traversal operation is handled in a performant manner, making it suitable for the given constraints (up to \(2 \times 10^5\)).

# [1620 - Factory Machines](https://cses.fi/problemset/task/1620)
To solve this problem efficiently, we can use a binary search approach to find the minimum time required to produce `t` products using the given machines. The idea is to determine a feasible time `x` such that the sum of products produced by all machines in time `x` is at least `t`.

Here is the C++ code that implements this solution:

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool canProduceProductsInTime(const vector<long long>& machines, long long n, long long t, long long time) {
    long long totalProducts = 0;
    for (long long machine : machines) {
        totalProducts += time / machine;
        if (totalProducts >= t) {
            return true;
        }
    }
    return false;
}

long long findMinimumTime(vector<long long>& machines, long long n, long long t) {
    long long left = 1;
    long long right = *max_element(machines.begin(), machines.end()) * t;
    long long result = right;

    while (left <= right) {
        long long mid = left + (right - left) / 2;
        if (canProduceProductsInTime(machines, n, t, mid)) {
            result = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    return result;
}

int main() {
    long long n, t;
    cin >> n >> t;
    vector<long long> machines(n);
    for (long long i = 0; i < n; ++i) {
        cin >> machines[i];
    }

    cout << findMinimumTime(machines, n, t) << endl;

    return 0;
}
```

### Explanation of the Code

1. **Reading Input**:
   - We first read the number of machines `n` and the number of products `t`.
   - We then read the time each machine takes to produce one product into a vector `machines`.

2. **Binary Search Setup**:
   - We initialize our binary search boundaries. `left` is set to 1 (minimum possible time), and `right` is set to the maximum possible time needed to produce `t` products using the slowest machine.

3. **Binary Search Loop**:
   - In each iteration of the binary search, we calculate the midpoint `mid` and check if it's possible to produce at least `t` products in `mid` time.
   - If it is possible (`canProduceProductsInTime` returns `true`), we update `result` to `mid` and move the right boundary to `mid - 1`.
   - If it is not possible, we move the left boundary to `mid + 1`.

4. **Feasibility Check**:
   - The function `canProduceProductsInTime` checks if we can produce at least `t` products within a given time `time`. It iterates through each machine and accumulates the total number of products produced by all machines in the given time.

5. **Output**:
   - Finally, we print the result, which is the minimum time required to produce `t` products.

This approach ensures that we efficiently find the minimum required time using binary search, keeping the solution within acceptable limits for large inputs.

# [1641 - Sum of Three Values](https://cses.fi/problemset/task/1641)
To solve the problem of finding three distinct values in an array whose sum equals a given target \( x \), we can leverage sorting and a two-pointer technique within a nested loop. This method ensures a more efficient approach compared to a naive triple nested loop.

Here's a step-by-step explanation followed by the C++ implementation:

### Explanation

1. **Sort the Array**: Start by sorting the array. Sorting helps to efficiently use the two-pointer technique to find pairs that sum up to a specific value.

2. **Iterate with Fixed Element**: For each element in the array, consider it as the first element of the triplet.

3. **Two-pointer Technique**: Use two pointers to find the other two elements such that their sum with the fixed element equals \( x \).
    - Initialize one pointer to the element just after the fixed element.
    - Initialize the other pointer to the end of the array.
    - Move the pointers inward based on the sum of the three elements:
        - If the sum is less than \( x \), move the left pointer to the right.
        - If the sum is greater than \( x \), move the right pointer to the left.
        - If the sum equals \( x \), you have found your triplet.

4. **Edge Cases**: If no such triplet is found, print "IMPOSSIBLE".

### C++ Code

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n;
    long long x;
    cin >> n >> x;
    vector<pair<long long, int>> a(n);
    
    for (int i = 0; i < n; ++i) {
        cin >> a[i].first;
        a[i].second = i + 1;  // store original positions
    }

    // Sort array based on the values
    sort(a.begin(), a.end());

    for (int i = 0; i < n - 2; ++i) {
        int left = i + 1;
        int right = n - 1;

        while (left < right) {
            long long sum = a[i].first + a[left].first + a[right].first;
            if (sum == x) {
                cout << a[i].second << " " << a[left].second << " " << a[right].second << endl;
                return 0;
            } else if (sum < x) {
                ++left;
            } else {
                --right;
            }
        }
    }

    cout << "IMPOSSIBLE" << endl;
    return 0;
}
```

### Key Points

1. **Sorting**: The array is sorted initially, which allows using the two-pointer technique efficiently.
2. **Two-pointer Technique**: This technique helps in reducing the time complexity by avoiding an additional nested loop.
3. **Edge Case Handling**: If no triplet is found after iterating through all possibilities, "IMPOSSIBLE" is printed.

This solution ensures an optimal approach with a time complexity of \( O(n^2) \) due to the combination of the sorting step (\( O(n \log n) \)) and the nested loop with the two-pointer technique (\( O(n^2) \)). This is efficient given the constraints \( 1 \le n \le 5000 \).

# [1642 - Sum of Four Values](https://cses.fi/problemset/task/1642)

```cpp
#include <iostream>
#include <vector>
#include <unordered_map>
#include <utility>

using namespace std;

int main() {
    int n, x;
    cin >> n >> x;
    
    vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }
    
    unordered_map<int, vector<pair<int, int>>> pair_sum_map;
    
    // Store all pairs and their indices
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            int sum = arr[i] + arr[j];
            pair_sum_map[sum].emplace_back(i, j);
        }
    }
    
    // Check for valid quadruples
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            int sum = arr[i] + arr[j];
            int complement = x - sum;
            
            if (pair_sum_map.find(complement) != pair_sum_map.end()) {
                for (auto& [p1, p2] : pair_sum_map[complement]) {
                    if (p1 != i && p1 != j && p2 != i && p2 != j) {
                        cout << p1 + 1 << " " << p2 + 1 << " " << i + 1 << " " << j + 1 << endl;
                        return 0;
                    }
                }
            }
        }
    }
    
    cout << "IMPOSSIBLE" << endl;
    return 0;
}
```

### Key Points in the Updated Code:
1. **Using a Vector for Pairs**: Instead of storing a single pair for each sum, the `unordered_map` now maps a sum to a `vector` of pairs. This allows storing multiple pairs for the same sum.

2. **Finding Valid Quadruples**: The code iterates over all pairs `(i, j)` and calculates their sum. It then checks if the complementary sum (`x - sum`) exists in the hash map. If it does, it iterates through all stored pairs for this complement to check if they form a valid quadruple with distinct indices.

3. **Output**: If a valid set of four indices is found, it prints them and exits. If no valid set is found after checking all possibilities, it prints "IMPOSSIBLE".

This approach ensures that the code correctly handles cases where multiple pairs produce the same sum.