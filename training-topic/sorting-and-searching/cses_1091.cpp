#include <iostream>
#include <vector>
#include <set>
using namespace std;

const int MAXN = 2e5 + 10;
int n, m;
multiset<int> ticket_prices;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    // Read the ticket prices
    for (int i = 0; i < n; ++i) {
        int price;
        cin >> price;
        ticket_prices.insert(price);
    }

    // Read the maximum prices customers are willing to pay
    for (int i = 0; i < m; ++i) {
        int max_price;
        cin >> max_price;
        auto it = ticket_prices.upper_bound(max_price);
        if (it == ticket_prices.begin()) {
            // No ticket can be assigned to this customer
            cout << -1 << "\n";
        } else {
            // A suitable ticket is found
            --it; // Move to the largest element that is <= max_prices[i]
            cout << *it << "\n";
            ticket_prices.erase(it); // Remove this ticket from the set
        }
    }

    return 0;
}
