#include <iostream>
#include <vector>

using namespace std;

void findTeleportationCounts(int n, vector<int>& teleporters) {
    vector<int> result(n, 0);
    vector<int> visited(n, -1);

    for (int i = 0; i < n; i++) {
        if (result[i] != 0) {
            continue;  // If this planet already has a calculated result, skip it.
        }
        cout << "Starting from planet " << i << endl;
        vector<int> path;  // Stores the current path of teleportations.
        int current = i;
        
        while (visited[current] == -1) {
            visited[current] = path.size();
            path.push_back(current);
            current = teleporters[current] - 1;
        }
        // print the path
        for (int j = 0; j < path.size(); j++) {
            cout << path[j] << " ";
        }
        cout << endl;

        int loop_start = visited[current];
        int loop_length = path.size() - loop_start;

        // Assign loop length to all planets in the loop.
        for (int j = loop_start; j < path.size(); j++) {
            result[path[j]] = loop_length;
        }

        // Calculate the number of teleportations for planets before entering the loop.
        for (int j = 0; j < loop_start; j++) {
            result[path[j]] = loop_length + (loop_start - j);
        }
    }

    // Output the results
    for (int i = 0; i < n; i++) {
        cout << result[i] << " ";
    }
    cout << endl;
}

int main() {
    int n;
    cin >> n;
    
    vector<int> teleporters(n);
    for (int i = 0; i < n; i++) {
        cin >> teleporters[i];
    }
    
    findTeleportationCounts(n, teleporters);

    return 0;
}
// g++ -std=c++17 -O2 -Wall cses_1751.cpp -o a && ./a < a.in