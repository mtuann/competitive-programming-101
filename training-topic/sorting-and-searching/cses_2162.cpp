// #include <iostream>
// #include <vector>

// using namespace std;

// int main() {
//     int n;
//     cin >> n;
    
//     vector<int> children(n);
//     for (int i = 0; i < n; ++i) {
//         children[i] = i + 1;
//     }
    
//     vector<int> removalOrder;
//     int current = 0;
//     int remaining = n;
    
//     while (remaining > 0) {
//         current = (current + 1) % remaining;  // Move to the next child to be removed
//         removalOrder.push_back(children[current]);
//         children.erase(children.begin() + current);
//         --remaining;
//     }
    
//     for (int i = 0; i < n; ++i) {
//         cout << removalOrder[i] << " ";
//     }
//     cout << endl;
    
//     return 0;
// }


#include <iostream>
#include <list>

using namespace std;

int main() {
    int n;
    cin >> n;

    list<int> children;
    for (int i = 1; i <= n; ++i) {
        children.push_back(i);
    }

    auto it = children.begin();
    while (!children.empty()) {
        it = next(it);
        if (it == children.end()) {
            it = children.begin();
        }
        cout << *it << " ";
        it = children.erase(it);
        if (it == children.end()) {
            it = children.begin();
        }
    }

    cout << endl;
    return 0;
}
