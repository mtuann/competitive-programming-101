#include <iostream>
#include <set>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> cubes(n);
    
    for (int i = 0; i < n; ++i) {
        cin >> cubes[i];
    }
    
    multiset<int> towers;
    
    for (int cube : cubes) {
        auto it = towers.upper_bound(cube);
        if (it != towers.end()) {
            towers.erase(it);
        }
        towers.insert(cube);
    }
    
    cout << towers.size() << endl;
    
    return 0;
}
