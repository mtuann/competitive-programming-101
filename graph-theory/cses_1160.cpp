#include <iostream>
#include <vector>

using namespace std;

vector<int> teleporter, cycle_length, distance_to_cycle, visited, cycle_id;

// DFS function to identify cycles and compute distances
void find_cycle(int planet) {
    vector<int> stack;
    while (!visited[planet]) {
        visited[planet] = 1;
        stack.push_back(planet);
        planet = teleporter[planet];
    }
    
    if (visited[planet] == 1) {
        int cycle_start = planet;
        int cycle_len = 0;
        // Count the length of the cycle
        do {
            cycle_length[planet] = cycle_len++;
            cycle_id[planet] = cycle_start;
            planet = teleporter[planet];
        } while (planet != cycle_start);
        
        // Assign cycle length to all planets in the cycle
        for (int i = 0; i < cycle_len; ++i) {
            planet = stack.back();
            stack.pop_back();
            visited[planet] = 2;
            distance_to_cycle[planet] = 0;
            cycle_length[planet] = cycle_len;
        }
    }

    // For non-cycle planets, calculate distance to the cycle
    while (!stack.empty()) {
        int current = stack.back();
        stack.pop_back();
        visited[current] = 2;
        distance_to_cycle[current] = distance_to_cycle[teleporter[current]] + 1;
        cycle_id[current] = cycle_id[teleporter[current]];
    }
}

int main() {
    int n, q;
    cin >> n >> q;
    
    teleporter.resize(n + 1);
    cycle_length.resize(n + 1);
    distance_to_cycle.resize(n + 1);
    visited.resize(n + 1, 0);
    cycle_id.resize(n + 1);
    
    // Input teleporters
    for (int i = 1; i <= n; ++i) {
        cin >> teleporter[i];
    }

    // Preprocess cycles and distances
    for (int i = 1; i <= n; ++i) {
        if (!visited[i]) {
            find_cycle(i);
        }
    }

    // Process queries
    for (int i = 0; i < q; ++i) {
        int a, b;
        cin >> a >> b;

        if (cycle_id[a] == cycle_id[b]) {
            if (distance_to_cycle[a] <= distance_to_cycle[b]) {
                cout << distance_to_cycle[b] - distance_to_cycle[a] << endl;
            } else {
                // Inside the same cycle
                int steps_in_cycle = (cycle_length[a] - distance_to_cycle[a]) + distance_to_cycle[b];
                cout << steps_in_cycle << endl;
            }
        } else {
            // a cannot reach b
            cout << -1 << endl;
        }
    }
    
    return 0;
}
