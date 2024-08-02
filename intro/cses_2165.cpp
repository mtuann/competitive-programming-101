#include <iostream>
#include <vector>

using namespace std;

// Recursive function to solve the Tower of Hanoi problem
void solveHanoi(int n, int from, int to, int aux, vector<pair<int, int>>& moves) {
    if (n == 0) return;

    // Move n-1 disks from 'from' to 'aux', using 'to' as auxiliary
    solveHanoi(n - 1, from, aux, to, moves);
    
    // Move the nth disk from 'from' to 'to'
    moves.push_back({from, to});
    
    // Move n-1 disks from 'aux' to 'to', using 'from' as auxiliary
    solveHanoi(n - 1, aux, to, from, moves);
}

int main() {
    int n;
    cin >> n;

    vector<pair<int, int>> moves;
    
    // Solve the Tower of Hanoi problem
    solveHanoi(n, 1, 3, 2, moves);
    
    // Output the number of moves
    cout << moves.size() << endl;
    
    // Output the moves
    for (const auto& move : moves) {
        cout << move.first << " " << move.second << endl;
    }

    return 0;
}
