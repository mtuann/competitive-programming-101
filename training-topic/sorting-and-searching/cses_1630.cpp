#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;
    
    vector<pair<int, int>> tasks(n);
    for (int i = 0; i < n; ++i) {
        cin >> tasks[i].first >> tasks[i].second;
    }

    // Sort tasks by their durations
    sort(tasks.begin(), tasks.end());

    long long totalReward = 0;
    long long currentTime = 0;

    for (int i = 0; i < n; ++i) {
        int duration = tasks[i].first;
        int deadline = tasks[i].second;

        currentTime += duration;
        totalReward += (deadline - currentTime);
    }

    cout << totalReward << endl;

    return 0;
}
