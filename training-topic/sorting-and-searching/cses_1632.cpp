#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct Movie {
    int start, end;
    bool operator<(const Movie& other) const {
        return end < other.end; // Sorting by ending time
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, k;
    cin >> n >> k;
    
    vector<Movie> movies(n);
    for (int i = 0; i < n; ++i) {
        cin >> movies[i].start >> movies[i].end;
    }

    // Sort movies by their ending time
    sort(movies.begin(), movies.end());

    // Min-heap to keep track of the end times of the movies being watched by each member
    priority_queue<int, vector<int>, greater<int>> endTimes;

    int maxMovies = 0;

    for (const Movie& movie : movies) {
        cout << movie.start << " " << movie.end << endl;
        // Assign the movie to a member (either a free one or a new member if less than k members are using the heap)
        if (endTimes.size() < k) {
            cout << "Watching movie: " << movie.start << " " << movie.end << endl;
            ++maxMovies;
            while (!endTimes.empty() && endTimes.top() <= movie.start) {
                // Reuse the member who has finished watching their movie
                endTimes.pop();
            }
            endTimes.push(movie.end);
        }
        // Update the end time for the member watching this movie
        
    }

    cout << maxMovies << endl;

    return 0;
}
// g++ -std=c++14 -O2 -Wall cses_1632.cpp -o a && ./a < a.in