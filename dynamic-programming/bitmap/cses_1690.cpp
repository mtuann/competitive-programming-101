#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int MAX_N = 20;
const ll MOD = (ll)1e9 + 7;

ll dp[1 << MAX_N][MAX_N];
// come_from[i] contains the cities that can fly to i
vector<int> come_from[MAX_N];

int main() {
	int city_num;
	int flight_num;
	cin >> city_num >> flight_num;
	for (int f = 0; f < flight_num; f++) {
		int start, end;
		cin >> start >> end;
		come_from[--end].push_back(--start);
	}

	dp[1][0] = 1;
	for (int s = 2; s < 1 << city_num; s++) {
		// only consider subsets that have the first city
		if ((s & (1 << 0)) == 0) continue;
		// also only consider subsets with the last city if it's the full subset
		if ((s & (1 << (city_num - 1))) && s != ((1 << city_num) - 1)) continue;

		for (int end = 0; end < city_num; end++) {
			if ((s & (1 << end)) == 0) continue;

			// the subset that doesn't include the current end
			int prev = s - (1 << end);
			for (int j : come_from[end]) {
				if ((s & (1 << j))) {
					dp[s][end] += dp[prev][j];
					dp[s][end] %= MOD;
				}
			}
		}
	}
	cout << dp[(1 << city_num) - 1][city_num - 1] << '\n';
}