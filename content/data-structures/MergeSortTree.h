/**
 * Author: Unknown
 * Date: Unknown
 * Source: custom
 * Description: Merge Sort Tree. Answers 2D range queries online.
 *  Default implementation returns the number of elements strictly less than x in half-open range $[l, r)$.
 *  To change the query condition, replace the \texttt{lower\_bound} call in \texttt{less()} based on this cheat sheet:
 *  1. Strictly Greater than x: \texttt{v.end() - upper\_bound(all(v), x)}
 *  2. Greater than or Equal to x: \texttt{v.end() - lower\_bound(all(v), x)}
 *  3. Strictly Less than x: \texttt{lower\_bound(all(v), x) - v.begin()}
 *  4. Less than or Equal to x: \texttt{upper\_bound(all(v), x) - v.begin()}
 *  5. Equal to x: \texttt{upper\_bound(all(v), x) - lower\_bound(all(v), x)}
 *  6. Not Equal to x: \texttt{sz(v) - (upper\_bound(all(v), x) - lower\_bound(all(v), x))}
 * Time: $O(N \log N)$ to build, $O(\log^2 N)$ per query.
 * Status: untested
 */
#pragma once
struct SegTree {
    int tree_size;
    vector<vector<int>> SegData;
    SegTree(int n) {
        tree_size = 1;
        while (tree_size < n) tree_size <<= 1;
        SegData.assign(2 * tree_size, {});
    }

    vector<int> merge(const vector<int> & lf, const vector<int> & ri) {
        int n = lf.size(), m = ri.size();
        vector<int> ans(n + m);

        int i = 0, j = 0, k = 0;
        while (i < n && j < m) {
            if(lf[i] < ri[j])
                ans[k++] = lf[i++];
            else
                ans[k++] = ri[j++];
        }

        while (i < n)
            ans[k++] = lf[i++];
        while (j < m)
            ans[k++] = ri[j++];

        return ans;
    }

    void build(const vector<int> & arr, int node, int lx, int rx) {
        if(rx - lx == 1) {
            if(lx < arr.size())
                SegData[node] = {arr[lx]};
            return;
        }

        int mid = (lx + rx) / 2;
        build(arr, 2 * node + 1, lx, mid);
        build(arr, 2 * node + 2, mid, rx);

        SegData[node] = merge(SegData[2 * node + 1], SegData[2 * node + 2]);
    }
    void build(const vector<int> & arr) {
        build(arr, 0, 0, tree_size);
    }


    int less(int l, int r, int x, int node, int lx, int rx) {
        if(lx >= r || rx <= l)
            return 0;
        if(lx >= l && rx <= r) {
            return lower_bound(SegData[node].begin(), SegData[node].end(), x) - SegData[node].begin();
            // greater -> return SegData[node].end() - upper_bound(SegData[node].begin(), SegData[node].end(), x);
        }

        int mid = (lx + rx) / 2;
        int lf = less(l, r, x, 2 * node + 1, lx, mid);
        int ri = less(l, r, x, 2 * node + 2, mid, rx);
        return lf + ri;
    }

    int less(int l, int r, int x) {
        return less(l, r, x, 0, 0, tree_size);
    }
};