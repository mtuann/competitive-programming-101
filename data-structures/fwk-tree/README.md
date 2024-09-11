- [Fenwick (Binary Indexed) Trees](https://www.hackerearth.com/practice/data-structures/advanced-data-structures/fenwick-binary-indexed-trees/tutorial/)

### Tutorial: Fenwick Tree (Binary Indexed Tree) in C++

#### 1. Introduction

A **Fenwick Tree** (also known as a **Binary Indexed Tree** or **BIT**) is a data structure that provides efficient methods for calculation and manipulation of the prefix sums of a table of values. It is particularly useful when you need to perform a large number of prefix sum queries and updates on an array.

Fenwick Tree allows you to:
- Update an element in an array in **O(log n)** time.
- Compute the prefix sum (sum of the first `k` elements) in **O(log n)** time.

This is much more efficient compared to a simple array, where such operations would take **O(n)** time.

#### 2. Structure and Concept

A Fenwick Tree is typically implemented as an array, where each element stores information about a cumulative frequency of elements up to a certain index. The key idea is to store the cumulative frequency in a way that allows quick computation of prefix sums and updates.

Given an array `arr[]` of size `n`, the Fenwick Tree can be visualized as:

```
            arr[] indices:    1   2   3   4   5   6   7   8   9  10
            Fenwick Tree:    F1  F2  F3  F4  F5  F6  F7  F8  F9  F10
```

Where `Fi` is the sum of some segment of `arr[]` depending on the structure of the tree.

#### 3. Fenwick Tree Operations

- **Initialization**: Constructing the tree from an array.
- **Update**: Updating an element in the array.
- **Query**: Computing the prefix sum up to a certain index.

#### 4. Implementation in C++

Let's implement a Fenwick Tree for a range sum query.

```cpp
#include <iostream>
#include <vector>
using namespace std;

class FenwickTree {
private:
    vector<int> bit;  // Binary Indexed Tree (BIT)
    int n;

public:
    // Constructor to initialize the Fenwick Tree with a given size
    FenwickTree(int n) {
        this->n = n;
        bit.assign(n + 1, 0);  // BIT is 1-indexed, so size is n + 1
    }

    // Constructor to initialize the Fenwick Tree with an initial array
    FenwickTree(vector<int>& arr) : FenwickTree(arr.size()) {
        for (size_t i = 0; i < arr.size(); i++) {
            update(i + 1, arr[i]);
        }
    }

    // Update function to add 'value' to index 'idx'
    void update(int idx, int value) {
        while (idx <= n) {
            bit[idx] += value;
            idx += idx & -idx;  // Move index to the next node in the tree
        }
    }

    // Query function to get the sum of the first 'idx' elements
    int query(int idx) {
        int sum = 0;
        while (idx > 0) {
            sum += bit[idx];
            idx -= idx & -idx;  // Move index to parent node
        }
        return sum;
    }

    // Function to get the sum of elements between l and r (1-based index)
    int rangeQuery(int l, int r) {
        return query(r) - query(l - 1);
    }
};

int main() {
    // Example usage
    vector<int> arr = {1, 2, 3, 4, 5};  // The initial array
    FenwickTree ft(arr);

    // Queries
    cout << "Sum of first 3 elements: " << ft.query(3) << endl;  // Output: 6
    cout << "Sum of elements from index 2 to 4: " << ft.rangeQuery(2, 4) << endl;  // Output: 9

    // Update
    ft.update(3, 5);  // Increase element at index 3 by 5
    cout << "After update, sum of first 3 elements: " << ft.query(3) << endl;  // Output: 11

    return 0;
}
```

#### 5. Explanation

1. **Initialization**:
   - `bit.assign(n + 1, 0);` initializes the BIT array of size `n + 1` with zeros. BIT is 1-indexed, so we add 1 to `n`.
   - The constructor `FenwickTree(vector<int>& arr)` initializes the BIT using the values of the given array by calling the `update` method for each element.

2. **Update Operation**:
   - The `update` function adds a value to the BIT at a specific index.
   - `idx += idx & -idx` moves the index to the next responsible element in the tree.

3. **Query Operation**:
   - The `query` function computes the prefix sum from index 1 to `idx`.
   - `idx -= idx & -idx` moves the index to its parent node in the tree.

4. **Range Query**:
   - The `rangeQuery(l, r)` function returns the sum of elements between indices `l` and `r` by subtracting the prefix sum up to `l-1` from the prefix sum up to `r`.

#### 6. Time Complexity

- **Update**: O(log n)
- **Query**: O(log n)
- **Range Query**: O(log n)

#### 7. Conclusion

A Fenwick Tree (BIT) is a powerful data structure for efficiently handling range sum queries and updates in logarithmic time. It is particularly useful in competitive programming and situations where frequent updates and queries are required.