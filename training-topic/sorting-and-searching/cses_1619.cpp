#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 2e5 + 10;

struct Event {
    int time;
    int type; // +1 for arrival, -1 for departure
};

// Custom comparator to sort events
bool compareEvents(const Event &e1, const Event &e2) {
    if (e1.time == e2.time) {
        return e1.type < e2.type; // Prioritize departures over arrivals if times are the same
    }
    return e1.time < e2.time;
}

int n;
Event events[2 * MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    int nn = 0;
    // Read the arrival and departure times
    for (int i = 0; i < n; ++i) {
        int arrival, departure;
        cin >> arrival >> departure;
        events[nn++] = {arrival, 1}; // Arrival event
        events[nn++] = {departure, -1}; // Departure event
    }

    // Sort the events
    sort(events, events + nn, compareEvents);

    int current_customers = 0;
    int max_customers = 0;

    // Process the events
    for (int i = 0; i < nn; ++i) {
        Event event = events[i];
        current_customers += event.type;
        if (current_customers > max_customers) {
            max_customers = current_customers;
        }
    }

    cout << max_customers << endl;

    return 0;
}
