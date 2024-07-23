# Bronze
## 1. Getting Started
### 1.1. [Time Complexity](https://usaco.guide/bronze/time-comp?lang=cpp)
- Time complexity is a measure of how the runtime of an algorithm scales with the size of the input.
- The time complexity of an algorithm is usually expressed in big O notation.
- The time complexity of an algorithm is the worst-case time complexity.
- The time complexity of an algorithm is the maximum number of operations the algorithm will perform on an input of size `n`.

### 1.2. [Introduction to Data Structures](https://usaco.guide/bronze/intro-ds?lang=cpp)
- Static arrays are arrays that have a fixed size.
- Dynamic arrays are arrays that can grow or shrink in size.
    - Iterators are a way to traverse a data structure.
    - Insertion and deletion in a dynamic array can be done in `O(n)` time.
- Strings are sequences of characters.
- Pair is a data structure that stores two elements.
- Tuples are data structures that store multiple elements.

The list of data structures that are commonly used in competitive programming:
- Vectors are dynamic arrays in C++.
- Stacks are a data structure that supports two operations: push and pop.
- Queues are a data structure that supports two operations: push and pop.
- Priority queues are a data structure that supports two operations: push and pop, with the element with the highest priority being popped first.
- Sets are a data structure that stores unique elements (unordered_set in C++).
- Maps are a data structure that stores key-value pairs (unordered_map in C++).

<details>
<summary>Demo using `tuples`</summary>

```cpp
#include <iostream>
#include <tuple>

/**
 * Output:
 * 3 4 5
 * 7 4 5
 * Hello world 100
 */

using namespace std;

int main() {
    tuple<int, int, int> t = {1, 2, 3};
    cout << get<0>(t) << " " << get<1>(t) << " " << get<2>(t) << endl;
    
    get<0>(t) = 7;
	cout << get<0>(t) << " " << get<1>(t) << " " << get<2>(t) << endl;
    
    tuple<string, string, int> tp2 = make_tuple("Hello", "world", 100);
	string s1, s2;
	int x;
	tie(s1, s2, x) = tp2;
	cout << s1 << " " << s2 << " " << x << endl;

    return 0;
}
```
</details>

## 2. Complete Search
### 2.1. [Basic Complete Search](https://usaco.guide/bronze/intro-complete?lang=cpp)
The idea of complete search is to try all possible solutions to a problem, usually by iterating through all possible values of the solution. Sometimes, complete search is also called brute force.

The two main types of complete search are:
- Iterative complete search: This is the simplest form of complete search, where you iterate through all possible values of the solution.
- Recursive complete search: This is complete search using recursion, where you try all possible values of the solution by recursively trying all possible values of the next part of the solution.

### 2.2. [Complete Search with Recursion](https://usaco.guide/bronze/complete-rec?lang=cpp)
The main idea of recursive complete search is to try generating all possible subsets and permutations of the solution.
- Subsets: A subset is a set that contains some or all of the elements of the original set.

- Permutations: A permutation is an arrangement of the elements of a set in a specific order.

- Backtracking: Backtracking is a technique used to generate all possible solutions to a problem by trying all possible values of the solution and backtracking when a solution is not valid.

## 3. Sorting and Sets
### 3.1. [Introduction to Sorting](https://usaco.guide/bronze/intro-sorting?lang=cpp)

### 3.2. [(Optional) Introduction to Sets & Maps](https://usaco.guide/bronze/intro-sets?lang=cpp)

## 4. Additional Problems
### 4.1 [Ad Hoc Problems](https://usaco.guide/bronze/ad-hoc?lang=cpp)

### 4.2 [Introduction to Greedy Algorithms](https://usaco.guide/bronze/intro-greedy?lang=cpp)

### 4.3 [Introduction to Graphs](https://usaco.guide/bronze/intro-graphs?lang=cpp)

### 4.4 [Rectangle Geometry](https://usaco.guide/bronze/rect-geo?lang=cpp)


## 5. Conclusion and Additional Practice for USACO Bronze

# Silver

# Gold

# Platinum

# Advanced