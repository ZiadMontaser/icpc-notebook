/**
 * Author: Unknown
 * Date: Unknown
 * Source: custom
 * Description: Zero-indexed array-based Segment Tree. Bounds are inclusive to the left and exclusive to the right $[l, r)$.
 *  Computes range sum by default. Can be changed by modifying the `Node` struct and `merge` function.
 * Time: $O(\log N)$ for queries and updates, $O(N)$ to build.
 * Usage: SegTree st(sz(v)); st.build(v); st.set(idx, val); st.get_range(l, r);
 * Status: untested
 */
#pragma once

struct Node {
    long long sum;
    Node() : sum(0){}
    Node(int x) : sum(x){}
};

struct SegTree {
    int tree_size;
    vector<Node> SegData;
    SegTree(int n) {
        tree_size = 1;
        while (tree_size < n) tree_size <<= 1;
        SegData.assign(2 * tree_size, Node());
    }

    Node merge(const Node & lf, const Node & ri) {
        Node ans = Node();
        ans.sum = lf.sum + ri.sum;
        return ans;
    }

    void build(const vector<int> & arr, int node, int lx, int rx) {
        if(rx - lx == 1) {
            if(lx < arr.size())
                SegData[node] = Node(arr[lx]);
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

    void set(int idx, int val, int node, int lx, int rx) {
        if(rx - lx == 1) {
            SegData[node].sum = val;
            return;
        }

        int mid = (lx + rx) / 2;
        if(idx < mid)
            set(idx, val, 2 * node + 1, lx, mid);
        else
            set(idx, val, 2 * node + 2, mid, rx);

        SegData[node] = merge(SegData[2 * node + 1], SegData[2 * node + 2]);
    }
    // 0 indexed
    void set(int idx, int val) {
        set(idx, val, 0, 0, tree_size);
    }

    Node get_range(int l, int r, int node, int lx, int rx) {
        if(lx >= r || rx <= l)
            return Node();
        if(lx >= l && rx <= r)
            return SegData[node];

        int mid = (lx + rx) / 2;
        Node lf = get_range(l, r, 2 * node + 1, lx, mid);
        Node ri = get_range(l, r, 2 * node + 2, mid, rx);

        return merge(lf, ri);
    }

    // r is not inclusive [l, r)
    long long get_range(int l, int r) {
        return get_range(l, r, 0, 0, tree_size).sum;
    }
};