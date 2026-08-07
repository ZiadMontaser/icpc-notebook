/**
 * Author: Unknown
 * Date: Unknown
 * Source: custom
 * Description: Mo's algorithm with Rollback for offline array range queries.
 *  Used when adding elements is easy but removing is hard.
 *  Modify `add()` to track the state and push to `history` if `record` is true.
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

    struct State {
        int old_ans;
        int pos;
        int val;
    };
    vector<State> history;

    Mo(vector<int> &v) {
        arr = v;
        n = v.size();
        sq = sqrt(n) + 1;
        freq.assign(n + 1, 0);
        ans = 0;
    }

    void add(int idx, bool record = false) {
        if(record) {
            history.push_back({ans, arr[idx], freq[arr[idx]]});
        }

        // edit
    }

    void rollback() {
        while (!history.empty()) {
            auto [old_ans, pos, val] = history.back();
            history.pop_back();
            ans = old_ans;
            freq[pos] = val;
        }
    }

    void reset() {
        fill(freq.begin(), freq.end(), 0);
        ans = 0;
        history.clear();
    }

    void solve(vector<Query> &q) {

        vector<int> res(q.size());
        for(auto [lq, rq, idx] : q) {
            if(rq - lq + 1 > sq) continue;
            for (int i = lq; i <= rq; ++i) {
                add(i, true);
            }
            res[idx] = ans;
            rollback();
        }

        sort(q.begin(), q.end(), [&](auto &lf, auto &ri) {
            if(lf.l / sq == ri.l / sq)
                return lf.r < ri.r;
            return lf.l / sq < ri.l / sq;
        });

        int l = 0, r = -1, block = -1;
        for(auto [lq, rq, idx] : q) {
            if(rq - lq + 1 <= sq) continue;

            if(lq / sq != block) {
                block = lq / sq;
                reset();

                r = min((block + 1) * sq - 1, n - 1);
                l = r + 1;
            }

            while (r < rq) add(++r);

            int old_l = l;
            while (l > lq) add(--l, true);
            res[idx] = ans;
            rollback();
            l = old_l;
        }

        for (int i = 0; i < res.size(); ++i) {
            cout << res[i] << '\n';
        }
    }
};