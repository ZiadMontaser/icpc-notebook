/**
 * Author: Unknown
 * Date: 2002-09-13
 * Source: predates tinyKACTL
 * Description: Multi-source BFS on a 2D grid.
 * Computes the shortest Manhattan distance from every cell to its nearest
 * source cell by initializing the BFS queue with all sources simultaneously.
 * Each move is allowed in the four cardinal directions and has unit cost.
 * Unreachable cells retain a distance of INF.
 * Time: O(|V| + |E|) = O(n * m)
 * Memory: O(n * m)
 * Status: stress-tested
 */


int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};

vector<vector<int>> multi_source_bfs_grid(vector<vector<int>>& grid,
                                          vector<pair<int,int>> sources) {
    int n = grid.size();
    int m = grid[0].size();

    vector<vector<int>> dist(n, vector<int>(m, INF));
    queue<pair<int,int>> q;

    // initialize sources
    for (auto [x, y] : sources) {
        dist[x][y] = 0;
        q.push({x, y});
    }

    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();

        for (int d = 0; d < 4; d++) {
            int nx = x + dx[d];
            int ny = y + dy[d];

            if (nx >= 0 && nx < n && ny >= 0 && ny < m) {
                if (dist[nx][ny] > dist[x][y] + 1) {
                    dist[nx][ny] = dist[x][y] + 1;
                    q.push({nx, ny});
                }
            }
        }
    }

    return dist;
}




const int INF = 1e9;

vector<int> multi_source_bfs(int n, vector<vector<int>>& adj, vector<int>& sources) {
    vector<int> dist(n, INF);
    queue<int> q;

    // initialize all sources
    for (int src : sources) {
        dist[src] = 0;
        q.push(src);
    }

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v : adj[u]) {
            if (dist[v] > dist[u] + 1) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }

    return dist;



