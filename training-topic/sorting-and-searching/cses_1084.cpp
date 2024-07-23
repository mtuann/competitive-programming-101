#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 2e5 + 10;
int n, m, k;
int applicants[MAXN];
int apartments[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> n >> m >> k;

    for (int i = 0; i < n; ++i) {
        cin >> applicants[i];
    }

    for (int i = 0; i < m; ++i) {
        cin >> apartments[i];
    }

    // Sort both the applicants and the apartments
    sort(applicants, applicants + n);
    sort(apartments, apartments + m);

    int i = 0; // Index for applicants
    int j = 0; // Index for apartments
    int count = 0;

    while (i < n && j < m) {
        if (apartments[j] < applicants[i] - k) {
            // Apartment too small, move to the next apartment
            j++;
        } else if (apartments[j] > applicants[i] + k) {
            // Apartment too big, move to the next applicant
            i++;
        } else {
            // Apartment fits within the acceptable range
            count++;
            i++;
            j++;
        }
    }

    cout << count << endl;

    return 0;
}
