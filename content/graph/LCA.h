#pragma once

/**
 * Author: Unknown
 * Date: 2002-09-13
 * Source: predates tinyKACTL
 * Description: Lowest Common Ancestor (LCA) using Binary Lifting.
 * Preprocesses a rooted tree to store the 2 to the i-th ancestor of every vertex
 * along with its depth. Supports finding the k-th ancestor of a vertex and
 * finding the lowest common ancestor of any two vertices.
 * The implementation assumes the graph is a tree and uses DFS to build
 * the ancestor table. LOG must be large enough to represent the maximum
 * possible tree depth.
 * Time: O(|V| log |V|) preprocessing, O(log |V|) per query
 * Memory: O(|V| log |V|)
 * Status: stress-tested
 */

// int N , LOG;
// int up[N][LOG];
// int depth[N];

vector<vector<int>> adjList;

void dfs(int u, int p, int d){
    depth[u] = d;

    up[u][0] = p;
    for (size_t i = 1; i < LOG; i++)
    {
        if (up[u][i - 1] != -1) {
            up[u][i] = up[ up[u][i - 1] ][i - 1];
        }
    }

    for(auto next : adjList[u]){
        if(next == p) continue;

        dfs(next, u, d + 1);
    }
}

int kth(int u, int p){
    if(depth[u] < p){
        return -1;
    }
    
    for (size_t i = 0; i < LOG; i++)
    {
        if(p & (1 << i)){
            u = up[u][i];
        }
    }
    return u;
}

int lca(int a, int b){
    if(depth[a] > depth[b]){
        swap(a, b);
    }

    b = kth(b, depth[b] - depth[a]);

    if(a == b) return a;

    for (int i = LOG - 1; i >= 0; i--)
    {
        if(up[a][i] != up[b][i]){
            a = up[a][i];
            b = up[b][i];
        }
    }
    return up[a][0];
}