
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
