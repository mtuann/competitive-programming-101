#include <iostream>
#include <vector>
#include <set>

using namespace std;

void insertMultiset(multiset<int>& ms, int value) {
    ms.insert(value);
}

void eraseMultiset(multiset<int>& ms, int value) {
    auto it = ms.find(value);
    if (it != ms.end()) {
        ms.erase(it);
    }
}

int getMedian(const multiset<int>& ms, int k) {
    auto it = ms.begin();
    advance(it, (k - 1) / 2);
    return *it;
}

int main() {
    int n, k;
    cin >> n >> k;
    
    vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }
    
    multiset<int> window;
    vector<int> medians;

    for (int i = 0; i < n; ++i) {
        insertMultiset(window, arr[i]);
        
        if (i >= k - 1) {
            medians.push_back(getMedian(window, k));
            eraseMultiset(window, arr[i - k + 1]);
        }
    }
    
    for (int median : medians) {
        cout << median << " ";
    }
    cout << endl;
    
    return 0;
}
