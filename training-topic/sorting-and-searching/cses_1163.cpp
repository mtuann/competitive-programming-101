#include <iostream>
#include <set>
#include <map>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int x, n;
    cin >> x >> n;
    vector<int> positions(n);
    
    for (int i = 0; i < n; ++i) {
        cin >> positions[i];
    }
    
    set<int> lights;
    multiset<int> segments;
    
    // Initially, we have one segment from 0 to x
    lights.insert(0);
    lights.insert(x);
    segments.insert(x);
    
    for (int p : positions) {
        auto it = lights.lower_bound(p);
        int right = *it;
        int left = *(--it);
        
        // Remove the current segment
        segments.erase(segments.find(right - left));
        
        // Insert new segments
        segments.insert(p - left);
        segments.insert(right - p);
        
        // Insert the new light position
        lights.insert(p);
        
        // Output the maximum segment length
        cout << *segments.rbegin() << " ";
    }
    
    cout << endl;
    
    return 0;
}
