#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

void generatePermutations(string& s, int left, int right, set<string>& permutations) {
    if (left == right) {
        permutations.insert(s);
    } else {
        for (int i = left; i <= right; ++i) {
            swap(s[left], s[i]);
            generatePermutations(s, left + 1, right, permutations);
            swap(s[left], s[i]); // backtrack
        }
    }
}

int main() {
    string s;
    cin >> s;

    set<string> permutations;
    generatePermutations(s, 0, s.size() - 1, permutations);

    // Convert set to vector for sorting
    vector<string> sortedPermutations(permutations.begin(), permutations.end());
    sort(sortedPermutations.begin(), sortedPermutations.end());

    // Output results
    cout << sortedPermutations.size() << endl;
    for (const string& perm : sortedPermutations) {
        cout << perm << endl;
    }

    return 0;
}
