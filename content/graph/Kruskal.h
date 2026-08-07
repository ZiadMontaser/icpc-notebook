
/**
 * Author: Unknown
 * Date: 2002-09-13
 * Source: predates tinyKACTL
 * Description: Minimum Spanning Tree using Kruskal's algorithm.
 * Sorts all edges by increasing weight and greedily adds an edge whenever
 * its endpoints belong to different connected components.
 * Uses a Disjoint Set Union structure with path compression and union by
 * rank to efficiently detect and merge connected components.
 * If the graph is connected, the result contains a minimum spanning tree.
 * For a disconnected graph, the result is a minimum spanning forest.
 * Time: O(|E| log |E|)
 * Memory: O(|V| + |E|)
 * Status: stress-tested
 */
#pragma once

vector<int> parent, rank;

// Initialize a set with a single element (self parent)
void make_set(int v) {
    parent[v] = v;     // each node is its own parent initially
    rank[v] = 0;       // rank (tree height approximation) starts at 0
}

// Find the representative (root) of the set with path compression
int find_set(int v) {
    if (v == parent[v])
        return v;
    // Path compression: flatten the tree for faster future queries
    return parent[v] = find_set(parent[v]);
}

// Union two sets by rank (attach smaller tree under larger tree)
void union_sets(int a, int b) {
    a = find_set(a);   // find root of a
    b = find_set(b);   // find root of b

    if (a != b) {      // only merge if they are in different sets
        // Ensure that 'a' has higher rank
        if (rank[a] < rank[b])
            swap(a, b);

        parent[b] = a; // attach tree b under root a

        // If both have same rank, increase rank of new root
        if (rank[a] == rank[b])
            rank[a]++;
    }
}

// Edge structure for graph
struct Edge {
    int u, v, weight;

    // Comparator to sort edges by weight (ascending)
    bool operator<(Edge const& other) {
        return weight < other.weight;
    }
};

int n;                  // number of vertices
vector<Edge> edges;     // list of all edges

int cost = 0;           // total cost of MST
vector<Edge> result;    // edges included in MST

parent.resize(n);
rank.resize(n);
for (int i = 0; i < n; i++)
    make_set(i);


sort(edges.begin(), edges.end());

// Iterate over edges in increasing order of weight
for (Edge e : edges) {
    // If adding this edge doesn't form a cycle
    if (find_set(e.u) != find_set(e.v)) {
        cost += e.weight;        // include edge weight in MST cost
        result.push_back(e);     // store edge in MST
        union_sets(e.u, e.v);    // merge the components
    }
}