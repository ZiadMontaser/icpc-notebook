/**
 * Author: Unknown
 * Date: 2002-09-13
 * Source: predates tinyKACTL
 * Description: Dijkstra's algorithm for finding the shortest paths from a
 * single source vertex to all other vertices in a weighted graph.
 * Uses a min-heap priority queue to repeatedly process the vertex with the
 * smallest known distance and relax its outgoing edges.
 * Requires all edge weights to be non-negative.
 * Unreachable vertices retain a distance of INF.
 * Time: O((|V| + |E|) log |V|)
 * Memory: O(|V| + |E|)
 * Status: stress-tested
 */
#pragma once

typedef long long ll;
const ll INF = 1e18;
vector<vector<pair<int, ll>>> adj;

vector<ll> dijkstra(int n, int src) {
    vector<ll> dist(n, INF); // distance array
    dist[src] = 0;

    // Min-heap: {distance, node}
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<>> pq;
    pq.push({0, src});

    while (!pq.empty()) {
        auto [currentDist, u] = pq.top();
        pq.pop();

        // Skip if this is not the best distance anymore
        if (currentDist > dist[u]) continue;

        // Traverse neighbors
        for (auto &[v, weight] : adj[u]) {
            // Relaxation step
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }

    return dist;
}