# Binary Search
## Finding The Maximum x Such That f(x) = true
Let's say we have a boolean function `f(x)` that is monotonically increasing. We want to find the maximum `x` such that `f(x) = true`. We can use binary search to find this value.
Since `f(x)` satisfies both of following conditions:
1. `f(x) = true` for all `x` such that `x >= x0`
2. `f(x) = false` for all `x` such that `x < x0`
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
1. `f(x) = true` for all `x` such that `x <= x0`
2. `f(x) = false` for all `x` such that `x > x0`
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
```
cout << lower << " " << upper << endl; // Output: 3 6
```
