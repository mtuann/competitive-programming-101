#include <iostream>
#include <vector>

using namespace std;

vector<int> teleporters, result, visited, cycle_size;

// DFS function to compute teleportation counts
int dfs(int planet) {
    if (visited[planet] == 1) {
        // We found a cycle
        visited[planet] = 2;
        int cycle_start = planet, cycle_length = 1;
        int next = teleporters[planet];
        while (next != cycle_start) {
            visited[next] = 2;
            next = teleporters[next];
            cycle_length++;
        }
        
        // Assign cycle length to all planets in the cycle
        next = planet;
        do {
            result[next] = cycle_length;
            next = teleporters[next];
        } while (next != cycle_start);
        
        return cycle_length;
    }

    if (visited[planet] == 2) {
        // Planet already fully processed (part of a known cycle or result)
        return result[planet];
    }

    visited[planet] = 1;  // Mark as visited (in-progress)
    int next = teleporters[planet];
    int total_steps = dfs(next) + 1;  // Move to next planet
    
    visited[planet] = 2;  // Mark as fully processed
    result[planet] = total_steps;
    return total_steps;
}

int main() {
    int n;
    cin >> n;
    
    teleporters.resize(n + 1);
    result.resize(n + 1);
    visited.resize(n + 1, 0);
    
    for (int i = 1; i <= n; ++i) {
        cin >> teleporters[i];
    }
    
    // Process each planet using DFS
    for (int i = 1; i <= n; ++i) {
        if (visited[i] == 0) {
            dfs(i);
        }
    }
    
    // Output the results
    for (int i = 1; i <= n; ++i) {
        cout << result[i] << " ";
    }
    cout << endl;
    
    return 0;
}

// g++ -std=c++17 -O2 -Wall cses_1751.cpp -o a && ./a < a.in