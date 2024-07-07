In this tutorial, we will learn how to 
code a problem by dividing it into sub-tasks.
Consider the following problem:


Given an integer `n` ($1 \leq n \leq 10^5$), you need to calculate the sum of all positive integers less than or equal to `n`.
There are 4 sub-tasks:
- Sub-task 1: $1 \leq n \leq 10$
- Sub-task 2: $1 \leq n \leq 10^3$
- Sub-task 3: $1 \leq n \leq 10^6$
- Sub-task 4: $1 \leq n \leq 10^9$

The model solution follows the tutorial of [Hanh Van Pham](https://www.youtube.com/watch?v=3clQUr9Skw0&list=PLXSK7hGtCiHudz50Vbykh9zaR6HON1sIt&index=7). Please give him a like and subscribe to his channel.

The general idea is to divide the problem into sub-tasks and solve each sub-task separately using distinct namespaces. The main function will call the corresponding function based on the input.

### Algorithm
```cpp
#include <iostream>
#include <vector>

using namespace std;

bool subtask1(long long n) {
    return n <= 10;
}

bool subtask2(long long n) {
    return n <= 1000;
}

bool subtask3(long long n) {
    return n <= 1000000;
}

bool subtask4(long long n) {
    return n <= 1000000000;
}

namespace subtask1 {
    long long sum(long long n) {
        return n * (n + 1) / 2;
    }
}

namespace subtask2 {
    long long sum(long long n) {
        return n * (n + 1) / 2;
    }
}

namespace subtask3 {
    long long sum(long long n) {
        return n * (n + 1) / 2;
    }
}

namespace subtask4 {
    long long sum(long long n) {
        return n * (n + 1) / 2;
    }
}

int main() {
    long long n;
    cin >> n;

    if (subtask1(n)) return cout << subtask1::sum(n) << endl, 0;
    if (subtask2(n)) return cout << subtask2::sum(n) << endl, 0;
    if (subtask3(n)) return cout << subtask3::sum(n) << endl, 0;
    if (subtask4(n)) return cout << subtask4::sum(n) << endl, 0;

    return 0;
}
// g++ -std=c++14 -O2 -Wall -Wextra sumn.cpp -o sumn && ./sumn
```