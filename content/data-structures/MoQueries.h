/**
 * Author: Unknown
 * Date: Unknown
 * Source: custom
 * Description: Mo's algorithm for offline array range queries.
 *  Answers queries by sorting them in a cache-friendly way and moving interval endpoints.
 *  Modify `add()` and `rem()` to track the current state, and update `ans`.
 * Time: $O(N \sqrt Q)$
 * Status: untested
 */
#pragma once

struct Query {
    int l, r, idx;
};

struct Mo {
    int n, sq;
    vector<int> arr;
    int ans;
    vector<int> freq;
    Mo(vector<int> &v, int q) {
        arr = v;
        n = v.size();
        sq = sqrt(n) + 1;
        freq.assign(1e6 + 1, 0);
        ans = 0;
    }

    void add(int idx) {
        
    }
    void rem(int idx) {

    }

    void solve(vector<Query> &q) {

        sort(q.begin(), q.end(), [&](auto &lf, auto &ri) {
            if(lf.l / sq == ri.l / sq)
                return (lf.l / sq) & 1 ? lf.r > ri.r : lf.r < ri.r;
            return lf.l / sq < ri.l / sq;
        });

        int l = q[0].l, r = q[0].l;
        add(l);

        vector<ll> res(q.size());
        for(auto [lq, rq, idx] : q) {
            while (r < rq) add(++r);
            while (l < lq) rem(l++);
            while (l > lq) add(--l);
            while (r > rq) rem(r--);

            res[idx] = ans;
        }

        for (int i = 0; i < res.size(); ++i) {
            cout << res[i] << '\n';
        }
    }
};