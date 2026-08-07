/**
 * Author: Unknown
 * Date: Unknown
 * Source: custom
 * Description: Dynamic (pointer-based) Segment Tree.
 *  Allocates nodes lazily to save memory, allowing range queries and point updates on large intervals.
 *  Uses half-open intervals $[l, r)$.
 * Time: $O(\log N)$ for updates and queries.
 * Status: untested
 */
#pragma once

struct TreeNode {
    int sum = 0;
    TreeNode *left = nullptr, *right = nullptr;
    void update(int val) {
        sum += val;
    }
};

using Node = TreeNode*;

struct DynamicSegTree {
    int n;
    Node root;

    DynamicSegTree(int sz) {
        n = sz;
        root = new TreeNode();
    }

    void update(int idx, int &val, Node &node, int lx, int rx) {
        if(rx - lx == 1) {
            node->update(val);
            return;
        }

        int mid = (lx + rx) / 2;
        if(idx < mid) {
            if (node->left == nullptr) node->left = new TreeNode();
            update(idx, val, node->left, lx, mid);
        }
        else {
            if (node->right == nullptr) node->right = new TreeNode();
            update(idx, val, node->right, mid, rx);
        }

        node->sum = ((node->left == nullptr) ? 0 : node->left->sum) +
                    ((node->right == nullptr) ? 0 : node->right->sum);
    }
    void update(int idx, int val) {
        update(idx, val, root, 0, n);
    }

    ll query(int l, int r, Node &node, int lx, int rx) {
        if(node == nullptr || lx >= r || rx <= l) return 0;
        if (lx >= l && rx <= r) return node->sum;

        int mid = (lx + rx) / 2;
        ll L = query(l, r, node->left, lx, mid);
        ll R = query(l, r, node->right, mid, rx);
        return L + R;
    }
    ll query(int l, int r) {
        return query(l, r, root, 0, n);
    }
};