/**
 * Author: Unknown
 * Date: 2002-09-13
 * Source: predates tinyKACTL
 * Description: Breadth-First Search (BFS) on an unweighted graph.
 * Computes the shortest distance from a source vertex to every reachable
 * vertex by exploring the graph level by level.
 * Also stores the parent of each vertex, allowing the shortest path from
 * the source to any reachable vertex to be reconstructed.
 * Vertices that are unreachable from the source retain a distance of -1.
 * Works for both directed and undirected graphs depending on the adjacency
 * list provided.
 * Time: O(|V| + |E|)
 * Memory: O(|V|)
 * Status: stress-tested
 */

vector<int> bfs(const vector<vector<int>>& adj, int src,
                vector<int>& parent) {
    int n = adj.size();

    vector<int> dist(n, -1);
    parent.assign(n, -1);

    if (src < 0 || src >= n)
        return dist;

    queue<int> q;

    dist[src] = 0;
    q.push(src);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v : adj[u]) {
            // Already visited
            if (dist[v] != -1)
                continue;

            dist[v] = dist[u] + 1;
            parent[v] = u;

            q.push(v);
        }
    }

    return dist;
}


vector<int> get_path(int src, int target,
                     const vector<int>& parent,
                     const vector<int>& dist) {
    if (target < 0 || target >= (int)parent.size())
        return {};

    if (dist[target] == -1)
        return {};

    vector<int> path;

    for (int v = target; v != -1; v = parent[v])
        path.push_back(v);

    reverse(path.begin(), path.end());

    if (path.empty() || path.front() != src)
        return {};

    return path;
}