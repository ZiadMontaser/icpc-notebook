/**
 * Author: Unknown
 * Date: Unknown
 * Description: Array-based Lazy Segment Tree. Supports range add, range set, and range sum queries.
 *  0-indexed API, range queries are half-open $[l, r)$.
 * Time: $O(\log N)$ for queries and updates, $O(N)$ for building.
 * Usage: SegTree st(sz(v)); st.build(v); st.add(l, r, val); st.set(l, r, val); st.get_range(l, r);
 * Status: untested
 */
#pragma once
struct Node {
    long long sum = 0;
    long long lazy_set, lazy_add = 0;
    bool is_lazy_set = 0, is_lazy_add = 0;
 
    Node(int x) : sum(x){}
    Node() {}
 
    void add(int val, int lx, int rx) {
        sum += (rx - lx) * val;
        lazy_add += val;
        is_lazy_add = 1;
    }
 
    void set(int val, int lx, int rx) {
        sum = (rx - lx) * val;
        lazy_set = val;
        is_lazy_set = 1;
        lazy_add = 0;
        is_lazy_add = 0;
    }
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
 
    void propagate(int node, int lx, int rx) {
        if(rx - lx == 1)
            return;
 
        int mid = (lx + rx) / 2;
 
        if(SegData[node].is_lazy_set) {
            SegData[2 * node + 1].set(SegData[node].lazy_set, lx, mid);
            SegData[2 * node + 2].set(SegData[node].lazy_set, mid, rx);
 
            SegData[node].lazy_set = 0;
            SegData[node].is_lazy_set = 0;
        }
 
        if(SegData[node].is_lazy_add) {
            SegData[2 * node + 1].add(SegData[node].lazy_add, lx, mid);
            SegData[2 * node + 2].add(SegData[node].lazy_add, mid, rx);
 
            SegData[node].lazy_add = 0;
            SegData[node].is_lazy_add = 0;
        }
    }
 
    void set(int l, int r, int val, int node, int lx, int rx) {
        propagate(node, lx, rx);
        if(lx >= r || rx <= l)
            return;
        if(lx >= l && rx <= r) {
            SegData[node].set(val, lx, rx);
            return;
        }
 
        int mid = (lx + rx) / 2;
        set(l, r, val, 2 * node + 1, lx, mid);
        set(l, r, val, 2 * node + 2, mid, rx);
        SegData[node] = merge(SegData[2 * node + 1], SegData[2 * node + 2]);
    }
    // 0 indexed
    void set(int l, int r, int val) {
        set(l, r, val, 0, 0, tree_size);
    }
 
    void add(int l, int r, int val, int node, int lx, int rx) {
        propagate(node, lx, rx);
        if(lx >= r || rx <= l)
            return;
        if(lx >= l && rx <= r) {
            SegData[node].add(val, lx, rx);
            return;
        }
 
        int mid = (lx + rx) / 2;
        add(l, r, val, 2 * node + 1, lx, mid);
        add(l, r, val, 2 * node + 2, mid, rx);
        SegData[node] = merge(SegData[2 * node + 1], SegData[2 * node + 2]);
    }
    // 0 indexed
    void add(int l, int r, int val) {
        add(l, r, val, 0, 0, tree_size);
    }
 
    Node get_range(int l, int r, int node, int lx, int rx) {
        propagate(node, lx, rx);
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

// ziad template
#pragma once
struct SegmentTree{
    int size;

    #define SegmentType int
    #define LazyType int
    SegmentType NUTRAL_ELEMENT = 0;
    LazyType NO_OPERATION = 0;

    #define L (2*i+1)
    #define R (2*i+2)

    vector<SegmentType> a;
    vector<LazyType> lazy;

    void AccumlateOperation(LazyType &a, LazyType b, int len = 1){
        a += b;
    }

    void ModifyOperation(SegmentType &a, LazyType b, int len = 1){
        a = a + b;
    }

    SegmentType CalcOperation(SegmentType a, SegmentType b){
        return merge(a, b);
    }

    SegmentType merge(SegmentType a, SegmentType b){
        return max(a, b);
    }

    void build(vector<SegmentType> &b){
        size = 1;
        while(size < b.size()) size *= 2;

        a.resize(size * 2, NUTRAL_ELEMENT);
        lazy.resize(size * 2, NO_OPERATION);

        for (int i = 0; i < b.size(); i++)
        {
            a[i+size-1] = b[i];
        }
        build(0, 0, size);
    }

    void build(int i, int l, int r){
        if(i >= a.size()) return;
        if(r - l == 1) return;

        int mid = (l + r) / 2;
        build(2 * i + 1, l, mid);
        build(2 * i + 2, mid, r);

        a[i] = merge(a[L], a[R]);
    }

    void Propogate(int i, int l, int r){
        if(lazy[i] == NO_OPERATION) return;

        ModifyOperation(a[i], lazy[i], (r - l));
 
        if(r - l > 1){
            AccumlateOperation(lazy[L], lazy[i]);
            AccumlateOperation(lazy[R], lazy[i]);
        }
        lazy[i] = NO_OPERATION;

    }

    SegmentType CalculateRec(int i, int l, int r, int lx, int rx){
        Propogate(i, l, r);
        
        if(l >= rx || r <= lx) return NUTRAL_ELEMENT;
        if(l >= lx && r <= rx){
            return a[i];
        }

        int mid = (l+r) / 2;
        return CalcOperation(CalculateRec(L, l, mid, lx, rx),
        CalculateRec(R, mid, r, lx, rx));
    }

    SegmentType Calculate(int l, int r){
        return CalculateRec(0, 0, size, l, r);
    }

    void Modify(int i, int l, int r, int lx, int rx, LazyType vx){
        Propogate(i, l , r);

        if(l >= rx || r <= lx) return;
        if(l >= lx && r <= rx) {
            AccumlateOperation(lazy[i], vx);
            
            Propogate(i, l , r);
            return;
        }

        int mid = (l+r) / 2;
        Modify(L, l, mid, lx, rx, vx);
        Modify(R, mid, r, lx, rx,vx);

        a[i] = CalcOperation(a[L], a[R]);
    }

    void Modify(int l, int r, LazyType v){
        Modify(0, 0, size, l, r, v);
    }

    SegmentType Find(int i, int l, int r, int lx, int rx, int vx){
        Propogate(i, l, r);

        if(l >= rx || r <= lx) return -1;
        if(l >= lx && r <= rx && a[i] < vx) {
            return -1;
        }

        if(r - l == 1){
            if(a[i] >= vx) return l;
            else return -1;
        }

        int mid = (l+r) / 2;

        auto left = Find(L, l, mid, lx, rx, vx);
        if(left != -1) return left;

        auto right = Find(R, mid, r, lx, rx, vx);
        return right;
    }

    SegmentType Find(int l, int r, int k){
        return Find(0, 0, size, l, r, k);
    }

    #undef SegmentType
    #undef LazyType
    #undef L
    #undef R
};