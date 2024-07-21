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
// remind calculate a * b > 10^18, use long long