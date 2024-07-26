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

// g++ -std=c++11 -O2 -Wall cses_1141.cpp -o a && ./a < a.in

// #include <iostream>
// #include <unordered_set>
// #include <vector>

// using namespace std;

// int longestUniqueSubsequence(const vector<int>& songs) {
//     unordered_set<int> songSet;
//     int maxLength = 0;
//     int start = 0;

//     for (int end = 0; end < songs.size(); ++end) {
//         // Move start forward until we remove the duplicate song
//         while (songSet.find(songs[end]) != songSet.end()) {
//             songSet.erase(songs[start]);
//             ++start;
//         }
//         // Add the current song to the set
//         songSet.insert(songs[end]);
//         // Update the maximum length
//         maxLength = max(maxLength, end - start + 1);
//     }

//     return maxLength;
// }

// int main() {
//     ios::sync_with_stdio(0);
//     cin.tie(0);
//     int n;
//     cin >> n;
//     vector<int> songs(n);
    
//     for (int i = 0; i < n; ++i) {
//         cin >> songs[i];
//     }
    
//     cout << longestUniqueSubsequence(songs) << endl;
    
//     return 0;
// }
