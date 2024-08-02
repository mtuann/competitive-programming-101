#include <iostream>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;
    
    vector<int> coins(n);
    for (int i = 0; i < n; ++i) {
        cin >> coins[i];
    }

    set<int> possible_sums;
    possible_sums.insert(0);

    for (int coin : coins) {
        vector<int> new_sums;
        for (int sum : possible_sums) {
            new_sums.push_back(sum + coin);
        }
        for (int new_sum : new_sums) {
            possible_sums.insert(new_sum);
        }
    }

    // Remove 0 if it is not required in the output
    possible_sums.erase(0);
    
    vector<int> sorted_sums(possible_sums.begin(), possible_sums.end());
    
    cout << sorted_sums.size() << endl;
    for (int sum : sorted_sums) {
        cout << sum << " ";
    }
    cout << endl;

    return 0;
}
