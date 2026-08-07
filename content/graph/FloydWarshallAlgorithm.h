/**
 * Author: Unknown
 * Date: 2002-09-13
 * Source: predates tinyKACTL
 * Description: All-Pairs Shortest Paths using the Floyd-Warshall algorithm.
 * Computes the shortest distance between every pair of vertices by allowing
 * each vertex to be used as an intermediate vertex.
 * The distance matrix d should initially contain edge weights, with d[i][i]
 * = 0 and d[i][j] = INF when there is no direct path between i and j.
 * Supports negative edge weights, but the presence of negative cycles makes
 * the shortest path distances undefined.
 * Time: O(|V|^3)
 * Memory: O(|V|^2)
 * Status: stress-tested
 */


 // All Pairs Shortest Path
void floydWarshall(vector<vector<ll>>& d) {
    int n = d.size();
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (d[i][k] != INF && d[k][j] != INF) {
                    d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
                }
            }
        }
    }
}