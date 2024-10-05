#include <iostream>
#include <vector>
using namespace std;

const int MAX = 1e6 + 5;

int main() {
    int n;
    cin >> n;
    
    vector<int> arr(n);
    vector<int> freq(MAX, 0);
    
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        freq[arr[i]]++;
    }
    
    // Total number of pairs (n choose 2)
    long long totalPairs = 1LL * n * (n - 1) / 2;
    
    // Array to count how many numbers are divisible by i
    vector<long long> countDivisible(MAX, 0);
    
    // For each g, count how many numbers are divisible by g
    for (int g = 1; g < MAX; g++) {
        for (int multiple = g; multiple < MAX; multiple += g) {
            countDivisible[g] += freq[multiple];
        }
    }
    
    // Now, calculate pairs that share a common divisor greater than 1
    long long nonCoprimePairs = 0;
    
    for (int g = 2; g < MAX; g++) {
        if (countDivisible[g] >= 2) {
            // Number of pairs with GCD >= g
            nonCoprimePairs += countDivisible[g] * (countDivisible[g] - 1) / 2;
        }
    }
    
    // The result is total pairs minus non-coprime pairs
    long long coprimePairs = totalPairs - nonCoprimePairs;
    
    cout << coprimePairs << endl;
    
    return 0;
}
