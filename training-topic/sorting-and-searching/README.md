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