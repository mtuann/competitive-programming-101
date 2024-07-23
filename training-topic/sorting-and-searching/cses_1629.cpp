#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Movie {
    int start;
    int end;
};

// Comparator to sort movies by end time
bool compareMovies(const Movie &m1, const Movie &m2) {
    return m1.end < m2.end;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<Movie> movies(n);

    // Read the start and end times of each movie
    for (int i = 0; i < n; ++i) {
        cin >> movies[i].start >> movies[i].end;
    }

    // Sort the movies by their end times
    sort(movies.begin(), movies.end(), compareMovies);

    int count = 0;
    int last_end_time = 0;

    // Iterate through the sorted movies and select non-overlapping movies
    for (const auto &movie : movies) {
        if (movie.start >= last_end_time) {
            count++;
            last_end_time = movie.end;
        }
    }

    cout << count << endl;

    return 0;
}