/**
 * Author: Unknown
 * Date: 2002-09-13
 * Source: predates tinyKACTL
 * Description: Euler Tour / DFS Flattening of a tree.
 * Assigns each vertex a contiguous interval [tin[u], tout[u]] such that
 * the entire subtree of u appears consecutively in the flattened array.
 * tin[u] stores the position where the subtree of u starts, while tout[u]
 * stores the position where the subtree ends.
 * The flattened array can be used to transform subtree queries on a tree
 * into range queries over a one-dimensional array.
 * Requires the input graph to be a tree and a valid root to be chosen
 * before calling DFS.
 * Time: O(|V|)
 * Memory: O(|V|)
 * Status: stress-tested
 */

 // subtree of node u is flat -> [tin[u] : tout[u]]
vector<int> adj[N];
int tin[N], tout[N], flat[N];
int timer = 0;

void dfs(int u, int parent) {
    tin[u] = timer;
    flat[timer] = u;
    timer++;

    for (auto v : adj[u]) {
        if (v == parent) continue;
        dfs(v, u);
    }

    tout[u] = timer - 1;
}