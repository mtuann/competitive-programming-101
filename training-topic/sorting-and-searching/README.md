# CSES Problem Set
## [1621 - Distinct Numbers](https://cses.fi/problemset/task/1621)

Here's a C++ program to solve the problem of calculating the number of distinct values in a list of integers:
<details>
<summary>Distinct Numbers using unordered_set/ sorting</summary>

```cpp
// using unordered_set
#include <iostream>
#include <unordered_set>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;

    unordered_set<int> distinct_values;

    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        distinct_values.insert(x);
    }

    cout << distinct_values.size() << endl;

    return 0;
}
```


```cpp
// using sort with vector
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int n;
    std::cin >> n;

    std::vector<int> values(n);

    for (int i = 0; i < n; ++i) {
        std::cin >> values[i];
    }

    // Sort the vector
    std::sort(values.begin(), values.end());

    // Count distinct values
    int distinct_count = 1; // At least one distinct value if n > 0
    for (int i = 1; i < n; ++i) {
        if (values[i] != values[i-1]) {
            distinct_count++;
        }
    }

    std::cout << distinct_count << std::endl;

    return 0;
}
```

```cpp
// using sort with array (fastest time)
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 2e5 + 10;

int n;
int values[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        cin >> values[i];
    }

    // Sort the array
    sort(values, values + n);

    // Count distinct values
    int distinct_count = 1; // At least one distinct value if n > 0
    for (int i = 1; i < n; ++i) {
        if (values[i] != values[i-1]) {
            distinct_count++;
        }
    }

    cout << distinct_count << endl;

    return 0;
}
```
</details>



### Explanation:

1. **Input Handling**:
   - The first input line is read into the integer `n`, which represents the number of values.
   - The subsequent `n` integers are read and stored in an unordered set `distinct_values`.

2. **Use of `unordered_set`**:
   - An `unordered_set` is used to store the integers because it automatically handles duplicates by storing only unique elements.

3. **Insertion and Output**:
   - For each integer read from the input, it is inserted into the `unordered_set`.
   - Finally, the size of the `unordered_set` is printed, which represents the number of distinct values in the list.


## [1084 - Apartments](https://cses.fi/problemset/task/1084)
Here is a C++ program to solve the problem of distributing apartments to as many applicants as possible, given their desired apartment sizes and an allowed size difference:

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 2e5 + 10;
int n, m, k;
int applicants[MAXN];
int apartments[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> n >> m >> k;

    for (int i = 0; i < n; ++i) {
        cin >> applicants[i];
    }

    for (int i = 0; i < m; ++i) {
        cin >> apartments[i];
    }

    // Sort both the applicants and the apartments
    sort(applicants, applicants + n);
    sort(apartments, apartments + m);

    int i = 0; // Index for applicants
    int j = 0; // Index for apartments
    int count = 0;

    while (i < n && j < m) {
        if (apartments[j] < applicants[i] - k) {
            // Apartment too small, move to the next apartment
            j++;
        } else if (apartments[j] > applicants[i] + k) {
            // Apartment too big, move to the next applicant
            i++;
        } else {
            // Apartment fits within the acceptable range
            count++;
            i++;
            j++;
        }
    }

    cout << count << endl;

    return 0;
}
```

### Explanation:

1. **Input Handling**:
   - The first input line reads `n`, `m`, and `k`, representing the number of applicants, the number of apartments, and the maximum allowed difference in size, respectively.
   - The next `n` integers represent the desired apartment sizes for each applicant.
   - The final `m` integers represent the sizes of the available apartments.

2. **Sorting**:
   - Both the list of applicants' desired sizes and the list of apartment sizes are sorted in non-decreasing order using `std::sort`.

3. **Two-Pointer Technique**:
   - Initialize two pointers `i` and `j` to iterate through the lists of applicants and apartments, respectively.
   - Iterate through both lists:
     - If the current apartment size is less than the applicant's desired size minus `k`, move to the next apartment.
     - If the current apartment size is greater than the applicant's desired size plus `k`, move to the next applicant.
     - If the current apartment size is within the acceptable range for the current applicant, count this as a match, and move to the next applicant and the next apartment.

4. **Output**:
   - Print the count of successful matches, representing the number of applicants who will get an apartment.

This approach ensures that the apartments are distributed as efficiently as possible, with a time complexity of O(n log n + m log m) due to the sorting steps.

## [1090 - Ferris Wheel](https://cses.fi/problemset/task/1090)

Here is a C++ program to solve the problem of distributing apartments to as many applicants as possible, given their desired apartment sizes and an allowed size difference:

```cpp
#include <iostream>
#include <algorithm>
using namespace std;

const int MAX_N = 10 + 200000;  // maximum number of children

int weights[MAX_N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, x;
    cin >> n >> x;

    for (int i = 0; i < n; ++i) {
        cin >> weights[i];
    }

    // Sort the weights of the children
    sort(weights, weights + n);

    int i = 0; // Index for the lightest child
    int j = n - 1; // Index for the heaviest child
    int gondolas = 0;

    while (i <= j) {
        if (weights[i] + weights[j] <= x) {
            // If the lightest and the heaviest child can share a gondola
            i++;
        }
        // Move to the next heaviest child
        j--;
        // One gondola used
        gondolas++;
    }

    cout << gondolas << endl;

    return 0;
}
```

### Explanation:

1. **Input Handling**:
   - The first input line reads `n`, `m`, and `k`, representing the number of applicants, the number of apartments, and the maximum allowed difference in size, respectively.
   - The next `n` integers represent the desired apartment sizes for each applicant.
   - The final `m` integers represent the sizes of the available apartments.

2. **Sorting**:
   - Both the list of applicants' desired sizes and the list of apartment sizes are sorted in non-decreasing order using `std::sort`.

3. **Two-Pointer Technique**:
   - Initialize two pointers `i` and `j` to iterate through the lists of applicants and apartments, respectively.
   - Iterate through both lists:
     - If the current apartment size is less than the applicant's desired size minus `k`, move to the next apartment.
     - If the current apartment size is greater than the applicant's desired size plus `k`, move to the next applicant.
     - If the current apartment size is within the acceptable range for the current applicant, count this as a match, and move to the next applicant and the next apartment.

4. **Output**:
   - Print the count of successful matches, representing the number of applicants who will get an apartment.

This approach ensures that the apartments are distributed as efficiently as possible, with a time complexity of O(n log n + m log m) due to the sorting steps.

## [1091 - Concert Tickets](https://cses.fi/problemset/task/1091)
Here is a C++ program to solve the problem of assigning concert tickets to customers based on their maximum willing price using the multiset data structure for efficient operations:

```cpp
#include <iostream>
#include <vector>
#include <set>
using namespace std;

const int MAXN = 2e5 + 10;
int n, m;
multiset<int> ticket_prices;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    // Read the ticket prices
    for (int i = 0; i < n; ++i) {
        int price;
        cin >> price;
        ticket_prices.insert(price);
    }

    // Read the maximum prices customers are willing to pay
    for (int i = 0; i < m; ++i) {
        int max_price;
        cin >> max_price;
        auto it = ticket_prices.upper_bound(max_price);
        if (it == ticket_prices.begin()) {
            // No ticket can be assigned to this customer
            cout << -1 << "\n";
        } else {
            // A suitable ticket is found
            --it; // Move to the largest element that is <= max_prices[i]
            cout << *it << "\n";
            ticket_prices.erase(it); // Remove this ticket from the set
        }
    }

    return 0;
}
```

### Explanation:

1. **Input Handling**:
   - The first input line reads `n` and `m`, representing the number of tickets and the number of customers.
   - The next line reads the prices of the tickets into a multiset `ticket_prices`.
   - The last line reads the maximum prices each customer is willing to pay into a vector `max_prices`.

2. **Multiset for Ticket Prices**:
   - A multiset is used to store the ticket prices because it allows for efficient insertion, deletion, and searching operations while maintaining sorted order.

3. **Processing Each Customer**:
   - For each customer, use `upper_bound` to find the smallest ticket price that is strictly greater than the customer's maximum price.
   - If `upper_bound` returns the beginning of the multiset, it means no ticket can satisfy the customer's price, so output `-1`.
   - Otherwise, move the iterator one step back to get the largest ticket price that is less than or equal to the customer's maximum price, print the price, and remove that ticket from the multiset.

This approach ensures efficient handling of up to 200,000 tickets and customers, leveraging the multiset for logarithmic time complexity operations.

## [1619 - Restaurant Customers](https://cses.fi/problemset/task/1619)
To solve the problem of finding the maximum number of customers in the restaurant at any time, you can use a technique known as the "sweep line algorithm" or "event counting." The idea is to process all the events (arrivals and departures) in a sorted manner to determine the maximum overlap.

Here's how you can approach the problem:

1. **Convert the Problem to Events**:
   - For each customer, create two events: one for arrival and one for departure.
   - Mark the arrival event with a `+1` (indicating an increase in the count of customers).
   - Mark the departure event with a `-1` (indicating a decrease in the count of customers).

2. **Sort Events**:
   - Sort all events primarily by time. If two events have the same time, process departure events before arrival events to ensure that when customers leave and arrive at the same time, the count does not falsely increase.

3. **Sweep Through Events**:
   - Traverse through the sorted events while maintaining a running count of customers in the restaurant.
   - Keep track of the maximum count observed during this traversal.

Here's a C++ program implementing this approach:

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Event {
    int time;
    int type; // +1 for arrival, -1 for departure
};

// Custom comparator to sort events
bool compareEvents(const Event &e1, const Event &e2) {
    if (e1.time == e2.time) {
        return e1.type < e2.type; // Prioritize departures over arrivals if times are the same
    }
    return e1.time < e2.time;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<Event> events;

    // Read the arrival and departure times
    for (int i = 0; i < n; ++i) {
        int arrival, departure;
        cin >> arrival >> departure;
        events.push_back({arrival, 1}); // Arrival event
        events.push_back({departure, -1}); // Departure event
    }

    // Sort the events
    sort(events.begin(), events.end(), compareEvents);

    int current_customers = 0;
    int max_customers = 0;

    // Process the events
    for (const auto &event : events) {
        current_customers += event.type;
        if (current_customers > max_customers) {
            max_customers = current_customers;
        }
    }

    cout << max_customers << endl;

    return 0;
}
```

### Explanation:

1. **Event Struct**:
   - `time` stores the time of the event.
   - `type` indicates whether the event is an arrival (`+1`) or a departure (`-1`).

2. **Event Sorting**:
   - Events are sorted by time. If two events occur at the same time, departures are processed before arrivals to ensure correct customer counts.

3. **Processing Events**:
   - Traverse through the sorted events, adjusting the current number of customers based on the event type.
   - Track the maximum number of customers encountered.

This approach efficiently handles the problem with a time complexity of \(O(n \log n)\) due to sorting, which is suitable for the given constraints.

## [1629 - Movie Festival](https://cses.fi/problemset/task/1629)
To determine the maximum number of non-overlapping movies you can watch entirely, we can use a greedy algorithm based on sorting the movies by their ending times. This strategy ensures that we can watch the maximum number of movies by always choosing the movie that finishes the earliest and then moving to the next movie that starts after the current movie ends.

Here’s a step-by-step approach to solving the problem:

1. **Sort the Movies by Ending Time**:
   - Sort the list of movies by their ending times. If two movies have the same ending time, it does not matter which one we choose first.

2. **Use a Greedy Algorithm to Select Movies**:
   - Initialize a variable to keep track of the end time of the last selected movie.
   - Iterate through the sorted list of movies, and for each movie, check if its start time is after or equal to the end time of the last selected movie. If it is, select this movie and update the end time.

### C++ Implementation

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Movie {
    int start;
    int end;
};

// Comparator to sort movies by end time
bool compareMovies(const Movie &m1, const Movie &m2) {
    return m1.end < m2.end;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<Movie> movies(n);

    // Read the start and end times of each movie
    for (int i = 0; i < n; ++i) {
        cin >> movies[i].start >> movies[i].end;
    }

    // Sort the movies by their end times
    sort(movies.begin(), movies.end(), compareMovies);

    int count = 0;
    int last_end_time = 0;

    // Iterate through the sorted movies and select non-overlapping movies
    for (const auto &movie : movies) {
        if (movie.start >= last_end_time) {
            count++;
            last_end_time = movie.end;
        }
    }

    cout << count << endl;

    return 0;
}
```

### Explanation:

1. **Struct Definition**:
   - A `Movie` struct is defined to store the start and end times of each movie.

2. **Input Handling**:
   - The number of movies `n` is read.
   - The start and end times of each movie are read into a vector of `Movie` structs.

3. **Sorting**:
   - The movies are sorted by their end times using the `sort` function and a custom comparator.

4. **Greedy Algorithm**:
   - Initialize `count` to keep track of the number of non-overlapping movies.
   - Initialize `last_end_time` to track the end time of the last selected movie.
   - Iterate through the sorted list of movies:
     - If the start time of the current movie is greater than or equal to `last_end_time`, it means the current movie can be watched entirely after the last selected movie. Update `count` and `last_end_time`.

5. **Output**:
   - Print the total count of non-overlapping movies that can be watched.

This algorithm efficiently finds the maximum number of non-overlapping movies that can be watched, with a time complexity of \(O(n \log n)\) due to sorting, which is optimal for the given constraints.

## [1640 - Sum of Two Values](https://cses.fi/problemset/task/1640)
To solve this problem efficiently, you can use a hash map (or an unordered_map in C++) to store the values and their corresponding indices as you iterate through the array. This allows you to check in constant time if the complement of the current value (i.e., `x - a[i]`) exists in the map. If it does, you have found the two numbers whose sum is `x`.

Here’s the step-by-step approach:

1. **Initialize a Hash Map**:
   - Use an unordered_map to store the value of each element as the key and its index as the value.

2. **Iterate Through the Array**:
   - For each element, calculate the complement (i.e., `x - a[i]`).
   - Check if the complement exists in the hash map.
   - If it does, print the indices (considering the 1-based indexing requirement) and exit.
   - If it does not, store the current element and its index in the hash map.

3. **Handle the Case Where No Solution Exists**:
   - If you finish iterating through the array without finding a pair, print "IMPOSSIBLE".

### C++ Implementation

```cpp
#include <iostream>
#include <unordered_map>
#include <vector>
#include <chrono>
using namespace std;

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, x;
    cin >> n >> x;

    vector<int> a(n);
    unordered_map<int, int, custom_hash> value_to_index;

    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    for (int i = 0; i < n; ++i) {
        int complement = x - a[i];
        if (value_to_index.find(complement) != value_to_index.end()) {
            cout << value_to_index[complement] + 1 << " " << i + 1 << "\n";
            return 0;
        }
        value_to_index[a[i]] = i;
    }

    cout << "IMPOSSIBLE\n";
    return 0;
}
```

### Explanation:

1. **Input Handling**:
   - Read `n` and `x`, the size of the array and the target sum.
   - Read the array `a` of size `n`.

2. **Hash Map for Index Tracking**:
   - Use an `unordered_map<int, int>` named `value_to_index` to keep track of the values and their indices.

3. **Iterate and Find Complement**:
   - For each element `a[i]` in the array, calculate the complement `x - a[i]`.
   - Check if the complement exists in the hash map.
   - If it does, print the indices of the complement and the current element (converted to 1-based indexing) and exit.
   - If it does not, store the current element and its index in the hash map.

4. **Output**:
   - If no such pair is found, print "IMPOSSIBLE".

This algorithm runs in O(n) time complexity due to the single pass through the array and the O(1) average time complexity for insertions and lookups in the hash map. This is efficient and suitable for the given constraints.

## [1643 - Maximum Subarray Sum](https://cses.fi/problemset/task/1643)
To solve the problem of finding the maximum sum of values in a contiguous, nonempty subarray, you can use Kadane's Algorithm. This algorithm efficiently finds the maximum sum in O(n) time, which is suitable given the constraints.

### Kadane's Algorithm
The idea behind Kadane's Algorithm is to iterate through the array while keeping track of the maximum sum of the subarray that ends at the current position. You maintain two values:
- `current_sum`: The maximum sum of the subarray that ends at the current position.
- `max_sum`: The maximum sum encountered so far.

For each element in the array, you update `current_sum` by taking the maximum of the current element itself and the sum of `current_sum` and the current element. Then, update `max_sum` if `current_sum` is greater than `max_sum`.

### C++ Implementation
Here’s the implementation of Kadane's Algorithm in C++:

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> array(n);
    for (int i = 0; i < n; ++i) {
        cin >> array[i];
    }

    int current_sum = array[0];
    int max_sum = array[0];

    for (int i = 1; i < n; ++i) {
        current_sum = max(array[i], current_sum + array[i]);
        max_sum = max(max_sum, current_sum);
    }

    cout << max_sum << endl;

    return 0;
}
```

### Explanation
1. **Input Handling**:
   - Read the size of the array `n`.
   - Read the array elements into a vector `array`.

2. **Initialization**:
   - Initialize `current_sum` and `max_sum` with the first element of the array.

3. **Iterate Through the Array**:
   - Start from the second element (index 1) and iterate to the end.
   - For each element, update `current_sum` to be the maximum of the current element itself or `current_sum` plus the current element.
   - Update `max_sum` if `current_sum` is greater than `max_sum`.

4. **Output the Result**:
   - Print the `max_sum`, which represents the maximum sum of a contiguous subarray.

### Complexity
- **Time Complexity**: O(n) because we only pass through the array once.
- **Space Complexity**: O(1) because we use a constant amount of extra space.

This approach ensures that the solution is efficient and works within the constraints provided.

## [1074 - Stick Lengths](https://cses.fi/problemset/task/1074)
To solve this problem of modifying all sticks to the same length with minimum total cost, the key observation is that the optimal length to convert all sticks to minimize the sum of absolute differences is the median of the stick lengths. The median minimizes the sum of absolute deviations compared to any other value.

Here's a step-by-step approach:

1. **Find the Median**:
   - Sort the array of stick lengths.
   - The median is the middle element if the number of elements is odd, or any of the two middle elements if the number of elements is even (both will give the same total cost).

2. **Calculate the Total Cost**:
   - For each stick, calculate the absolute difference between its length and the median.
   - Sum these differences to get the total cost.

### C++ Implementation

Here’s how you can implement this in C++:

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> sticks(n);

    for (int i = 0; i < n; ++i) {
        cin >> sticks[i];
    }

    // Sort the stick lengths to find the median
    sort(sticks.begin(), sticks.end());

    // Find the median
    int median = sticks[n / 2];

    // Calculate the total cost to make all sticks equal to the median
    long long total_cost = 0;
    for (int i = 0; i < n; ++i) {
        total_cost += abs(sticks[i] - median);
    }

    cout << total_cost << endl;

    return 0;
}
```

### Explanation

1. **Input Handling**:
   - Read the number of sticks `n`.
   - Read the lengths of the sticks into a vector `sticks`.

2. **Finding the Median**:
   - Sort the vector `sticks`.
   - The median is `sticks[n / 2]`.

3. **Calculating the Total Cost**:
   - Iterate through each stick and calculate the absolute difference between its length and the median.
   - Sum these differences to get the total cost.

4. **Output the Result**:
   - Print the `total_cost`.

### Complexity
- **Time Complexity**: O(n log n) due to the sorting step.
- **Space Complexity**: O(1) additional space, aside from the input storage.

This approach ensures that the solution is efficient and works within the given constraints.

## [2183 - Missing Coin Sum](https://cses.fi/problemset/task/2183)
To solve the problem of finding the smallest sum you cannot create using a subset of given coin values, you can use a greedy algorithm. The key insight is that if you have sorted the coins and you can create all sums from 1 to a certain value \( S \), then to extend this range to \( S + 1 \), you need a coin that is \( S + 1 \) or smaller. If the next coin is larger than \( S + 1 \), then \( S + 1 \) is the smallest sum that cannot be created.

### Steps:

1. **Sort the Coin Values**: Sorting the coin values helps in using the smallest coins first to build up the range of sums we can create.
2. **Initialize the Smallest Unreachable Sum**: Start with the smallest sum that cannot be created, initially set to 1.
3. **Iterate Through the Coins**: For each coin, check if it is greater than the current smallest unreachable sum:
   - If it is, then the current smallest unreachable sum is the answer.
   - Otherwise, add the value of the coin to the current smallest unreachable sum, extending the range of sums that can be created.

### C++ Implementation

Here’s how you can implement this approach in C++:

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> coins(n);
    for (int i = 0; i < n; ++i) {
        cin >> coins[i];
    }

    sort(coins.begin(), coins.end());

    long long smallest_unreachable_sum = 1;
    for (int i = 0; i < n; ++i) {
        if (coins[i] > smallest_unreachable_sum) {
            break;
        }
        smallest_unreachable_sum += coins[i];
    }

    cout << smallest_unreachable_sum << endl;

    return 0;
}
```

### Explanation:

1. **Input Handling**:
   - Read the number of coins `n`.
   - Read the coin values into a vector `coins`.

2. **Sorting**:
   - Sort the vector `coins`.

3. **Finding the Smallest Unreachable Sum**:
   - Initialize `smallest_unreachable_sum` to 1.
   - Iterate through each coin:
     - If the current coin value is greater than `smallest_unreachable_sum`, break the loop because `smallest_unreachable_sum` is the answer.
     - Otherwise, add the coin value to `smallest_unreachable_sum`, extending the range of sums that can be created.

4. **Output**:
   - Print the `smallest_unreachable_sum`.

### Complexity:
- **Time Complexity**: O(n log n) due to sorting.
- **Space Complexity**: O(1) additional space, aside from the input storage.

This algorithm efficiently finds the smallest sum that cannot be created using a subset of the coins, working within the given constraints.

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

## [1620 - Factory Machines](https://cses.fi/problemset/task/1620)
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

## [1642 - Sum of Four Values](https://cses.fi/problemset/task/1642)

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

## [1645 - Nearest Smaller Values](https://cses.fi/problemset/task/1645)

To solve this problem efficiently given the constraints (with \( n \) up to \( 2 \times 10^5 \)), you can use a stack-based approach. This method processes each element in the array while maintaining a stack that helps in finding the nearest smaller element to the left.

Here's a C++ implementation of this approach:

```cpp
#include <iostream>
#include <vector>
#include <stack>

using namespace std;

int main() {
    int n;
    cin >> n;
    
    vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }
    
    vector<int> result(n);
    stack<int> s;
    
    for (int i = 0; i < n; ++i) {
        // Pop elements from the stack until we find a smaller element or the stack is empty
        while (!s.empty() && arr[s.top()] >= arr[i]) {
            s.pop();
        }
        // If stack is not empty, the top of the stack is the nearest smaller element
        if (!s.empty()) {
            result[i] = s.top() + 1;  // Convert to 1-based index
        } else {
            result[i] = 0;
        }
        // Push the current index onto the stack
        s.push(i);
    }
    
    // Print the result
    for (int i = 0; i < n; ++i) {
        cout << result[i] << " ";
    }
    cout << endl;
    
    return 0;
}
```

### Explanation:

1. **Input Reading**: The code starts by reading the size of the array `n` and the array values.

2. **Stack for Nearest Smaller Elements**: The stack is used to keep track of indices of array elements. For each element in the array, the code:
   - Pops elements from the stack while the top of the stack is not smaller than the current element.
   - If the stack is not empty after this, the index at the top of the stack is the position of the nearest smaller element.
   - If the stack is empty, it means there is no smaller element to the left, so the result for that position is `0`.
   - Pushes the current index onto the stack.

3. **Output**: After processing all elements, the result vector contains the nearest smaller element's position (1-based index). The result is then printed.

This stack-based approach ensures that each element is pushed and popped from the stack at most once, resulting in an \( O(n) \) time complexity, which is efficient for large inputs.

## [1660 - Subarray Sums I](https://cses.fi/problemset/task/1660)
To solve the problem of counting the number of subarrays with a given sum \( x \), you can use the sliding window (or two-pointer) technique combined with a prefix sum approach. This method is efficient with a time complexity of \( O(n) \), which is well-suited for the problem's constraints.

Here's a C++ implementation using the sliding window approach:

```cpp
#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n, x;
    cin >> n >> x;
    
    vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }
    
    int count = 0;
    int current_sum = 0;
    int start = 0;
    
    for (int end = 0; end < n; ++end) {
        current_sum += arr[end];
        
        // Shrink the window from the left if the current_sum is greater than x
        while (current_sum > x && start <= end) {
            current_sum -= arr[start];
            ++start;
        }
        
        // Check if the current_sum is exactly x
        if (current_sum == x) {
            ++count;
        }
    }
    
    cout << count << endl;
    
    return 0;
}
```

### Explanation:

1. **Input Reading**: The code reads the size of the array `n` and the target sum `x`, followed by the array elements.

2. **Sliding Window Technique**:
   - Initialize `count` to count the number of subarrays with the sum equal to `x`.
   - Use two pointers, `start` and `end`, to represent the window of the current subarray.
   - Expand the window by adding elements to `current_sum` as the `end` pointer moves to the right.
   - If `current_sum` exceeds `x`, shrink the window from the left by subtracting elements from `current_sum` until it is less than or equal to `x`.
   - If `current_sum` equals `x`, increment the `count`.

3. **Output**: The final count of subarrays whose sum is exactly `x` is printed.

This method efficiently finds all subarrays with the desired sum without checking every possible subarray explicitly, which would be too slow for large arrays.

## [1661 - Subarray Sums II](https://cses.fi/problemset/task/1661)
Given the problem of counting the number of subarrays with a sum equal to `x`, especially with the constraints where the array can have negative numbers, a more sophisticated approach using prefix sums and a hash map (or unordered map) is suitable.

### Approach

1. **Prefix Sum and Hash Map**:
   - Maintain a running prefix sum while iterating through the array.
   - Use a hash map to keep track of how many times each prefix sum has occurred.
   - For each element, compute the prefix sum up to that point.
   - Check if the difference between the current prefix sum and `x` exists in the hash map. If it does, it means there are subarrays ending at the current index that sum to `x`.
   - Update the hash map with the current prefix sum.

This approach ensures an \( O(n) \) time complexity due to single-pass processing and constant-time operations with the hash map.

### C++ Implementation

Here's the C++ code to solve this problem:

```cpp
#include <iostream>
#include <vector>
#include <chrono>
#include <unordered_map>

using namespace std;
struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};


int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, x;
    cin >> n >> x;
    
    vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }
    
    unordered_map<long long, int, custom_hash> prefix_sum_count;
    long long current_sum = 0;
    long long count = 0;
    
    // Initialize the map with prefix sum 0 having count 1 (to handle the case when subarray starts from index 0)
    prefix_sum_count[0] = 1;
    
    for (int i = 0; i < n; ++i) {
        current_sum += arr[i];
        
        // Check if there is a prefix sum such that (current_sum - prefix_sum) == x
        if (prefix_sum_count.find(current_sum - x) != prefix_sum_count.end()) {
            count += prefix_sum_count[current_sum - x];
        }
        
        // Update the map with the current prefix sum
        prefix_sum_count[current_sum]++;
    }
    
    cout << count << endl;
    
    return 0;
}
```

### Explanation

1. **Input Reading**: Read the size of the array `n` and the target sum `x`, followed by the array elements.

2. **Prefix Sum Calculation**:
   - Maintain a variable `current_sum` to keep track of the prefix sum up to the current index.
   - Use an `unordered_map` named `prefix_sum_count` to store counts of each prefix sum encountered.

3. **Finding Subarrays**:
   - For each element, update the `current_sum`.
   - Check if `(current_sum - x)` is a key in the hash map. If it is, it means there are subarrays ending at the current index that sum to `x`.
   - Update the count based on how many times `(current_sum - x)` has been encountered.
   - Update the hash map with the current prefix sum.

4. **Output**: Print the count of subarrays with sum equal to `x`.

This approach efficiently handles the problem within the constraints and correctly accounts for negative values in the array.

## [1662 - Subarray Divisibility](https://cses.fi/problemset/task/1662)
To count the number of subarrays where the sum of values is divisible by `n`, you can use a prefix sum approach combined with modular arithmetic and a hash map. Here's how you can solve this problem efficiently:

### Approach

1. **Prefix Sum with Modular Arithmetic**:
   - Compute the prefix sum for each subarray.
   - Calculate the prefix sum modulo `n`.
   - Use a hash map to keep track of the frequency of each remainder when the prefix sum is divided by `n`.
   - A subarray sum is divisible by `n` if the difference between the remainders of the two prefix sums is zero (i.e., they have the same remainder).

2. **Key Points**:
   - Use modular arithmetic to handle negative numbers properly. Since `prefix_sum % n` might be negative, adjust it to be within `[0, n-1]`.
   - Use a hash map to count the occurrences of each remainder.

### C++ Implementation

Here's a C++ implementation of the approach:

```cpp
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;
int n;

int main() {
    
    cin >> n;
    
    vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }
    
    unordered_map<int, int> remainder_count;
    long long prefix_sum = 0;
    long long count = 0;
    
    // Initialize the map with remainder 0 having count 1 (to handle the case when subarray starts from index 0)
    remainder_count[0] = 1;
    
    for (int i = 0; i < n; ++i) {
        prefix_sum += arr[i];
        int remainder = ((prefix_sum % n) + n) % n;  // Normalize negative remainders
        
        if (remainder_count.find(remainder) != remainder_count.end()) {
            count += remainder_count[remainder];
        }
        
        remainder_count[remainder]++;
    }
    
    cout << count << endl;
    
    return 0;
}
```

### Explanation

1. **Input Reading**: Read the size of the array `n` and the array elements.

2. **Prefix Sum Calculation**:
   - Maintain a running `prefix_sum`.
   - Calculate the remainder of the `prefix_sum` modulo `n`. Adjust the remainder to be within the range `[0, n-1]` to handle negative values correctly.

3. **Using Hash Map**:
   - Use the hash map `remainder_count` to count occurrences of each remainder.
   - If a remainder has been seen before, it means there are subarrays (ending at the current index) whose sums are divisible by `n`.
   - Update the count based on the number of times the remainder has been encountered before.

4. **Output**: Print the count of subarrays where the sum is divisible by `n`.

This method ensures that the solution is efficient with a time complexity of \( O(n) \), which is suitable given the constraints.

## [1085 - Array Division](https://cses.fi/problemset/task/1085)

To solve the problem of dividing an array into \( k \) subarrays such that the maximum sum of any subarray is minimized, you can use a binary search approach combined with a greedy algorithm. Here's a step-by-step breakdown:

### Approach

1. **Binary Search**:
   - We will use binary search to find the minimum possible value of the maximum sum of the subarrays.
   - The search space for the maximum subarray sum ranges from the maximum single element (as no subarray can be smaller than the largest element) to the sum of the entire array (as the worst case is having one subarray containing all elements).

2. **Greedy Check**:
   - For a given potential maximum sum \( mid \) during the binary search, use a greedy approach to check if it is feasible to divide the array into \( k \) or fewer subarrays such that each subarray has a sum less than or equal to \( mid \).
   - Traverse the array while maintaining a running sum. If adding the next element exceeds \( mid \), start a new subarray and continue. Count the number of subarrays formed this way.

3. **Adjust Search Space**:
   - If it's feasible to divide the array into \( k \) or fewer subarrays with the maximum sum \( mid \), then try a smaller maximum sum by adjusting the binary search range.
   - If it's not feasible, increase the maximum sum and continue the search.

### C++ Implementation

Here's the C++ code implementing the above approach:

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

bool canDivide(const vector<int>& arr, int k, long long max_sum) {
    long long current_sum = 0;
    int subarray_count = 1;  // Start with one subarray

    for (int value : arr) {
        if (current_sum + value > max_sum) {
            // Need to start a new subarray
            ++subarray_count;
            current_sum = value;

            if (subarray_count > k) {
                return false;  // More subarrays than allowed
            }
        } else {
            current_sum += value;
        }
    }
    return true;
}

int main() {
    int n, k;
    cin >> n >> k;
    
    vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }
    
    long long left = *max_element(arr.begin(), arr.end());
    long long right = accumulate(arr.begin(), arr.end(), 0LL);
    long long result = right;
    
    while (left <= right) {
        long long mid = left + (right - left) / 2;
        
        if (canDivide(arr, k, mid)) {
            result = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    
    cout << result << endl;
    
    return 0;
}
```

### Explanation:

1. **Binary Search Initialization**:
   - `left` is initialized to the maximum element in the array, as no subarray can have a sum smaller than this value.
   - `right` is initialized to the sum of the entire array.

2. **Feasibility Check**:
   - The `canDivide` function checks if it's possible to divide the array into \( k \) or fewer subarrays where each subarray's sum is less than or equal to `max_sum`.

3. **Binary Search Execution**:
   - Adjust the search range based on whether the current `mid` is feasible or not.
   - Update the result whenever a feasible `mid` is found.

4. **Output**:
   - Print the minimum possible value of the maximum sum in the optimal division.

This approach efficiently handles large arrays due to the \( O(n \log(\text{sum})) \) complexity, where `sum` is the sum of all array elements.

# [2428 - Subarray Distinct Values](https://cses.fi/problemset/task/2428)
To solve the problem of counting the number of subarrays with at most \( k \) distinct values efficiently, we can use the sliding window technique with two pointers. This approach helps to dynamically maintain the count of distinct values in the current window while iterating through the array.

### Approach

1. **Sliding Window with Two Pointers**:
   - Use two pointers to maintain a window of subarrays.
   - Expand the right end of the window to include new elements.
   - When the window contains more than \( k \) distinct elements, move the left end to reduce the number of distinct elements.
   - Count the valid subarrays formed by the current window.

2. **Hash Map to Track Frequencies**:
   - Use a hash map (or dictionary) to keep track of the frequency of each element in the current window.

3. **Counting Valid Subarrays**:
   - For each position of the right pointer, add the number of valid subarrays ending at that position.

### Detailed Steps

1. Initialize two pointers: `left` and `right`, both starting at the beginning of the array.
2. Use a hash map to count the frequency of elements in the current window.
3. Expand the window by moving the `right` pointer and updating the hash map.
4. If the window has more than \( k \) distinct elements, move the `left` pointer to reduce the number of distinct elements.
5. For each position of the `right` pointer, count the number of valid subarrays that end at `right`.

### Implementation in C++

Here's the implementation of the approach described:

```cpp
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

int countSubarraysWithAtMostKDistinct(const vector<int>& arr, int k) {
    int n = arr.size();
    unordered_map<int, int> freq;
    int left = 0, right = 0;
    int count = 0;
    int distinct = 0;

    while (right < n) {
        // Expand the window by adding arr[right]
        if (freq[arr[right]] == 0) {
            distinct++;
        }
        freq[arr[right]]++;
        right++;

        // Shrink the window from the left if it has more than k distinct elements
        while (distinct > k) {
            if (--freq[arr[left]] == 0) {
                distinct--;
            }
            left++;
        }

        // Add the number of valid subarrays ending at 'right - 1'
        count += (right - left);
    }

    return count;
}

int main() {
    int n, k;
    cin >> n >> k;
    
    vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }
    
    int result = countSubarraysWithAtMostKDistinct(arr, k);
    cout << result << endl;

    return 0;
}
```

### Explanation

1. **Initialization**:
   - `left` and `right` pointers start at the beginning of the array.
   - `freq` is a hash map to keep track of the frequency of elements in the current window.
   - `count` keeps the total number of valid subarrays.
   - `distinct` tracks the number of distinct elements in the current window.

2. **Sliding Window**:
   - Expand the window by moving the `right` pointer and updating the frequency count of the current element.
   - If adding a new element increases the distinct count beyond \( k \), move the `left` pointer to shrink the window until it has at most \( k \) distinct elements.
   - For each position of the `right` pointer, the number of valid subarrays ending at `right - 1` is added to `count`. These are the subarrays starting from `left` to `right-1`.

3. **Output**:
   - Print the total count of valid subarrays.

This approach ensures that each element is processed at most twice, leading to an \( O(n) \) time complexity, which is efficient given the problem constraints.