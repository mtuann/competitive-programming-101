#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Project {
    int start, end, reward;
};

bool compareByEnd(const Project& a, const Project& b) {
    return a.end < b.end;
}

// Function to find the last non-overlapping project
// int findLastNonOverlapping(const vector<Project>& projects, int index) {
//     int low = 0, high = index - 1;
//     int target = projects[index].start;
    
//     while (low <= high) {
//         int mid = low + (high - low) / 2;
//         if (projects[mid].end < target) {
//             low = mid + 1;
//         } else {
//             high = mid - 1;
//         }
//     }
//     return high; // Return the index of the last non-overlapping project
// }


int findLastNonOverlapping(const vector<Project>& projects, int index) {
    int low = 0, high = index - 1;
    int target = projects[index].start;
    
    while (low < high) {
        int mid = (low + high + 1) / 2;
        if (projects[mid].end < target) {
            low = mid;
        } else {
            high = mid - 1;
        }
    }
    return projects[low].end < target ? low : -1; // Return the index of the last non-overlapping project
}


int main() {
    int n;
    cin >> n;
    vector<Project> projects(n);

    for (int i = 0; i < n; ++i) {
        cin >> projects[i].start >> projects[i].end >> projects[i].reward;
    }

    // Sort projects by end day
    sort(projects.begin(), projects.end(), compareByEnd);

    vector<long long> dp(n, 0);
    dp[0] = projects[0].reward;

    for (int i = 1; i < n; ++i) {
        // Option 1: Not taking the current project
        dp[i] = dp[i - 1];
        // Option 2: Taking the current project
        int lastNonOverlap = findLastNonOverlapping(projects, i);
        long long includeCurrent = projects[i].reward;
        if (lastNonOverlap != -1) {
            includeCurrent += dp[lastNonOverlap];
        }
        dp[i] = max(dp[i], includeCurrent);
    }

    cout << dp[n - 1] << endl;

    return 0;
}
