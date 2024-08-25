#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Event {
    int time;
    int type; // +1 for arrival, -1 for departure
    int index;
};

int main() {
    int n;
    cin >> n;

    vector<pair<int, int>> customers(n);
    vector<Event> events;
    for (int i = 0; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        customers[i] = {a, b};
        events.push_back({a, +1, i});    // arrival
        events.push_back({b + 1, -1, i}); // departure (b + 1)
    }

    sort(events.begin(), events.end(), [](const Event &e1, const Event &e2) {
        if (e1.time == e2.time) return e1.type < e2.type;
        return e1.time < e2.time;
    });

    int max_rooms = 0;
    int current_rooms = 0;
    vector<int> room_assignment(n);
    priority_queue<int, vector<int>, greater<int>> available_rooms;

    for (const auto& event : events) {
        if (event.type == +1) { // arrival
            current_rooms++;
            if (available_rooms.empty()) {
                max_rooms++;
                room_assignment[event.index] = max_rooms;
            } else {
                int room = available_rooms.top();
                available_rooms.pop();
                room_assignment[event.index] = room;
            }
        } else { // departure
            current_rooms--;
            available_rooms.push(room_assignment[event.index]);
        }
    }

    cout << max_rooms << endl;
    for (int i = 0; i < n; ++i) {
        cout << room_assignment[i] << " ";
    }
    cout << endl;

    return 0;
}
