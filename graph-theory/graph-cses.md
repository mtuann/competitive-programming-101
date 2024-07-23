
## Bipartite Graph
- https://cses.fi/problemset/task/1668/

### Approach:

1. **Graph Representation**: Represent the pupils and their friendships as a graph. Pupils are nodes, and friendships are edges.
2. **Bipartite Check**: A graph is bipartite if we can color its nodes with two colors such that no two adjacent nodes have the same color.
3. **Graph Traversal**: Use BFS (Breadth-First Search) or DFS (Depth-First Search) to try to color the graph. If we find a contradiction (i.e., two adjacent nodes having the same color), the graph is not bipartite.


```cpp
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

bool bfs(int start, vector<vector<int>>& adj, vector<int>& team) {
    queue<int> q;
    q.push(start);
    team[start] = 1;  // Assign team 1 to the start node

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v : adj[u]) {
            if (team[v] == 0) {
                // Assign the opposite team to the adjacent node
                team[v] = 3 - team[u];
                q.push(v);
            } else if (team[v] == team[u]) {
                // If the adjacent node has the same team, the graph is not bipartite
                return false;
            }
        }
    }

    return true;
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj(n + 1); // Adjacency list for the graph
    vector<int> team(n + 1, 0); // Team assignment for each pupil, 0 means unassigned

    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    // Try to color the graph using BFS
    for (int i = 1; i <= n; ++i) {
        if (team[i] == 0) { // If the node is unassigned, perform BFS
            if (!bfs(i, adj, team)) {
                cout << "IMPOSSIBLE" << endl;
                return 0;
            }
        }
    }

    // If the graph is bipartite, print the team assignment
    for (int i = 1; i <= n; ++i) {
        cout << team[i] << " ";
    }
    cout << endl;

    return 0;
}
```

### Explanation:
1. **Input Reading**: The input is read into a graph representation using an adjacency list.
2. **Team Assignment**: The `team` vector keeps track of which team each pupil is assigned to (1 or 2). If a pupil is unassigned, it is marked as 0.
3. **BFS for Bipartite Check**: The `bfs` function attempts to color the graph using BFS. If it encounters a contradiction, it returns false.
4. **Traversal**: The main loop ensures all connected components are checked by initiating a BFS from every unassigned node.
5. **Output**: If a valid bipartite coloring is found, the team assignments are printed. Otherwise, "IMPOSSIBLE" is printed.

## Counting Rooms (DFS/ BFS in matrix graph)
- https://cses.fi/problemset/task/1192/

### Approach:

1. **Input Reading**: Read the dimensions of the map and then the map itself.
2. **Visited Array**: Use a 2D array to keep track of visited cells to avoid recounting the same room.
3. **DFS/BFS Traversal**: For each unvisited floor cell, perform a DFS/BFS to mark all reachable floor cells as visited. Each time you start a DFS/BFS from an unvisited floor cell, increment the room count.
4. **Count Rooms**: The number of times you start a DFS/BFS traversal will be the number of rooms.


```cpp
#include <iostream>
#include <vector>
#include <stack>

using namespace std;

void dfs(int x, int y, const vector<vector<char>>& map, vector<vector<bool>>& visited) {
    int n = map.size();
    int m = map[0].size();
    stack<pair<int, int>> s;
    s.push({x, y});
    visited[x][y] = true;
    
    int directions[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}}; // Right, Down, Left, Up

    while (!s.empty()) {
        int cx = s.top().first;
        int cy = s.top().second;
        s.pop();

        for (int i = 0; i < 4; ++i) {
            int nx = cx + directions[i][0];
            int ny = cy + directions[i][1];

            if (nx >= 0 && nx < n && ny >= 0 && ny < m && !visited[nx][ny] && map[nx][ny] == '.') {
                visited[nx][ny] = true;
                s.push({nx, ny});
            }
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<char>> map(n, vector<char>(m));
    vector<vector<bool>> visited(n, vector<bool>(m, false));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> map[i][j];
        }
    }

    int room_count = 0;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (map[i][j] == '.' && !visited[i][j]) {
                ++room_count;
                dfs(i, j, map, visited);
            }
        }
    }

    cout << room_count << endl;

    return 0;
}
```

### Explanation:

1. **Input Reading**: The map is read into a 2D vector `map`. The dimensions `n` and `m` are read first.
2. **Visited Array**: A 2D vector `visited` is initialized to keep track of visited cells.
3. **DFS Function**: The `dfs` function performs a DFS starting from a given cell `(x, y)`, marking all connected floor cells as visited. It uses a stack to manage the DFS traversal.
4. **Main Logic**: The main part of the code iterates over each cell of the map. If an unvisited floor cell is found, it indicates the start of a new room. The `dfs` function is called from that cell, and the room count is incremented.
5. **Output**: Finally, the number of rooms is printed.

## Labyrinth (BFS/ DFS)
- https://cses.fi/problemset/task/1193/

To solve the problem of finding the shortest path in a labyrinth from the start position 'A' to the end position 'B', we can use the Breadth-First Search (BFS) algorithm. BFS is ideal for finding the shortest path in an unweighted grid.

### Approach:
1. **Input Reading**: Read the dimensions of the map and then the map itself.
2. **BFS Initialization**: Initialize BFS from the start position 'A'.
3. **Direction Vectors**: Use direction vectors to explore neighboring cells.
4. **Path Tracking**: Use an auxiliary data structure to track the previous cell and direction for reconstructing the path once the end 'B' is reached.
5. **Output**: If BFS reaches 'B', reconstruct and output the path; otherwise, output "NO".

Here is the implementation in C++:

```cpp
#include <iostream>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

struct Cell {
    int x, y;
};

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<char>> labyrinth(n, vector<char>(m));
    vector<vector<bool>> visited(n, vector<bool>(m, false));
    vector<vector<Cell>> previous(n, vector<Cell>(m, {-1, -1}));
    vector<vector<char>> direction(n, vector<char>(m));
    Cell start, end;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> labyrinth[i][j];
            if (labyrinth[i][j] == 'A') {
                start = {i, j};
            } else if (labyrinth[i][j] == 'B') {
                end = {i, j};
            }
        }
    }

    queue<Cell> q;
    q.push(start);
    visited[start.x][start.y] = true;

    int directions[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    char dir_chars[4] = {'R', 'D', 'L', 'U'};

    bool found = false;

    while (!q.empty()) {
        Cell current = q.front();
        q.pop();

        if (current.x == end.x && current.y == end.y) {
            found = true;
            break;
        }

        for (int i = 0; i < 4; ++i) {
            int nx = current.x + directions[i][0];
            int ny = current.y + directions[i][1];

            if (nx >= 0 && nx < n && ny >= 0 && ny < m && !visited[nx][ny] && labyrinth[nx][ny] != '#') {
                visited[nx][ny] = true;
                previous[nx][ny] = current;
                direction[nx][ny] = dir_chars[i];
                q.push({nx, ny});
            }
        }
    }

    if (found) {
        cout << "YES" << endl;

        // Reconstruct path
        string path;
        Cell current = end;
        while (current.x != start.x || current.y != start.y) {
            path.push_back(direction[current.x][current.y]);
            current = previous[current.x][current.y];
        }
        reverse(path.begin(), path.end());

        cout << path.length() << endl;
        cout << path << endl;
    } else {
        cout << "NO" << endl;
    }

    return 0;
}
```

### Explanation:
1. **Input Reading**: The labyrinth is read into a 2D vector, and the start ('A') and end ('B') positions are stored.
2. **BFS Initialization**: A queue is initialized with the start position, and the corresponding cell is marked as visited.
3. **BFS Traversal**: The BFS explores all four possible directions from each cell. If a neighbor is reachable (not a wall and not visited), it is added to the queue, marked as visited, and its predecessor and direction are recorded.
4. **Path Reconstruction**: Once the end position 'B' is reached, the path is reconstructed by backtracking from 'B' to 'A' using the recorded predecessors and directions.
5. **Output**: If a path is found, "YES", the path length, and the path itself are printed. If no path is found, "NO" is printed.

## Building Roads (BFS/ DFS)
- https://cses.fi/problemset/task/1666

To solve this problem, we need to ensure that all cities are connected, meaning we need to create a connected graph. A connected graph is one in which there is a path between any pair of vertices. This can be achieved by connecting the different components of the graph with the minimum number of edges.

### Approach:
1. **Input Reading**: Read the number of cities and roads.
2. **Graph Representation**: Represent the cities and roads using an adjacency list.
3. **Connected Components Identification**: Use a graph traversal technique (BFS or DFS) to identify all the connected components.
4. **Connecting Components**: To connect all components, you need at least (number of components - 1) new roads. Connect the components by adding edges between nodes of different components.
5. **Output**: Print the number of new roads required and the pairs of cities that form these roads.

Here is the implementation in C++:

```cpp
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

void bfs(int start, const vector<vector<int>>& adj, vector<bool>& visited) {
    queue<int> q;
    q.push(start);
    visited[start] = true;

    while (!q.empty()) {
        int node = q.front();
        q.pop();
        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj(n + 1);
    vector<bool> visited(n + 1, false);

    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    vector<int> component_representatives;

    for (int i = 1; i <= n; ++i) {
        if (!visited[i]) {
            component_representatives.push_back(i);
            bfs(i, adj, visited);
        }
    }

    int num_new_roads = component_representatives.size() - 1;
    cout << num_new_roads << endl;

    for (int i = 1; i < component_representatives.size(); ++i) {
        cout << component_representatives[i - 1] << " " << component_representatives[i] << endl;
    }

    return 0;
}
```

## Message Route (BFS)
- https://cses.fi/problemset/task/1667

### Explanation:
1. **Input Reading**: We read the number of cities \( n \) and roads \( m \), and then read each road into the adjacency list `adj`.
2. **Graph Representation**: The adjacency list `adj` is used to represent the graph.
3. **BFS for Connected Components**: We use BFS to traverse each component of the graph. The `visited` array keeps track of visited cities. For each unvisited city, we initiate a BFS and mark all reachable cities.
4. **Component Representatives**: Each time we find a new component, we record a representative city of that component in the `component_representatives` vector.
5. **Connecting Components**: To connect all components, we need (number of components - 1) new roads. We connect each component's representative to the next.
6. **Output**: We print the number of new roads required and the pairs of cities that form these new roads.



To solve the problem of finding the shortest path from Uolevi's computer (node 1) to Maija's computer (node \( n \)) in a network of computers, we can use the Breadth-First Search (BFS) algorithm. BFS is ideal for finding the shortest path in an unweighted graph.

### Approach:
1. **Input Reading**: Read the number of computers and connections.
2. **Graph Representation**: Use an adjacency list to represent the graph.
3. **BFS Initialization**: Initialize BFS from the start node (1).
4. **Path Tracking**: Use auxiliary data structures to track the previous node and the distance for each node.
5. **Reconstructing the Path**: If BFS reaches the end node (\( n \)), reconstruct the path by backtracking from node \( n \) to node 1 using the recorded predecessors.
6. **Output**: Print the number of nodes in the path and the path itself. If no path is found, print "IMPOSSIBLE".

Here is the implementation in C++:

```cpp
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj(n + 1);
    vector<int> dist(n + 1, -1);
    vector<int> prev(n + 1, -1);

    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    queue<int> q;
    q.push(1);
    dist[1] = 1; // Starting node distance is 1 because we include the start node in the count

    while (!q.empty()) {
        int node = q.front();
        q.pop();

        for (int neighbor : adj[node]) {
            if (dist[neighbor] == -1) { // If the neighbor has not been visited
                dist[neighbor] = dist[node] + 1;
                prev[neighbor] = node;
                q.push(neighbor);

                // If we reached the target node, we can stop early
                if (neighbor == n) {
                    break;
                }
            }
        }
    }

    if (dist[n] == -1) {
        cout << "IMPOSSIBLE" << endl;
    } else {
        cout << dist[n] << endl;
        vector<int> path;
        for (int at = n; at != -1; at = prev[at]) {
            path.push_back(at);
        }
        reverse(path.begin(), path.end());
        for (int node : path) {
            cout << node << " ";
        }
        cout << endl;
    }

    return 0;
}
```

### Explanation:
1. **Input Reading**: The number of computers (\( n \)) and connections (\( m \)) are read, followed by the connections.
2. **Graph Representation**: The adjacency list `adj` is constructed to represent the graph.
3. **BFS Initialization**: The BFS is initialized from node 1. The distance of node 1 is set to 1 (since it is the start node and the problem statement expects the count to include the starting node).
4. **BFS Traversal**: The BFS explores all reachable nodes. For each unvisited neighbor, the distance and predecessor are recorded. If the end node (\( n \)) is reached, the traversal can terminate early.
5. **Path Reconstruction**: If node \( n \) is reached, the path is reconstructed by backtracking from node \( n \) using the `prev` array.
6. **Output**: The number of nodes in the path and the path itself are printed. If node \( n \) is not reachable, "IMPOSSIBLE" is printed.


## Round Trip (DFS)
- https://cses.fi/problemset/task/1669

To solve this problem, we need to find a cycle in an undirected graph. Specifically, we need to find a cycle that involves at least three distinct cities. A common approach to detect cycles in an undirected graph is to use Depth-First Search (DFS). 

### Approach:
1. **Input Reading**: Read the number of cities and roads.
2. **Graph Representation**: Use an adjacency list to represent the graph.
3. **Cycle Detection with DFS**: Use DFS to detect cycles. During the DFS traversal, keep track of the parent node to ensure that we do not consider the immediate parent node as part of the cycle.
4. **Path Reconstruction**: Once a cycle is detected, reconstruct the path from the start node to the end node.
5. **Output**: Print the number of cities in the cycle and the cities themselves in the order they are visited. If no cycle is found, print "IMPOSSIBLE".


```cpp
#include <iostream>
#include <vector>
#include <stack>

using namespace std;

bool dfs(int node, int parent, const vector<vector<int>>& adj, vector<int>& visited, vector<int>& parent_track, int& cycle_start, int& cycle_end) {
    visited[node] = 1; // Mark node as visited
    for (int neighbor : adj[node]) {
        if (neighbor == parent) continue; // Ignore the edge to the parent node
        if (visited[neighbor]) {
            // Cycle found
            cycle_start = neighbor;
            cycle_end = node;
            return true;
        }
        parent_track[neighbor] = node;
        if (dfs(neighbor, node, adj, visited, parent_track, cycle_start, cycle_end)) {
            return true;
        }
    }
    return false;
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    vector<int> visited(n + 1, 0);
    vector<int> parent_track(n + 1, -1);
    int cycle_start = -1, cycle_end = -1;

    for (int i = 1; i <= n; ++i) {
        if (!visited[i]) {
            if (dfs(i, -1, adj, visited, parent_track, cycle_start, cycle_end)) {
                break;
            }
        }
    }

    if (cycle_start == -1) {
        cout << "IMPOSSIBLE" << endl;
    } else {
        vector<int> cycle;
        cycle.push_back(cycle_start);
        for (int v = cycle_end; v != cycle_start; v = parent_track[v]) {
            cycle.push_back(v);
        }
        cycle.push_back(cycle_start);
        reverse(cycle.begin(), cycle.end());

        cout << cycle.size() << endl;
        for (int v : cycle) {
            cout << v << " ";
        }
        cout << endl;
    }

    return 0;
}
```

### Explanation:
1. **Input Reading**: We read the number of cities (\( n \)) and roads (\( m \)), followed by the connections.
2. **Graph Representation**: The adjacency list `adj` is used to represent the graph.
3. **DFS for Cycle Detection**: The `dfs` function traverses the graph to find cycles. The `visited` array keeps track of visited cities, and `parent_track` keeps track of the parent nodes to reconstruct the cycle.
4. **Path Reconstruction**: If a cycle is found, the cycle is reconstructed by backtracking from the end node to the start node using the `parent_track` array.
5. **Output**: The number of cities in the cycle and the cities themselves are printed. If no cycle is found, "IMPOSSIBLE" is printed.

##  Shortest Routes I (Directed Graph, Dijkstra's Algorithm)
- https://cses.fi/problemset/task/1671
To solve this problem of finding the shortest route from Syrjälä (city 1) to every other city in a directed graph, we can use **Dijkstra's algorithm**. This algorithm is well-suited for graphs with non-negative weights, which is the case here since all flight lengths (weights) are positive.

### Approach:
1. **Initialization**: Initialize the distances from city 1 to all other cities as infinity (`inf`) except the start city itself, which is initialized to 0.
2. **Priority Queue**: Use a priority queue to always expand the shortest discovered distance first.
3. **Relaxation**: For each city, update the distances to its neighboring cities if a shorter path is found through the current city.

### Implementation:

```cpp
#include <iostream>
#include <vector>
#include <queue>
#include <tuple>

using namespace std;

const long long INF = LLONG_MAX;

struct Edge {
    int to;
    long long cost;
};

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<Edge>> graph(n + 1);
    for (int i = 0; i < m; ++i) {
        int a, b;
        long long c;
        cin >> a >> b >> c;
        graph[a].push_back({b, c});
    }

    vector<long long> dist(n + 1, INF);
    dist[1] = 0;

    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
    pq.push({0, 1});

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        if (d > dist[u]) continue;

        for (auto& edge : graph[u]) {
            int v = edge.to;
            long long cost = edge.cost;

            if (dist[u] + cost < dist[v]) {
                dist[v] = dist[u] + cost;
                pq.push({dist[v], v});
            }
        }
    }

    for (int i = 1; i <= n; ++i) {
        cout << dist[i] << " ";
    }
    cout << endl;

    return 0;
}
```

### Explanation:
1. **Input Reading**: We read the number of cities `n` and flight connections `m`. For each flight, we store the start city, end city, and flight length in an adjacency list.
2. **Initialization**: We initialize the distance to all cities as `INF`, except for city 1 (Syrjälä), which is initialized to `0`.
3. **Priority Queue**: We use a min-heap (priority queue) to efficiently get the city with the smallest known distance.
4. **Relaxation**: For the current city, we iterate over its neighbors and update their distances if a shorter path is found. Each updated distance is pushed into the priority queue.
5. **Output**: After processing all cities, we print the shortest distances from city 1 to all other cities.

## Shortest Routes II (Directed Graph, Floyd-Warshall Algorithm)
- https://cses.fi/problemset/task/1672
Given the constraints of the problem, the optimal approach to solve the shortest path queries is to use the **Floyd-Warshall algorithm**. This algorithm computes the shortest paths between all pairs of nodes and is suitable for dense graphs with up to 500 nodes.

### Floyd-Warshall Algorithm
The Floyd-Warshall algorithm is a dynamic programming algorithm used for finding the shortest paths between all pairs of vertices in a weighted graph. It works with negative weights as well but assumes no negative cycles.

### Approach:
1. **Initialization**: Initialize a distance matrix `dist` where `dist[i][j]` represents the shortest distance from city `i` to city `j`. Set the distance from each city to itself as 0 and the distances for each direct road as given. Initialize all other distances as infinity (`inf`).
2. **Relaxation**: Update the distance matrix by considering each city as an intermediate point and updating the shortest path using the intermediate city if it provides a shorter path.
3. **Query Processing**: After computing the shortest paths, answer each query by looking up the precomputed shortest paths in the distance matrix.

### Implementation:

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const long long INF = 1e18;

int main() {
    int n, m, q;
    cin >> n >> m >> q;

    vector<vector<long long>> dist(n + 1, vector<long long>(n + 1, INF));

    for (int i = 1; i <= n; ++i) {
        dist[i][i] = 0;
    }

    for (int i = 0; i < m; ++i) {
        int a, b;
        long long c;
        cin >> a >> b >> c;
        dist[a][b] = min(dist[a][b], c);
        dist[b][a] = min(dist[b][a], c);
    }

    // Floyd-Warshall algorithm
    for (int k = 1; k <= n; ++k) {
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (dist[i][k] < INF && dist[k][j] < INF) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }

    for (int i = 0; i < q; ++i) {
        int a, b;
        cin >> a >> b;
        if (dist[a][b] == INF) {
            cout << -1 << endl;
        } else {
            cout << dist[a][b] << endl;
        }
    }

    return 0;
}
```

### Explanation:
1. **Initialization**: We initialize a `dist` matrix of size `(n+1) x (n+1)` with `INF`, setting `dist[i][i] = 0` for all `i`. We then read the roads and update the distances for directly connected cities.
2. **Floyd-Warshall Algorithm**: We run three nested loops over all cities to update the distance matrix considering each city as an intermediate point.
3. **Query Processing**: For each query, we check the precomputed distance in the `dist` matrix. If the distance remains `INF`, it means there is no path between the cities, and we print `-1`. Otherwise, we print the shortest path length.

## Flight Discount (Directed Graph, Dijkstra's Algorithm)
- https://cses.fi/problemset/task/1195

To solve the problem of finding the minimum-price flight route from Syrjälä to Metsälä with one possible discount coupon, we can use a modified version of Dijkstra's algorithm. This version will keep track of the minimum cost to reach each city both with and without using the discount coupon.

### Key Steps:
1. **Initialization**: We maintain two distance arrays:
   - `dist_without`: Minimum cost to reach each city without using the discount.
   - `dist_with`: Minimum cost to reach each city using the discount.
   
2. **Priority Queue**: We use a priority queue to process the nodes in the order of their current minimum cost.

3. **Relaxation**: For each city, we update the distances to its neighbors considering both scenarios (using the discount on the current flight and not using it).

### Implementation:

```cpp
#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <algorithm>
#include <cmath>

using namespace std;

const long long INF = 1e18;

struct Edge {
    int to;
    long long cost;
};

struct State {
    long long cost;
    int node;
    bool used_discount;
    bool operator>(const State &other) const {
        return cost > other.cost;
    }
};

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<Edge>> graph(n + 1);
    for (int i = 0; i < m; ++i) {
        int a, b;
        long long c;
        cin >> a >> b >> c;
        graph[a].push_back({b, c});
    }

    vector<long long> dist_without(n + 1, INF);
    vector<long long> dist_with(n + 1, INF);
    
    priority_queue<State, vector<State>, greater<State>> pq;
    dist_without[1] = 0;
    pq.push({0, 1, false});

    while (!pq.empty()) {
        State curr = pq.top();
        pq.pop();

        long long current_cost = curr.cost;
        int current_node = curr.node;
        bool used_discount = curr.used_discount;

        if (used_discount && current_cost > dist_with[current_node]) continue;
        if (!used_discount && current_cost > dist_without[current_node]) continue;

        for (const Edge &edge : graph[current_node]) {
            int next_node = edge.to;
            long long next_cost = current_cost + edge.cost;

            // Case 1: Not using the discount
            if (!used_discount && next_cost < dist_without[next_node]) {
                dist_without[next_node] = next_cost;
                pq.push({next_cost, next_node, false});
            }

            // Case 2: Using the discount
            long long discounted_cost = current_cost + floor(edge.cost / 2);
            if (!used_discount && discounted_cost < dist_with[next_node]) {
                dist_with[next_node] = discounted_cost;
                pq.push({discounted_cost, next_node, true});
            }

            // Case 3: Already used the discount
            if (used_discount && next_cost < dist_with[next_node]) {
                dist_with[next_node] = next_cost;
                pq.push({next_cost, next_node, true});
            }
        }
    }

    cout << min(dist_without[n], dist_with[n]) << endl;

    return 0;
}
```

### Explanation:
1. **Input Reading**: We read the number of cities `n` and the number of flights `m`. Each flight is described by its start city, end city, and cost. We store these flights in an adjacency list.
2. **Initialization**: We initialize two distance arrays `dist_without` and `dist_with` to infinity (`INF`) and set the starting city's distances to 0 for both cases. We also initialize a priority queue to manage the states.
3. **Priority Queue Processing**: We process the current state, considering whether we have used the discount coupon or not.
4. **Relaxation**: For each neighbor of the current city, we update the distances in both scenarios (with and without using the discount).
5. **Output**: The minimum cost to reach Metsälä is the smaller value between `dist_without[n]` and `dist_with[n]`.


Certainly! To solve this problem by running Dijkstra's algorithm twice (once from the start city and once from the destination city), and then using the results to update the cost of using each edge with the discount, we can follow these steps:

1. **Run Dijkstra's Algorithm** from the start city (Syrjälä) to compute the shortest path to all other cities.
2. **Run Dijkstra's Algorithm** from the destination city (Metsälä) to compute the shortest path from all other cities to the destination.
3. **Evaluate Each Edge** to see if using the discount on that edge would yield a lower cost route from the start to the destination.

Here's the implementation:

```cpp
#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <algorithm>
#include <climits>

using namespace std;

const long long INF = LLONG_MAX;

struct Edge {
    int to;
    long long cost;
};

void dijkstra(int start, vector<long long>& dist, const vector<vector<Edge>>& graph) {
    dist[start] = 0;
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
    pq.push({0, start});
    
    while (!pq.empty()) {
        auto [current_dist, u] = pq.top();
        pq.pop();
        
        if (current_dist > dist[u]) continue;
        
        for (const auto& edge : graph[u]) {
            int v = edge.to;
            long long weight = edge.cost;
            
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    
    vector<vector<Edge>> graph(n + 1);
    vector<tuple<int, int, long long>> edges;

    for (int i = 0; i < m; ++i) {
        int a, b;
        long long c;
        cin >> a >> b >> c;
        graph[a].push_back({b, c});
        edges.push_back({a, b, c});
    }
    
    vector<long long> dist_from_start(n + 1, INF);
    vector<long long> dist_to_end(n + 1, INF);

    dijkstra(1, dist_from_start, graph);
    vector<vector<Edge>> reversed_graph(n + 1);
    for (const auto& [a, b, c] : edges) {
        reversed_graph[b].push_back({a, c});
    }
    dijkstra(n, dist_to_end, reversed_graph);

    long long min_cost = dist_from_start[n];
    
    for (const auto& [a, b, c] : edges) {
        if (dist_from_start[a] < INF && dist_to_end[b] < INF) {
            long long cost_with_discount = dist_from_start[a] + (c / 2) + dist_to_end[b];
            min_cost = min(min_cost, cost_with_discount);
        }
    }

    cout << min_cost << endl;

    return 0;
}
```

## Course Schedule (Topological Sorting)
- https://cses.fi/problemset/task/1679

### Explanation:
1. **Data Structures**:
    - `graph`: Adjacency list representation of the graph for the forward direction.
    - `reversed_graph`: Adjacency list for the graph with reversed edges, used to compute distances to the destination city.
    - `dist_from_start`: Distance array storing the shortest distance from Syrjälä to all other cities.
    - `dist_to_end`: Distance array storing the shortest distance from all other cities to Metsälä.

2. **Dijkstra's Algorithm**:
    - First, we run Dijkstra's algorithm starting from city 1 to compute `dist_from_start`.
    - Next, we reverse the graph and run Dijkstra's algorithm starting from city `n` to compute `dist_to_end`.

3. **Evaluate Each Edge**:
    - For each edge, calculate the potential new cost if we use the discount on that edge.
    - The new potential cost is calculated as the sum of the distance from the start to the source of the edge, half the edge's cost, and the distance from the target of the edge to the destination.
    - Keep track of the minimum possible cost found.

4. **Output**:
    - Print the minimum cost found.


To solve the problem of finding a valid order in which to complete courses given their prerequisites, we can use the concept of **Topological Sorting**. This is a classic problem in graph theory where we need to order the nodes of a directed graph such that for every directed edge \( u \rightarrow v \), node \( u \) comes before \( v \) in the ordering.

### Key Concepts:

1. **Topological Sort**:
   - Topological sorting of a directed graph is a linear ordering of its vertices such that for every directed edge \( u \rightarrow v \), vertex \( u \) comes before \( v \) in the ordering.
   - This can be achieved using Kahn’s Algorithm (BFS-based) or Depth-First Search (DFS-based).

2. **Cycle Detection**:
   - If the graph contains a cycle, it is impossible to complete the courses as per the given prerequisites. Thus, we need to detect cycles.

Given the constraints, Kahn’s Algorithm (BFS-based) is suitable due to its iterative nature and ease of understanding.

### Steps:

1. **Graph Representation**:
   - Use an adjacency list to represent the graph.
   - Maintain an in-degree array to track the number of incoming edges for each node.

2. **Kahn’s Algorithm (BFS-based)**:
   - Initialize a queue with all nodes having in-degree of 0 (i.e., no prerequisites).
   - Process each node, reduce the in-degree of its neighbors, and if any neighbor's in-degree becomes 0, add it to the queue.
   - Collect the nodes in the order they are processed to form the topological sort.

3. **Cycle Detection**:
   - If at the end, the number of processed nodes is less than the total number of nodes, a cycle exists, making it impossible to complete all courses.

### Implementation:

Here is the C++ implementation for finding a valid order or detecting if it's impossible:

```cpp
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

void findCourseOrder(int n, int m, vector<pair<int, int>> &edges) {
    vector<vector<int>> graph(n + 1);
    vector<int> in_degree(n + 1, 0);
    
    // Build the graph and in-degree array
    for (auto edge : edges) {
        int a = edge.first;
        int b = edge.second;
        graph[a].push_back(b);
        in_degree[b]++;
    }
    
    queue<int> q;
    vector<int> order;
    
    // Add all nodes with in-degree 0 to the queue
    for (int i = 1; i <= n; i++) {
        if (in_degree[i] == 0) {
            q.push(i);
        }
    }
    
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        order.push_back(node);
        
        for (int neighbor : graph[node]) {
            in_degree[neighbor]--;
            if (in_degree[neighbor] == 0) {
                q.push(neighbor);
            }
        }
    }
    
    // If we processed all nodes, we have a valid topological order
    if (order.size() == n) {
        for (int course : order) {
            cout << course << " ";
        }
        cout << endl;
    } else {
        cout << "IMPOSSIBLE" << endl;
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> edges(m);
    
    for (int i = 0; i < m; i++) {
        cin >> edges[i].first >> edges[i].second;
    }
    
    findCourseOrder(n, m, edges);
    
    return 0;
}
```

### Explanation:

1. **Graph Representation**:
   - The graph is represented using an adjacency list where `graph[a]` contains all nodes `b` such that there is an edge \( a \rightarrow b \).

2. **In-degree Array**:
   - The in-degree array tracks the number of prerequisites for each course.

3. **BFS-based Topological Sort (Kahn’s Algorithm)**:
   - We initialize a queue with all courses having no prerequisites (in-degree 0).
   - Process each course by reducing the in-degree of its neighbors and adding them to the queue if their in-degree becomes 0.
   - Collect the courses in the order they are processed.

4. **Cycle Detection**:
   - If we process fewer courses than the total number, it indicates the presence of a cycle, making it impossible to complete all courses.

This approach ensures that we find a valid order to complete the courses or detect if it's impossible due to cyclic dependencies.

## Longest Flight Route (DAG)
- https://cses.fi/problemset/task/1680

To solve this problem, we need to find the longest path from city 1 (Syrjälä) to city n (Lehmälä) in a Directed Acyclic Graph (DAG). Since there are no cycles in the flight network, we can leverage the properties of DAGs and use dynamic programming combined with topological sorting to achieve this efficiently.

### Approach:

1. **Topological Sorting**:
   - Perform a topological sort of the graph. This allows us to process the nodes in a linear order such that for any directed edge \( u \rightarrow v \), \( u \) comes before \( v \).

2. **Dynamic Programming**:
   - Use a dynamic programming array `dp` where `dp[i]` stores the maximum number of cities that can be visited starting from city 1 to city `i`.
   - Use a `parent` array to keep track of the path taken to reconstruct the route at the end.

3. **Processing Nodes**:
   - Iterate over the nodes in the order given by the topological sort. For each node, update the `dp` values of its adjacent nodes.

4. **Path Reconstruction**:
   - After processing all nodes, reconstruct the path from city 1 to city n using the `parent` array.

### Implementation:

Here is the C++ implementation:

```cpp
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <queue>

using namespace std;

void findLongestPath(int n, int m, vector<pair<int, int>>& edges) {
    vector<vector<int>> adj(n + 1);
    vector<int> indegree(n + 1, 0);

    // Build the adjacency list and calculate indegrees
    for (auto edge : edges) {
        int a = edge.first, b = edge.second;
        adj[a].push_back(b);
        indegree[b]++;
    }

    // Topological sort using Kahn's algorithm
    queue<int> q;
    for (int i = 1; i <= n; i++) {
        if (indegree[i] == 0) {
            q.push(i);
        }
    }

    vector<int> topo_order;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        topo_order.push_back(u);

        for (int v : adj[u]) {
            indegree[v]--;
            if (indegree[v] == 0) {
                q.push(v);
            }
        }
    }

    // Initialize the dp and parent arrays
    vector<int> dp(n + 1, -1);
    vector<int> parent(n + 1, -1);
    dp[1] = 1;

    // Process nodes in topological order
    for (int u : topo_order) {
        if (dp[u] != -1) {
            for (int v : adj[u]) {
                if (dp[u] + 1 > dp[v]) {
                    dp[v] = dp[u] + 1;
                    parent[v] = u;
                }
            }
        }
    }

    // If there's no path to the last city
    if (dp[n] == -1) {
        cout << "IMPOSSIBLE" << endl;
        return;
    }

    // Reconstruct the path from Syrjälä to Lehmälä
    vector<int> path;
    for (int u = n; u != -1; u = parent[u]) {
        path.push_back(u);
    }
    reverse(path.begin(), path.end());

    // Output the result
    cout << dp[n] << endl;
    for (int city : path) {
        cout << city << " ";
    }
    cout << endl;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> edges(m);
    for (int i = 0; i < m; i++) {
        cin >> edges[i].first >> edges[i].second;
    }
    findLongestPath(n, m, edges);
    return 0;
}
```

### Explanation:

1. **Graph Representation**:
   - We represent the graph using an adjacency list.
   - We also maintain an array to keep track of the in-degrees of nodes.

2. **Topological Sort**:
   - Using Kahn's algorithm, we perform a topological sort to process nodes in the correct order.

3. **Dynamic Programming**:
   - We use a `dp` array to store the maximum number of cities that can be visited starting from city 1 to each city.
   - We use a `parent` array to reconstruct the path later.

4. **Processing and Path Reconstruction**:
   - We iterate over the nodes in the topological order and update the `dp` values and `parent` pointers accordingly.
   - Finally, we reconstruct the path from city 1 to city n using the `parent` array and output the result.

## Game Routes (DAG)
- https://cses.fi/problemset/task/1681
To solve the problem of finding the number of distinct ways to reach level \( n \) from level \( 1 \) in a directed acyclic graph (DAG), we can utilize dynamic programming combined with topological sorting. Here's a step-by-step approach:

### Approach:

1. **Graph Representation**:
   - Represent the graph using an adjacency list.

2. **Topological Sorting**:
   - Perform a topological sort of the graph. This allows us to process the nodes in a linear order such that for any directed edge \( u \rightarrow v \), \( u \) comes before \( v \).

3. **Dynamic Programming**:
   - Use a dynamic programming array `dp` where `dp[i]` stores the number of distinct ways to reach level \( i \) from level 1.
   - Initialize `dp[1] = 1` since there is one way to be at the starting level 1 (just start there).

4. **Process Nodes**:
   - Iterate over the nodes in the order given by the topological sort. For each node, update the `dp` values of its adjacent nodes.

### Implementation:

Here is the C++ implementation:

```cpp
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int MOD = 1e9 + 7;

void findWays(int n, int m, vector<pair<int, int>>& edges) {
    vector<vector<int>> adj(n + 1);
    vector<int> indegree(n + 1, 0);

    // Build the adjacency list and calculate indegrees
    for (auto edge : edges) {
        int a = edge.first, b = edge.second;
        adj[a].push_back(b);
        indegree[b]++;
    }

    // Topological sort using Kahn's algorithm
    queue<int> q;
    for (int i = 1; i <= n; i++) {
        if (indegree[i] == 0) {
            q.push(i);
        }
    }

    vector<int> topo_order;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        topo_order.push_back(u);

        for (int v : adj[u]) {
            indegree[v]--;
            if (indegree[v] == 0) {
                q.push(v);
            }
        }
    }

    // Initialize the dp array
    vector<int> dp(n + 1, 0);
    dp[1] = 1;

    // Process nodes in topological order
    for (int u : topo_order) {
        for (int v : adj[u]) {
            dp[v] = (dp[v] + dp[u]) % MOD;
        }
    }

    // Output the number of ways to reach level n
    cout << dp[n] << endl;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> edges(m);
    for (int i = 0; i < m; i++) {
        cin >> edges[i].first >> edges[i].second;
    }
    findWays(n, m, edges);
    return 0;
}
```

### Explanation:

1. **Graph Representation**:
   - We store the graph in an adjacency list `adj` and maintain an indegree array to keep track of the number of incoming edges for each node.

2. **Topological Sort**:
   - Using Kahn's algorithm, we perform a topological sort. Nodes with zero indegree are added to the queue, and we process each node by reducing the indegree of its neighbors. If a neighbor's indegree drops to zero, it's added to the queue.

3. **Dynamic Programming**:
   - We initialize `dp[1] = 1` since there's only one way to start at level 1.
   - We iterate over each node in the topological order. For each node \( u \), we update its neighbors \( v \) by adding the number of ways to reach \( u \) (`dp[u]`) to the number of ways to reach \( v \) (`dp[v]`).

4. **Output**:
   - Finally, the value `dp[n]` gives the number of distinct ways to reach level \( n \) from level 1.

## Planets Queries I (sparse table)
- https://cses.fi/problemset/task/1750

```cpp
#include <iostream>
#include <vector>
using namespace std;

const int MAX_L = 60; // 2^60 is larger than 10^18, suffices for k <= 10^9
const int MOD = 1e9+7;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, q;
    cin >> n >> q;
    
    vector<int> teleports(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> teleports[i];
    }
    
    vector<vector<int>> lift(n + 1, vector<int>(MAX_L));
    
    // Initialize the lift table
    for (int i = 1; i <= n; ++i) {
        lift[i][0] = teleports[i];
    }
    
    // Fill the table
    for (int j = 1; j < MAX_L; ++j) {
        for (int i = 1; i <= n; ++i) {
            lift[i][j] = lift[lift[i][j-1]][j-1];
        }
    }
    
    while (q--) {
        int x, k;
        cin >> x >> k;
        int current = x;
        
        for (int j = 0; j < MAX_L; ++j) {
            if (k & (1LL << j)) {
                current = lift[current][j];
            }
        }
        
        cout << current << "\n";
    }
    
    return 0;
}
```

### Explanation of the C++ Code:

1. **Input Reading**:
   - The program reads `n` (number of planets) and `q` (number of queries).
   - The teleporter destinations are stored in a vector `teleports`.

2. **Binary Lifting Table Initialization**:
   - `lift[i][0]` is set to the destination of the teleporter from planet `i`.

3. **Filling the Table**:
   - The table is filled for powers of 2 up to `2^60` using a nested loop.
   - Each entry `lift[i][j]` represents the planet reached after `2^j` teleports starting from planet `i`.

4. **Processing Queries**:
   - For each query, the starting planet `x` and the number of teleports `k` are read.
   - The number of teleports `k` is decomposed into its binary form.
   - The destination planet is determined by combining the results from the precomputed table using the relevant bits of `k`.

## Road Reparation
- https://cses.fi/problemset/task/1675

To solve the problem of finding the minimum reparation cost to ensure that all cities are connected, we need to construct a Minimum Spanning Tree (MST) from the given graph. The MST will help us connect all cities with the minimum total cost.

### Approach

1. **Model the Problem as a Graph**:
   - Cities are nodes.
   - Roads are edges with weights representing the reparation costs.

2. **Use Kruskal’s Algorithm**:
   - **Step 1**: Sort all the edges based on their weights (reparation costs).
   - **Step 2**: Use a Union-Find (Disjoint Set Union, DSU) structure to add edges to the MST while ensuring no cycles are formed.

3. **Check Connectivity**:
   - If the number of edges included in the MST is less than \(n - 1\), the graph is not fully connected, and thus, it’s impossible to connect all cities.

### Detailed Steps

1. **Parse Input**: Read the number of cities and roads, followed by the road details.
2. **Sort Edges**: Sort the edges based on the reparation costs.
3. **Union-Find Structure**:
   - Initialize with each city as its own parent.
   - Use path compression and union by rank to efficiently manage the connections.
4. **Construct MST**:
   - Add edges to the MST in the order of their costs, ensuring no cycles are created.
5. **Output**:
   - If all cities are connected, print the total cost of the MST.
   - If not all cities can be connected, print "IMPOSSIBLE".

Here is the C++ code implementing this approach using Kruskal’s algorithm:

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Edge {
    int u, v, cost;
    bool operator<(const Edge& other) const {
        return cost < other.cost;
    }
};

vector<int> parent, rank;

int find(int x) {
    if (parent[x] != x)
        parent[x] = find(parent[x]);
    return parent[x];
}

void unionSet(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);

    if (rootX != rootY) {
        if (rank[rootX] > rank[rootY]) {
            parent[rootY] = rootX;
        } else if (rank[rootX] < rank[rootY]) {
            parent[rootX] = rootY;
        } else {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<Edge> edges(m);
    for (int i = 0; i < m; ++i) {
        cin >> edges[i].u >> edges[i].v >> edges[i].cost;
        --edges[i].u;
        --edges[i].v;
    }

    sort(edges.begin(), edges.end());

    parent.resize(n);
    rank.resize(n, 0);
    for (int i = 0; i < n; ++i) {
        parent[i] = i;
    }

    long long totalCost = 0;
    int edgeCount = 0;

    for (const Edge& e : edges) {
        int rootU = find(e.u);
        int rootV = find(e.v);

        if (rootU != rootV) {
            unionSet(rootU, rootV);
            totalCost += e.cost;
            edgeCount++;
        }

        if (edgeCount == n - 1) {
            break;
        }
    }

    if (edgeCount == n - 1) {
        cout << totalCost << "\n";
    } else {
        cout << "IMPOSSIBLE\n";
    }

    return 0;
}
```

### Explanation of the Code

1. **Edge Structure**:
   - Holds information about each edge: its endpoints and cost.

2. **Union-Find Functions**:
   - `find`: Finds the root of a set and applies path compression.
   - `unionSet`: Merges two sets and uses union by rank.

3. **Main Function**:
   - Reads input and initializes the Union-Find structure.
   - Sorts edges and processes them to build the MST while keeping track of the total cost.
   - Checks if a valid MST is constructed and prints the result.

## Planets and Kingdoms
- https://cses.fi/problemset/task/1682

To solve the problem of determining the kingdoms in the game, where a kingdom is defined by strongly connected components (SCCs) in a directed graph, we need to identify SCCs. Each SCC is a maximal subgraph where every vertex is reachable from every other vertex in the same SCC.

Here’s a step-by-step approach using Kosaraju’s algorithm, which is efficient for finding SCCs in \(O(n + m)\) time complexity.

### Steps Using Kosaraju’s Algorithm

1. **Perform a DFS to Determine Finish Times**:
   - Traverse the graph and record the finishing times of each vertex.
   
2. **Reverse the Graph**:
   - Reverse the direction of all edges in the graph.

3. **Perform DFS on the Reversed Graph**:
   - Process nodes in the order of decreasing finish times from the first DFS. Each DFS tree in the reversed graph represents an SCC.

4. **Assign Kingdom Labels**:
   - Each SCC corresponds to a unique kingdom.

### C++ Implementation

Here’s a C++ implementation of the above approach:

```cpp
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

const int MAXN = 100000;
vector<int> graph[MAXN], reverseGraph[MAXN];
vector<int> scc[MAXN];
bool visited[MAXN];
stack<int> nodesStack;
int component[MAXN];
int n, m;

void dfs1(int u) {
    visited[u] = true;
    for (int v : graph[u]) {
        if (!visited[v]) {
            dfs1(v);
        }
    }
    nodesStack.push(u);
}

void dfs2(int u, int comp) {
    visited[u] = true;
    component[u] = comp;
    scc[comp].push_back(u);
    for (int v : reverseGraph[u]) {
        if (!visited[v]) {
            dfs2(v, comp);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;

    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        --a; --b; // Convert to 0-based indexing
        graph[a].push_back(b);
        reverseGraph[b].push_back(a);
    }

    // Step 1: Perform DFS to get finishing times
    fill(visited, visited + n, false);
    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            dfs1(i);
        }
    }

    // Step 2: Reverse DFS using finish times to find SCCs
    fill(visited, visited + n, false);
    int compCount = 0;
    while (!nodesStack.empty()) {
        int u = nodesStack.top();
        nodesStack.pop();
        if (!visited[u]) {
            dfs2(u, compCount++);
        }
    }

    // Output results
    cout << compCount << endl;
    for (int i = 0; i < n; ++i) {
        cout << component[i] + 1 << " "; // Convert back to 1-based indexing
    }
    cout << endl;

    return 0;
}
```

### Explanation:

1. **Graph and Reverse Graph Construction**:
   - Read input and build the graph and its reversed version.

2. **First DFS**:
   - Traverse the original graph to determine the finishing times of nodes.

3. **Reverse DFS**:
   - Using the reversed graph, perform DFS in the order of decreasing finish times to discover SCCs.

4. **Output**:
   - Print the number of SCCs (kingdoms) and the kingdom label for each planet.

### Complexity:
- **Time Complexity**: \(O(n + m)\) due to the two DFS traversals.
- **Space Complexity**: \(O(n + m)\) for storing the graph and auxiliary data structures.

This approach ensures that we efficiently determine the number of kingdoms and assign labels to each planet according to their respective kingdoms.

Tarjan's algorithm is another efficient method for finding Strongly Connected Components (SCCs) in a directed graph. It operates in \(O(n + m)\) time complexity, making it suitable for large graphs. The algorithm uses a single DFS traversal and maintains indices and low-link values to determine SCCs.

Here is a C++ implementation of Tarjan's algorithm to solve the problem:

### C++ Code for Tarjan's Algorithm

```cpp
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

const int MAXN = 100000;
vector<int> graph[MAXN];
vector<int> scc[MAXN];
bool inStack[MAXN];
int index[MAXN], lowlink[MAXN], component[MAXN];
stack<int> nodeStack;
int indexCounter = 0, sccCount = 0;
int n, m;

void tarjan(int u) {
    index[u] = lowlink[u] = indexCounter++;
    nodeStack.push(u);
    inStack[u] = true;

    for (int v : graph[u]) {
        if (index[v] == -1) {
            // v has not been visited
            tarjan(v);
            lowlink[u] = min(lowlink[u], lowlink[v]);
        } else if (inStack[v]) {
            // v is in the stack (part of the current SCC)
            lowlink[u] = min(lowlink[u], index[v]);
        }
    }

    // If u is a root node, pop the stack and generate an SCC
    if (lowlink[u] == index[u]) {
        vector<int> currentSCC;
        int v;
        do {
            v = nodeStack.top();
            nodeStack.pop();
            inStack[v] = false;
            component[v] = sccCount;
            currentSCC.push_back(v);
        } while (v != u);
        scc[sccCount++] = currentSCC;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;

    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        --a; --b; // Convert to 0-based indexing
        graph[a].push_back(b);
    }

    fill(index, index + n, -1); // Initialize all indices to -1
    fill(lowlink, lowlink + n, -1); // Initialize all lowlink values to -1

    for (int i = 0; i < n; ++i) {
        if (index[i] == -1) {
            tarjan(i);
        }
    }

    // Output results
    cout << sccCount << endl;
    for (int i = 0; i < n; ++i) {
        cout << component[i] + 1 << " "; // Convert back to 1-based indexing
    }
    cout << endl;

    return 0;
}
```

### Explanation

1. **Initialization**:
   - **Graph Representation**: Read the graph and construct adjacency lists.
   - **Arrays**: Initialize `index` and `lowlink` arrays to `-1`, and use a stack to keep track of nodes in the current SCC.
   - **`inStack`**: A boolean array to check if a node is currently in the stack.

2. **Tarjan's Algorithm**:
   - **DFS Traversal**: For each unvisited node, perform a DFS to assign `index` and `lowlink` values.
   - **Stack Operations**: If a node `u` is the root of an SCC (i.e., `lowlink[u] == index[u]`), pop nodes from the stack until `u` is reached, forming one SCC.

3. **Output**:
   - **SCC Count**: The number of SCCs found.
   - **Component Labels**: Each node is assigned a kingdom label based on its SCC.

### Complexity:
- **Time Complexity**: \(O(n + m)\) because each node and edge is processed once.
- **Space Complexity**: \(O(n + m)\) for storing graph structures and auxiliary data.

Tarjan's algorithm is well-suited for problems involving the detection of SCCs and is particularly effective for large-scale graphs due to its efficiency.