#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

long long max_flow(vector<vector<int>> adj, vector<vector<long long>> capacity,
                   int source, int sink) {
	int n = adj.size();
	vector<int> parent(n, -1);
	// Find a way from the source to sink on a path with non-negative capacities
	auto reachable = [&]() -> bool {
		queue<int> q;
		q.push(source);
		while (!q.empty()) {
			int node = q.front();
			q.pop();
			for (int son : adj[node]) {
				long long w = capacity[node][son];
				if (w <= 0 || parent[son] != -1) continue;
				parent[son] = node;
				q.push(son);
			}
		}
		return parent[sink] != -1;
	};

	long long flow = 0;
	// While there is a way from source to sink with non-negative capacities
	while (reachable()) {
		int node = sink;
		// The minimum capacity on the path from source to sink
		long long curr_flow = LLONG_MAX;
		while (node != source) {
			curr_flow = min(curr_flow, capacity[parent[node]][node]);
			node = parent[node];
		}
        cout << "curr_flow: " << curr_flow << endl;
        cout << "Augmenting path: ";
		node = sink;
		while (node != source) {
            cout << node + 1<< " ";
			// Subtract the capacity from capacity edges
			capacity[parent[node]][node] -= curr_flow;
			// Add the current flow to flow backedges
			capacity[node][parent[node]] += curr_flow;
			node = parent[node];
		}
        cout << source + 1<< endl;
		flow += curr_flow;
		fill(parent.begin(), parent.end(), -1);
	}

	return flow;
}

int main() {
	int n, m;
	cin >> n >> m;

	vector<vector<long long>> capacity(n, vector<long long>(n));
	vector<vector<int>> adj(n);
	for (int i = 0; i < m; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		adj[--a].push_back(--b);
		adj[b].push_back(a);
		capacity[a][b] += c;
	}

	cout << max_flow(adj, capacity, 0, n - 1) << endl;
    return 0;
}