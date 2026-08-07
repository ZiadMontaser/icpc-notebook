/**
 * Author: Unknown
 * Date: 2002-09-13
 * Source: predates tinyKACTL
 * Description: Topological sorting of a directed graph using DFS.
 *  Produces an ordering of all vertices such that for every directed edge
 *  u -> v, u appears before v in the ordering, provided the graph is acyclic.
 *  Vertices are added to the result after all their outgoing neighbors have
 *  been processed, then the resulting list is reversed.
 *  This implementation does not explicitly detect cycles. For graphs
 *  containing cycles, the returned ordering is not guaranteed to be valid.
 * Time: O(|V| + |E|)
 * Memory: O(|V|)
 * Status: stress-tested
 */
#pragma once
int n; // number of vertices
vector<vector<int>> adj; // adjacency list of graph
vector<bool> visited;
vector<int> ans;

void dfs(int v) {
    visited[v] = true;
    for (int u : adj[v]) {
        if (!visited[u]) {
            dfs(u);
        }
    }
    ans.push_back(v);
}

void topological_sort() {
    visited.assign(n, false);
    ans.clear();
    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            dfs(i);
        }
    }
    reverse(ans.begin(), ans.end());
}
