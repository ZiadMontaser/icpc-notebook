/**
 * Author: Unknown
 * Date: 2002-09-13
 * Source: predates tinyKACTL
 * Description: Depth-First Search (DFS) with vertex entry and exit times.
 * Assigns each vertex an entry time when DFS first visits it and an exit time
 * after all of its reachable descendants have been processed.
 * Uses three colors to represent the DFS state: unvisited, currently active,
 * and fully processed. The entry and exit times can be used to determine
 * ancestor relationships and are useful in algorithms such as cycle detection
 * and topological sorting.
 * For a graph with multiple connected components, DFS should be started from
 * every unvisited vertex.
 * Time: O(|V| + |E|)
 * Memory: O(|V|)
 * Status: stress-tested
 */

 vector<vector<int>> adj; // graph represented as an adjacency list
int n; // number of vertices

vector<int> color;

vector<int> time_in, time_out;
int dfs_timer = 0;

void dfs(int v) {
    time_in[v] = dfs_timer++;
    color[v] = 1;
    for (int u : adj[v])
        if (color[u] == 0)
            dfs(u);
    color[v] = 2;
    time_out[v] = dfs_timer++;
}