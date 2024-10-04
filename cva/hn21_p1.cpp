#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <numeric>

using namespace std;

const long long LIMIT = 1000000;

// Function to calculate sum of divisors <= 10^6
long long sumDivisorsUnderMillion(long long L, long long R) {
    long long total_sum = 0;
    for (long long d = 1; d <= LIMIT; ++d) {
        // Find first multiple of d in range [L, R]
        long long first_multiple = (L + d - 1) / d; // This gives us the first integer k such that k*d >= L
        long long last_multiple = R / d;            // This gives us the last integer k such that k*d <= R

        if (first_multiple > last_multiple) continue;

        // If d is a divisor, add it to the sum
        total_sum += d;
    }
    return total_sum;
}

// Function to calculate the sum of divisors >= 10^6
long long sumDivisorsAboveMillion(long long L, long long R) {
    vector<pair<long long, long long>> ranges;

    // Calculate ranges for d from 1 to 1000
    for (long long d = 1; d <= 1000; ++d) {
        long long first = max(LIMIT + 1, (L + d - 1) / d); // First multiple of d in the range
        long long last = R / d;             // Last multiple of d in the range
        
        if (first <= last) {
            // cout << "d: " << d << " first: " << first << " last: " << last << endl;
            ranges.emplace_back(first, last);
        }
    }
    if (ranges.empty()) return 0;

    // Sort the ranges by starting point
    sort(ranges.begin(), ranges.end());
    // for (const auto& range : ranges) {
    //     cout << range.first << " " << range.second << endl;
    // }

    // Merge overlapping ranges
    vector<pair<long long, long long>> mergedRanges;
    long long currentStart = ranges[0].first;
    long long currentEnd = ranges[0].second;

    for (size_t i = 1; i < ranges.size(); ++i) {
        long long start = ranges[i].first;
        long long end = ranges[i].second;
        
        if (start <= currentEnd + 1) {
            // Overlapping or adjacent, merge
            currentEnd = max(currentEnd, end);
        } else {
            // No overlap, save the current range
            mergedRanges.emplace_back(currentStart, currentEnd);
            currentStart = start;
            currentEnd = end;
        }
    }
    // Save the last merged range
    mergedRanges.emplace_back(currentStart, currentEnd);

    // Calculate the sum of all numbers in merged ranges
    long long totalSum = 0;
    for (const auto& range : mergedRanges) {
        long long start = range.first;
        long long end = range.second;
        totalSum += (end - start + 1) * (start + end) / 2; // Sum of arithmetic series
    }

    return totalSum;
}

int main() {
    // Input handling
    long long L, R;
    cin >> L >> R;
    
    long long totalSum = 0;

    // Case 1: Divisors < 10^6
    totalSum += sumDivisorsUnderMillion(L, R);

    // Case 2: Divisors >= 10^6
    totalSum += sumDivisorsAboveMillion(L, R);
    
    // Output the result
    cout << totalSum << endl;

    return 0;
}

// 3449394270735
//  g++ -std=c++11 -O2 -Wall hn21_p1.cpp -o a && ./a < a.in