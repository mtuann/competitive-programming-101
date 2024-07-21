# Meet in the middle
Problem: https://cses.fi/problemset/task/1628/
## Approach:
1. **Divide the array into two halves**.
2. **Generate all possible subset sums** for each half.
3. **Use bit manipulation** to efficiently generate subsets.
4. **Use a hash map (unordered_map) to store the sums of subsets of the first half**.
5. **For each subset sum of the second half, check if the required sum can be formed** by combining it with any subset sum of the first half.

Here's the C++ code:

```cpp
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

// Function to generate all possible subset sums for a given half
void generate_subset_sums(const vector<int>& array, unordered_map<int, int>& sum_map, int start, int end) {
    int n = end - start;
    int total_subsets = 1 << n; // 2^n subsets
    
    for (int i = 0; i < total_subsets; ++i) {
        int sum = 0;
        for (int j = 0; j < n; ++j) {
            if (i & (1 << j)) {
                sum += array[start + j];
            }
        }
        sum_map[sum]++;
    }
}

int count_subsets_with_sum(int n, int x, const vector<int>& array) {
    // Divide array into two halves
    int mid = n / 2;
    
    // Generate all possible subset sums for each half
    unordered_map<int, int> first_half_sums, second_half_sums;
    generate_subset_sums(array, first_half_sums, 0, mid);
    generate_subset_sums(array, second_half_sums, mid, n);
    
    // Count the number of ways to form the sum x
    int count = 0;
    for (const auto& pair : first_half_sums) {
        int sum1 = pair.first;
        int count1 = pair.second;
        int sum2 = x - sum1;
        if (second_half_sums.find(sum2) != second_half_sums.end()) {
            count += count1 * second_half_sums[sum2];
        }
    }
    
    return count;
}

int main() {
    int n, x;
    cout << "Enter the array size and the required sum: ";
    cin >> n >> x;
    vector<int> array(n);
    cout << "Enter the array elements: ";
    for (int i = 0; i < n; ++i) {
        cin >> array[i];
    }
    
    int result = count_subsets_with_sum(n, x, array);
    cout << "Number of ways to create the sum " << x << ": " << result << endl;
    
    return 0;
}
```

### Explanation:
1. **Dividing the array**: The array is divided into two halves, which are then processed independently.
2. **Generating subset sums**: For each half, generate all possible subset sums using bit manipulation. Each subset is represented by a bitmask.
3. **Storing subset sums**: Use `unordered_map` to store the count of each possible sum for the first half and the second half.
4. **Counting valid combinations**: For each subset sum in the first half, check if there is a corresponding subset sum in the second half that adds up to `x`. Multiply their counts to get the number of valid combinations.

This approach leverages the efficiency of bit manipulation and the power of hash maps to handle large sums and arrays up to size 40 efficiently.

### Reducing Time Complexity to only one map:
```cpp
// https://cses.fi/problemset/task/1628 (Meet in the Middle)

#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

// Function to generate all possible subset sums for a given range
void generate_subset_sums(const vector<int>& array, unordered_map<long long, int>& sum_map, int start, int end) {
    int n = end - start;
    int total_subsets = 1 << n; // 2^n subsets
    
    for (int i = 0; i < total_subsets; ++i) {
        long long sum = 0;
        for (int j = 0; j < n; ++j) {
            if (i & (1 << j)) {
                sum += array[start + j];
            }
        }
        sum_map[sum]++;
    }
}

long long count_subsets_with_sum(int n, int x, const vector<int>& array) {
    // Divide array into two halves
    int mid = n / 2;
    
    // Generate all possible subset sums for the first half
    unordered_map<long long, int> subset_sums;
    generate_subset_sums(array, subset_sums, 0, mid);
    
    // Count the number of ways to form the sum x using the second half
    long long count = 0;
    int second_half_size = n - mid;
    int total_subsets_second_half = 1 << second_half_size;
    
    for (int i = 0; i < total_subsets_second_half; ++i) {
        long long sum = 0;
        for (int j = 0; j < second_half_size; ++j) {
            if (i & (1 << j)) {
                sum += array[mid + j];
            }
        }
        long long complement = x - sum;
        if (subset_sums.find(complement) != subset_sums.end()) {
            count += subset_sums[complement];
        }
    }
    
    return count;
}

int main() {
    int n;
    long long x;
    cin >> n >> x;

    vector<int> array(n);
    for (int i = 0; i < n; ++i) {
        cin >> array[i];
    }
    
    long long result = count_subsets_with_sum(n, x, array);
    cout << result << endl;
    
    return 0;
}

// g++ -std=c++11 -O2 -Wall cses1628.cpp -o a && ./a < a.in
```

## Improved Approach for hash map using unordered_map and custom hash function:
```cpp
// https://cses.fi/problemset/task/1628 (Meet in the Middle)

#include <iostream>
#include <vector>
#include <unordered_map>
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

// Function to generate all possible subset sums for a given range
void generate_subset_sums(const vector<int>& array, unordered_map<long long, int, custom_hash>& sum_map, int start, int end) {
    int n = end - start;
    int total_subsets = 1 << n; // 2^n subsets
    
    for (int i = 0; i < total_subsets; ++i) {
        long long sum = 0;
        for (int j = 0; j < n; ++j) {
            if (i & (1 << j)) {
                sum += array[start + j];
            }
        }
        sum_map[sum]++;
    }
}

long long count_subsets_with_sum(int n, int x, const vector<int>& array) {
    // Divide array into two halves
    int mid = n / 2;
    
    // Generate all possible subset sums for the first half
    unordered_map<long long, int, custom_hash> subset_sums;
    generate_subset_sums(array, subset_sums, 0, mid);
    
    // Count the number of ways to form the sum x using the second half
    long long count = 0;
    int second_half_size = n - mid;
    int total_subsets_second_half = 1 << second_half_size;
    
    for (int i = 0; i < total_subsets_second_half; ++i) {
        long long sum = 0;
        for (int j = 0; j < second_half_size; ++j) {
            if (i & (1 << j)) {
                sum += array[mid + j];
            }
        }
        long long complement = x - sum;
        if (subset_sums.find(complement) != subset_sums.end()) {
            count += subset_sums[complement];
        }
    }
    
    return count;
}

int main() {
    int n;
    long long x;
    cin >> n >> x;

    vector<int> array(n);
    for (int i = 0; i < n; ++i) {
        cin >> array[i];
    }
    
    long long result = count_subsets_with_sum(n, x, array);
    cout << result << endl;
    
    return 0;
}

// g++ -std=c++11 -O2 -Wall cses1628.cpp -o a && ./a < a.in
```